<script lang="ts">
  import { PixelEditor, Pencil } from "@curtishughes/pixel-editor";
  import { resolution } from "../../../constants";
  import type { imageProps } from "./props";
  import { onMount } from "svelte";
  import PreviewEmbed from "../preview/previewEmbed.svelte";
  import Brush from "./tools/brush";

  let editorEl: HTMLCanvasElement | null = $state(null);
  let editor: PixelEditor | null = $state(null);

  let toolType: keyof typeof tools = $state("pencil");
  let brushSize: "px" | "sm" | "md" | "lg" = $state("md");

  const tools = $derived({
    pencil: new Brush("black", brushSize),
    eraser: new Brush(undefined, brushSize),
  });

  onMount(() => {
    if (editorEl && liveImage) {
      const ctx = editorEl.getContext("2d");
      if (ctx) {
        const img = new Image();
        img.onload = () => {
          ctx.drawImage(img, 0, 0);
        };
        img.src = liveImage;
      }
    }
  });

  onMount(() => {
    if (editorEl) {
      editor = new PixelEditor(
        editorEl,
        resolution.w,
        resolution.h,
        tools[toolType]
      );
    }
  });

  $effect(() => {
    if (editor) {
      editor.tool = tools[toolType];
    }
  });

  let {
    liveImage = $bindable(),
    updateImage,
    messagePreview,
    account,
  }: imageProps = $props();

  const save = () => {
    if (editorEl) {
      const image = editorEl.toDataURL();
      updateImage({ image });
    }
  };
</script>

<div class="editor-frame relative bg-white">
  <canvas class="z-0 relative" bind:this={editorEl} onpointerup={save}></canvas>
  <div class="embed-frame">
    <PreviewEmbed
      author={account?.name}
      message={messagePreview}
      showPixels={true}
      showFilter={false}
    />
  </div>
</div>
<div class="toolbar">
  <button
    type="button"
    class:active={toolType === "eraser"}
    onclick={() => {
      if (editor) toolType = "eraser";
    }}>Eraser</button
  >
  <button
    type="button"
    class:active={toolType === "pencil"}
    onclick={() => {
      if (editor) toolType = "pencil";
    }}>Pencil</button
  >
  <div class="btn-group">
    <p type="button" class="btn-label p-2">Brush</p>
    <button
      type="button"
      onclick={() => {
        if (editor) {
          brushSize = "px";
        }
      }}
      class:active={brushSize === "px"}
      class="brush brush-px"
      title="one pixel"
    ></button>
    <button
      type="button"
      onclick={() => {
        if (editor) {
          brushSize = "sm";
        }
      }}
      class:active={brushSize === "sm"}
      class="brush brush-sm"
      title="small"
    ></button>
    <button
      type="button"
      onclick={() => {
        if (editor) {
          brushSize = "md";
        }
      }}
      class:active={brushSize === "md"}
      class="brush brush-md"
      title="medium"
    ></button>
    <button
      type="button"
      onclick={() => {
        if (editor) {
          brushSize = "lg";
        }
      }}
      class:active={brushSize === "lg"}
      class="brush brush-lg"
      title="large"
    ></button>
  </div>
  <button
    type="button"
    onclick={() => {
      if (editor) editor.undo();
      save();
    }}>Undo</button
  >
  <button
    type="button"
    onclick={() => {
      if (editor) editor.redo();
      save();
    }}>Redo</button
  >
  <div class="grow"></div>
  <button
    type="button"
    onclick={() => {
      if (editor) editor.clear();
      save();
    }}>Clear</button
  >
</div>

<style lang="postcss">
  .toolbar {
    @apply flex flex-wrap items-center gap-2 bg-primary;
    button {
      @apply p-2 bg-black bg-opacity-30 text-white hover:scale-95 hover:bg-opacity-50 transition;
      &.active {
        @apply bg-opacity-100 bg-black scale-95;
      }
    }
    .btn-group {
      @apply flex items-center bg-black bg-opacity-30 text-white;
      .btn-label {
        @apply pl-2 py-2 hover:scale-100 bg-opacity-0;
      }
      button {
        @apply h-full leading-none block p-2 align-middle;
      }
    }
    button.brush {
      @apply w-9 h-9;
      &::after {
        @apply block w-4 h-4 bg-white rounded-full mx-auto;
        content: "";
      }
      &.brush-px:after {
        @apply w-1 h-1 rounded-none;
      }
      &.brush-sm:after {
        @apply w-2 h-2;
      }
      &.brush-md:after {
        @apply w-3 h-3;
      }
      &.brush-lg:after {
        @apply w-4 h-4;
      }
    }
  }
  .embed-frame {
    @apply z-10 w-full absolute top-0 pointer-events-none;
  }
</style>
