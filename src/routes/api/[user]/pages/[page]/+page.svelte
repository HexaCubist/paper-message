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
      messageData = JSON.parse(preview);
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
    <h1 class="daydream">{messageData.from} writes...</h1>

    <p class="text-sm">
      {messageData.message}
    </p>
  {:else}
    <h1 class="text-center">Message Deleted 💔</h1>
  {/if}
</div>

<style lang="postcss">
  h1 {
  }
</style>
