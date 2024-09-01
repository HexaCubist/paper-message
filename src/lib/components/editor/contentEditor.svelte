<script lang="ts">
  import PixelEditor from "./pixelEditor.svelte";
  import type { editorProps } from "./props";
  import TextEditor from "./textEditor.svelte";
  import debounce from "debounce";
  let {
    editorData = $bindable(),
    sending = false,
    canSend = false,
    update,
    disabled,
    account,
  }: editorProps = $props();

  const updateText = debounce((e) => {
    if (editorData.type !== "text") return;
    editorData.content.text = (e.target as HTMLInputElement)?.value;
    update(editorData);
  }, 500);
  const updateImage = debounce(({ image }) => {
    if (editorData.type !== "image") return;
    editorData.content.image = image;
    update(editorData);
  }, 150);
</script>

<div role="tablist" class="tabs tabs-bordered">
  <input
    value="text"
    bind:group={editorData.type}
    type="radio"
    name="content_type"
    role="tab"
    class="tab"
    aria-label="Text{editorData.content.text ? ' (will send)' : ''}"
  />
  <input
    value="image"
    bind:group={editorData.type}
    type="radio"
    name="content_type"
    role="tab"
    class="tab"
    aria-label="Image{editorData.content.image ? ' (will send)' : ''}"
  />
</div>
<div class="frame">
  <div class:hidden={editorData.type !== "text"}>
    <TextEditor
      bind:liveText={editorData.content.text}
      {updateText}
      {sending}
      {canSend}
      {disabled}
    />
  </div>
  <div class:hidden={editorData.type !== "image"}>
    <PixelEditor
      bind:liveImage={editorData.content.image}
      messagePreview={editorData.content.text}
      {updateImage}
      {sending}
      {canSend}
      {disabled}
      {account}
    />
  </div>
</div>

<style lang="postcss">
  .frame {
    @apply border border-gray-300 border-t-0;
  }
</style>
