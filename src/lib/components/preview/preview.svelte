<script lang="ts">
  import FrontFace from "./front-face.svelte";
</script>

<div class="frontFace">
  <FrontFace page={0} image={false} />
</div>

<style lang="postcss">
  .frontFace {
    @apply w-full h-full p-4;
  }
</style>
