<script lang="ts">
  const { data } = $props();
</script>

<div class="flex h-full items-start p-2 gap-2">
  <!-- QRCode needs to be a multiple of 21, but the block as a whole needs to be even -->
  <img src={data.update_details} alt="" class="shrink-0 block w-[42px]" />
  <div class="">
    <p class="daydream">Downloading...</p>
    <p class="text-sm">
      Scan the QR code to check out all the new bugs added in this version.
    </p>
  </div>
</div>
