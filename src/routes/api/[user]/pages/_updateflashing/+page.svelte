<script lang="ts">
  const { data } = $props();
</script>

<div class="flex h-full items-start p-2 gap-2">
  <!-- QRCode needs to be a multiple of 21, but the block as a whole needs to be even -->
  <img src={data.update_details} alt="" class="shrink-0 block w-[42px]" />
  <div class="">
    <p class="daydream">Flashing update...</p>
    <p class="text-sm">
      If something goes horribly wrong, use the website's device manager before it starts plotting its revenge.<br/>
    </p>
  </div>
</div>
