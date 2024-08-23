<script lang="ts">
  import FrontFace from "$lib/components/preview/front-face.svelte";
  import debounce from "debounce";
  import { AppModes, type messageDataType } from "../../constants";
  import moment from "moment";
  import { env } from "$env/dynamic/public";
  import { Role } from "../../constants.js";
  import { fade } from "svelte/transition";

  const { data } = $props();

  let previewData = $state({
    author: data.account?.name!,
    message: "",
  });

  const updateText = debounce((e) => {
    previewData.message = (e.target as HTMLInputElement)?.value;
  }, 500);

  let liveText = $state("");
  let charsLeft = $derived(140 - liveText.length);
  let sending = $state(false);

  let timeTill = $state(data.nextTime - Date.now());
  let canSend = $derived(timeTill <= 0);
  let timeTillLabel = $state(moment(data.nextTime).fromNow());
  setInterval(() => {
    timeTill = data.nextTime - Date.now();
    timeTillLabel = moment(data.nextTime).fromNow();
  }, 250);

  let showComplete = $state(true);
</script>

<!-- Preview box -->
<div class="p-4 relative">
  <FrontFace page={0} live={true} bind:previewData userData={data.user} />
  {#if !canSend && showComplete}
    <button
      class="preview-complete"
      onclick={() => {
        showComplete = false;
      }}
      out:fade
    >
      <h3 class="daydream daydream-lg">
        Submitted!
        {#if data.appMode === AppModes.LimitSends}
          You can send again in {moment
            .duration(env.PUBLIC_TIME_INTERVAL)
            .humanize()}
        {:else}
          Your message will appear on {moment(data.nextTime).format(
            "dddd, MMMM Do YYYY"
          )}
        {/if}
      </h3>
    </button>
  {/if}
</div>
<label class="form-control block max-w-screen-md mx-auto">
  <div class="label">
    <span class="label-text">
      {#if charsLeft > 0}
        Your message ({charsLeft} left)
      {:else if charsLeft === 0}
        Your message (the perfect length)
      {:else if charsLeft > -50}
        Your very long message ({-charsLeft} over)
      {:else if charsLeft > -100}
        Your super long message ({-charsLeft} over)
      {:else if charsLeft > -140}
        Please consider writing a shorter message, this is getting ridiculous ({-charsLeft}
        over)
      {:else if charsLeft > -200}
        Your message is now twice the length of a tweet ({-charsLeft} over) and possibly
        shouldn't be, but who am I to say?
      {:else}
        I'm cutting you off here as you've probably already broken the screen's
        layout ({-charsLeft})
      {/if}
    </span>
  </div>
  <form
    onsubmit={async (e) => {
      e.preventDefault();
      if (!canSend && data.role !== Role.Admin) return false;
      sending = true;
      await fetch(`/api/${data.user.userID}/post`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(previewData),
      });
      sending = false;
      window.location.reload();
      return false;
    }}
  >
    <textarea
      class="textarea textarea-bordered w-full h-24 transition"
      placeholder="Your message here..."
      bind:value={liveText}
      onkeyup={(e) => updateText(e)}
      disabled={sending || !(canSend || data.role === Role.Admin)}
      maxlength="340"
      required
    ></textarea>

    {#if !canSend && timeTill}
      <progress
        class="progress mt-2"
        value={parseInt(env.PUBLIC_TIME_INTERVAL) - timeTill}
        max={parseInt(env.PUBLIC_TIME_INTERVAL)}
      ></progress>
    {/if}
    <button
      type="submit"
      class="btn btn-primary mt-2 transition"
      disabled={sending || !(canSend || data.role === Role.Admin)}
    >
      {#if sending}
        Sending...
      {:else if canSend}
        Send (once {moment.duration(env.PUBLIC_TIME_INTERVAL).humanize()})
      {:else}
        You can send {timeTillLabel}
        {#if timeTill < 60 * 60 * 1000}
          ({moment(timeTill).format("mm:ss")})
        {:else if timeTill < 24 * 60 * 60 * 1000}
          (at {moment(data.nextTime).format("h:mma")})
        {:else}
          (on {moment(data.nextTime).format("dddd, MMMM Do YYYY")})
        {/if}
      {/if}
    </button>
  </form>
  {#if data.role === Role.Admin}
    <!-- Admin section -->
    <div class="card mt-10">
      <div
        class="card bg-base-100 w-full shadow-xl card-bordered border-red-700 border-2"
      >
        <div class="card-body">
          <h2 class="card-title">Admin Mode!</h2>
          {#if data.messages}
            <div class="overflow-x-auto">
              <table class="table">
                <!-- head -->
                <thead>
                  <tr>
                    <th>Time</th>
                    <th>User</th>
                    <th>Message</th>
                    <th>Action</th>
                  </tr>
                </thead>
                <tbody>
                  {#each data.messages as message}
                    <tr>
                      <td title={moment(message.createdAt).format()}
                        >{moment(message.createdAt).fromNow()}</td
                      >
                      <td>{message.author?.name}</td>
                      <td>{message.message}</td>
                      <td>
                        <button
                          class="btn btn-error"
                          onclick={async () => {
                            if (
                              !confirm(
                                `Are you sure you want to delete ${message.author?.name}'s message?`
                              )
                            )
                              return;
                            await fetch(`/api/admin/${message.id}`, {
                              method: "DELETE",
                              headers: {
                                "Content-Type": "application/json",
                              },
                            });
                            window.location.reload();
                          }}
                        >
                          Delete
                        </button>
                      </td>
                    </tr>{/each}
                </tbody>
              </table>
            </div>
          {/if}
          <button
            class="btn btn-error mt-2"
            onclick={async () => {
              if (!confirm("Are you sure you want to clear all messages?"))
                return;
              await fetch(`/api/admin/delete`, {
                method: "POST",
                headers: {
                  "Content-Type": "application/json",
                },
              });
              window.location.reload();
            }}
          >
            Clear ALL Messages
          </button>
        </div>
      </div>
    </div>
  {/if}
</label>

<style lang="postcss">
  .preview-complete {
    @apply rounded-3xl w-full h-auto bg-green-800 mx-auto p-6 shadow-lg flex items-center justify-center text-center;
    @apply absolute z-20 block top-4 left-0 right-0;
    @apply bg-opacity-80 backdrop-blur transition-colors duration-500;
    aspect-ratio: 296/128;
    max-width: calc(296px * 2);
    h3 {
      @apply text-white transition-transform duration-500;
    }
    &:hover {
      @apply bg-opacity-100;
      h3 {
        @apply scale-105;
      }
    }
  }
</style>
