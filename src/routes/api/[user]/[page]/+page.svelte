<script lang="ts">
  import { browser } from "$app/environment";

  let { data } = $props();
  let messageData = $state(data.messages[data.page]);
  if (browser) {
    // Search param is "preview" and if set should override the message data
    const url = new URL(location.href);
    const preview = url.searchParams.get("preview");
    if (preview) {
      messageData = JSON.parse(preview);
    }
  }
</script>

<div class="h-full flex flex-col justify-center">
  {#if messageData}
    <h1 class="daydream">{messageData.from} writes...</h1>

    <p class="text-sm">
      {messageData.text}
    </p>
  {:else}
    <h1 class="text-center">Message Deleted 💔</h1>
  {/if}
</div>

<style lang="postcss">
  h1 {
  }
</style>
