<script lang="ts">
  import { fade } from "svelte/transition";
  import type { userDataType } from "../../../routes/api/[user]/+server";

  import church from "./img/church.png";

  let {
    page = $bindable(0),
    live = $bindable(true),
    previewData = $bindable(false),
    userData,
  }: {
    page: number;
    live: boolean;
    previewData?:
      | {
          author: string;
          message: string;
        }
      | false;
    userData: userDataType;
  } = $props();

  const patternSize = 50;
  let boxSize: undefined | ResizeObserverEntry["contentBoxSize"] = $state();
  let width = $derived(boxSize ? boxSize[0].inlineSize : undefined);
  let ratio = $derived(width ? width / 296 : undefined);

  let changing = $state(false);
  let previewing = $derived(previewData !== false && previewData.message);

  const changePage = async (newPage: number) => {
    if (changing) return;
    let oldPage = page;
    changing = true;
    setTimeout(() => {
      page = newPage;
    }, 250);
    if (previewing || live || oldPage === newPage)
      setTimeout(() => {
        changing = false;
      }, 500);
  };
</script>

<div class="frame">
  <button
    title={previewing ? "Preview is active" : "Click to change page"}
    class="outer-interact"
    class:previewing
    class:changing
    onclick={() => {
      changePage((page + 1) % userData.total_pages);
    }}
    disabled={changing || previewing}
  >
    <svg
      class="overflow-visible"
      viewBox="0 0 362.07812 156.84961"
      version="1.1"
      xmlns="http://www.w3.org/2000/svg"
    >
      <defs>
        <pattern
          id="pattern0"
          patternUnits="userSpaceOnUse"
          width={patternSize}
          height={patternSize}
          class="pattern"
          ><path
            d="M 0,0 0,{patternSize} {patternSize},{patternSize} {patternSize},0 Z M {patternSize},{patternSize} {patternSize},{patternSize} {patternSize},{patternSize} {patternSize},{patternSize} Z"
          ></path><image
            x="0"
            y="0"
            width={patternSize}
            height={patternSize}
            href={church}
          ></image></pattern
        >
      </defs>
      <g id="g8" transform="translate(-0.5,-0.5)">
        <path
          id="path5"
          class="outer-frame"
          style="stroke:none"
          d="M 18.642578,0.5 A 18.140429,18.140429 0 0 0 0.5,18.642578 v 98.347652 22.22071 a 18.146884,18.146884 0 0 0 18.140625,18.13867 H 344.43945 a 18.146884,18.146884 0 0 0 18.13867,-18.13867 V 18.642578 A 18.140429,18.140429 0 0 0 344.4375,0.5 Z M 61.349609,18.263672 H 324.40625 V 138.83008 H 61.349609 Z"
          fill="#303030"
        />
        <!-- Replaced path below with a forienobject to display page -->
        <!-- <path
        d="M 61.349604,18.263672 H 324.40625 V 138.83008 H 61.349604 Z"
        style="fill:#fff;stroke:none"
        class="shadow-inner"
        id="screen"
      /> -->
        <foreignobject
          class="node overflow-visible"
          x="61.349609"
          y="18.263672"
          width="263.05664"
          height="120.56641"
        >
          <div
            bind:contentBoxSize={boxSize}
            class="inner-frame"
            class:changing
            style:filter="contrast(0.7) brightness(1.25)"
          >
            {#if previewing && previewData}
              {#key JSON.stringify(previewData)}
                <iframe
                  transition:fade
                  class="col-start-1 row-start-1"
                  src="/api/0/pages/1?live&preview={encodeURIComponent(
                    JSON.stringify(previewData)
                  )}"
                  style:transform="scale({ratio})"
                  title="Preview"
                ></iframe>
              {/key}
            {:else if live}
              <iframe
                src="/api/0/pages/{page}?live"
                style:transform="scale({ratio})"
                title="Live"
              ></iframe>
            {:else}
              <img
                src="/api/0/pages/{page}"
                class="image-preview"
                height="263.05664"
                alt="Page {page}"
                onload={() => {
                  changing = false;
                }}
              />
            {/if}
          </div>
        </foreignobject>
      </g>
    </svg>
  </button>
  <div class="form-control flex-row justify-end items-center mt-1">
    <label class="label cursor-pointer gap-2">
      <input
        type="checkbox"
        class="toggle toggle-xs"
        bind:checked={live}
        disabled={previewing}
      />
      <span class="label-text text-sm">Live mode</span>
    </label>
    {#if previewing}
      <button
        class="btn btn-xs shrink !w-auto btn-primary"
        onclick={() => {
          if (previewData) previewData.message = "";
        }}
      >
        Reset Preview
      </button>
    {/if}
  </div>
</div>

<style lang="postcss">
  .frame {
    @apply w-full mx-auto;
    max-width: calc(296px * 2);
  }
  .outer-interact {
    @apply w-full block cursor-pointer transition;
    @apply hover:opacity-90 hover:scale-95;
    &:disabled {
      @apply cursor-not-allowed hover:opacity-100 hover:scale-100;
    }
  }
  .inner-frame {
    @apply grid h-full grid-cols-1 grid-rows-1 items-center w-full bg-white bg-repeat contain-inline-size transition justify-center justify-items-center;
    background-image: url("img/cardboard-flat.png");
    background-size: 100px;
    box-shadow:
      inset 0 0 0.3rem 1px #30303066,
      0 0 0.3rem 1px #000000;
    &.changing {
      @apply bg-black;
      background-image: none;
    }
  }
  .outer-frame {
    @apply drop-shadow-lg transition duration-500;
    fill: url(#pattern0);
  }

  #pattern0 {
    path {
      @apply fill-zinc-900 transition-all duration-700;
    }
    image {
      @apply opacity-30 transition-all duration-700;
    }
  }
  iframe {
    @apply w-auto h-auto mix-blend-multiply pointer-events-none;
    width: 296px;
    height: 128px;
    border: none;
    aspect-ratio: 296 / 128;
  }
  .image-preview {
    @apply mix-blend-multiply;
    transform: rotate(90deg);
    image-rendering: pixelated;
  }

  .previewing {
    #pattern0 {
      path {
        @apply fill-slate-800;
      }
      image {
        @apply opacity-40;
      }
    }
    .outer-frame {
      filter: drop-shadow(0 4px 6px #00228899);
    }
  }
</style>
