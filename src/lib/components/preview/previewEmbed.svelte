<script lang="ts">
  import { fade } from "svelte/transition";
  import { resolution } from "../../../constants";

  let boxSize: undefined | ResizeObserverEntry["contentBoxSize"] = $state();
  let width = $derived(boxSize ? boxSize[0].inlineSize : undefined);
  let ratio = $derived(width ? width / resolution.w : undefined);

  let {
    author = "Someone",
    message = "",
    showPixels = false,
    showFilter = true,
  }: {
    author?: string;
    message?: string;
    showPixels?: boolean;
    showFilter?: boolean;
  } = $props();

  let changing = $state(false);
  $effect(() => {
    message;
    author;
    changing = true;
    setTimeout(() => {
      changing = false;
    }, 500);
  });
</script>

<div
  class="inner-frame"
  bind:contentBoxSize={boxSize}
  class:changing
  class:showPixels
  style:filter={showFilter ? "contrast(0.7) brightness(1.25)" : undefined}
  style:aspect-ratio="{resolution.w} / {resolution.h}"
  style:--ratio={ratio}
>
  {#key JSON.stringify({ author, message })}
    <iframe
      transition:fade
      class="col-start-1 row-start-1"
      src="/api/0/pages/1?live&preview={encodeURIComponent(
        JSON.stringify({ author, message })
      )}"
      style:transform="scale({ratio})"
      style:width="{resolution.w}px"
      style:height="{resolution.h}px"
      title="Preview"
    ></iframe>
  {/key}
</div>

<style lang="postcss">
  .inner-frame {
    @apply grid h-full grid-cols-1 grid-rows-1 items-center w-full contain-inline-size transition justify-center justify-items-center relative;
    /* @apply pointer-events-none select-none; */
    container-type: size;
    @apply bg-transparent;
    &.changing {
      @apply bg-black;
    }
    &.showPixels {
      @apply bg-repeat bg-left-top;
      background-image: url("./img/4px-subtle.png");
      background-size: calc(var(--ratio) * 2px);
    }
  }
</style>
