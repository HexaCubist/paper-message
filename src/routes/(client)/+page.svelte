<script lang="ts">
  import FrontFace from "$lib/components/preview/front-face.svelte";
  import debounce from "debounce";
  import type { messageDataType } from "../../hooks.server.js";

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
</script>

<!-- Preview box -->
<div class="p-4">
  <FrontFace page={0} live={true} bind:previewData userData={data.user} />
</div>
<label class="form-control block max-w-screen-md mx-auto">
  <div class="label">
    <span class="label-text">Your message ({charsLeft} left)</span>
  </div>
  <textarea
    class="textarea textarea-bordered w-full h-24"
    placeholder="Your message here..."
    bind:value={liveText}
    onkeyup={(e) => updateText(e)}
  ></textarea>
</label>
