<script lang="ts">
  const { data } = $props();
</script>

<div class="flex flex-col h-full">
  <div class="flex grow items-center pb-2 gap-2">
    <img src={data.wifi_ip} alt="" class="block h-[40px] w-[40px]" />
    <div>
      <p class="daydream">Get Connected!</p>
      <p class="text-sm">
        Open your WiFi and connnect to "RSB-Device". Use the page that pops up
        to connect me to the internet.
      </p>
    </div>
  </div>
  <p class="text-sm">
    Nothing showing? Make sure you're on the WiFi and then try scanning the QR
    code above.
  </p>
</div>
