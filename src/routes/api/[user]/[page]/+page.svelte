<script lang="ts">
  let { data } = $props();
  const messageData = data.messages[data.page];
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
