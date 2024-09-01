<script lang="ts">
  const { data } = $props();
</script>

<div class="flex h-full items-center p-2 gap-2">
  <!-- QRCode needs to be a multiple of 21, but the block as a whole needs to be even -->
  <img src={data.update_details} alt="" class="shrink-0 block w-[42px]" />
  <div class="">
    <p class="daydream">Update Finished!</p>
    <p class="text-sm">
      Hopefully I start back up in a couple of seconds. If not, try using a hammer.<br/>
    </p>
  </div>
</div>
