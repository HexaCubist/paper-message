<script lang="ts">
  import FrontFace from "$lib/components/preview/front-face.svelte";
  import debounce from "debounce";
  import type { messageDataType } from "../../hooks.server.js";
  import moment from "moment";
  import { env } from "$env/dynamic/public";

  const { data } = $props();

  let previewData = $state<messageDataType>({
    from: "John Doe",
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
</script>

<!-- Preview box -->
<div class="p-4">
  <FrontFace page={0} live={true} bind:previewData userData={data.user} />
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
      if (!canSend) return false;
      sending = true;
      await fetch(`/api/${data.user.userID}/post`, {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(previewData),
      });
      sending = false;
      return false;
    }}
  >
    <textarea
      class="textarea textarea-bordered w-full h-24 transition"
      placeholder="Your message here..."
      bind:value={liveText}
      onkeyup={(e) => updateText(e)}
      disabled={sending || !canSend}
      maxlength="340"
      required
    ></textarea>

    {#if !canSend}
      <progress
        class="progress mt-2"
        value={parseInt(env.PUBLIC_TIME_INTERVAL) - timeTill}
        max={parseInt(env.PUBLIC_TIME_INTERVAL)}
      ></progress>
    {/if}
    <button
      type="submit"
      class="btn btn-primary mt-2 transition"
      disabled={sending || !canSend}
    >
      {#if sending}
        Sending...
      {:else if canSend}
        Send
      {:else}
        You can send in {timeTillLabel}
        {#if timeTill < 60 * 60 * 1000}
          ({moment(timeTill).format("mm:ss")})
        {:else if timeTill < 24 * 60 * 60 * 1000}
          (at {moment(data.nextTime).format("HH:mma")})
        {:else}
          (on {moment(data.nextTime).format("dddd, MMMM Do YYYY")})
        {/if}
      {/if}
    </button>
  </form>
</label>
