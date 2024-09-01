<script lang="ts">
  import { page } from "$app/stores";
  import { onMount } from "svelte";

  let { data } = $props();
  let messageData: messageDataType = $state(data.messages[data.page - 1]);
  // if (browser) {
  // Search param is "preview" and if set should override the message data
  let previewData: undefined | Record<string, any> = undefined;
  const updateMessage = () => {
    const url = new URL($page.url);
    const preview = url.searchParams.get("preview");
    if (preview) {
      previewData = JSON.parse(preview);
      if (!previewData) return;
      messageData = {
        id: 0,
        message: previewData.message,
        image: undefined,
        createdAt: new Date(),
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
  onMount(() => {
    if (previewData) {
      document.body.style.backgroundColor = "transparent";
      const html = document.querySelector("html");
      if (html) {
        html.style.backgroundColor = "transparent";
      }
    }
  });

  onMount(() => {
    if (messageData.image) {
      document.body.style.backgroundImage = `url(${messageData.image})`;
    }
  });
</script>

<div class="h-full flex flex-col justify-center relative z-10">
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
