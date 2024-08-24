<script lang="ts">
  import { page } from "$app/stores";

  let { data } = $props();
  let messageData = $state(data.messages[data.page - 1]);
  // if (browser) {
  // Search param is "preview" and if set should override the message data
  const updateMessage = () => {
    const url = new URL($page.url);
    const preview = url.searchParams.get("preview");
    if (preview) {
      const previewData = JSON.parse(preview);
      messageData = {
        id: 0,
        message: previewData.message,
        authorId: "",
        author: {
          id: "",
          name: previewData.author,
          image: null,
        },
      };
    }
  };
  $effect(() => {
    $page.url;
    updateMessage();
  });
  updateMessage();
</script>

<div class="h-full flex flex-col justify-center">
  {#if messageData}
    <h1 class="daydream">{messageData.author?.name} writes...</h1>

    <p class="text-sm">
      {messageData.message}
    </p>
  {:else}
    <h1 class="text-center">Something went wrong 💔</h1>
    <p class="text-sm text-center">
      Try changing pages again, or restart the device! Let us know if this keeps
      happening.
    </p>
  {/if}
</div>

<style lang="postcss">
  h1 {
  }
</style>
