<script lang="ts">
    const { data } = $props();
</script>

<div class="flex h-full items-center p-2 gap-2">
    <!-- QRCode needs to be a multiple of 21, but the block as a whole needs to be even -->
    <img src={data.update_details} alt="" class="shrink-0 block w-[42px]" />
    <div class="">
      <p class="daydream">Update Available!</p>
      <p class="text-sm">
        <!-- Scan the QR code to check out all the new bugs added in this version.<br/> -->
        Hold down the button to start downloading the update.<br/>
        If I don't deserve this update, press the button fast to ignore it.<br/>
      </p>
    </div>
</div>
  