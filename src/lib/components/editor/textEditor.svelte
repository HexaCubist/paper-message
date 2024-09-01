<script lang="ts">
  import type { textProps } from "./props";

  let {
    liveText = $bindable(),
    updateText,
    sending,
    canSend,
    disabled,
  }: textProps = $props();

  let charsLeft = $derived(140 - liveText.length);
</script>

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
<textarea
  class="textarea textarea-bordered w-full h-24 transition"
  placeholder="Your message here..."
  bind:value={liveText}
  name="message"
  onkeyup={(e) => updateText(e)}
  disabled={sending || disabled}
  maxlength="340"
></textarea>
