<script lang="ts">
  const { data } = $props();
</script>

{#if data.messages.length}
  <h1 class="h-full flex flex-col justify-center text-center">
    <p class="daydream">New Message{data.messages.length > 1 ? "s" : ""}!</p>
    <p class="text-sm">Press button to read...</p>
  </h1>
{:else}
  <h1 class="h-full flex flex-col justify-center text-center">
    <p class="daydream">Royal Society of Besties</p>
    <p class="text-sm">No new messages... Why not send one?</p>
  </h1>
{/if}
