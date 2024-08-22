<script lang="ts">
  import FrontFace from "$lib/components/preview/front-face.svelte";

  const { data } = $props();

  let previewData = $state({
    from: "John Doe",
    text: "Hello, world!",
  });
</script>

<!-- Preview box -->
<div class="p-4">
  <FrontFace page={0} live={true} {previewData} />
</div>
<label class="form-control block">
  <div class="label">
    <span class="label-text">Your message</span>
  </div>
  <textarea
    class="textarea textarea-bordered w-full h-24"
    placeholder="Your message here..."
    bind:value={previewData.text}
  ></textarea>
</label>
