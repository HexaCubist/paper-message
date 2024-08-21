<script lang="ts">
	import '../../app.postcss';
	let { children } = $props();
	

	let pages = 2;
	let currentPage = 0;

	import QRCode from 'qrcode'
	const qr = QRCode.toDataURL('https://paper.zac.nz/', {
		errorCorrectionLevel: "L",
		margin: 0,
		color: {
			dark: "#ffffff",
			light: "#000000"
		}
	})
</script>

<div class="flex gap-[2px] h-full overflow-hidden">
	<div class="col bg-black text-white w-[30px] shrink-0 h-full rounded p-[2px] flex flex-col">
		<div class="grow py-[5px] relative mx-auto text-sm">
				<!-- Sidebar scroller -->
				<div class="w-[10px] text-center bg-white h-full rounded-full relative">
					<div style:width="calc(100% - 2px)" class="bg-black left-0 right-0 mx-auto rounded-full absolute transition"
					style:height="calc({(1 / pages) * 100}% - 4px)"
					style:top="calc({(currentPage / pages) * 100}% + 2px)"
					>
					{currentPage + 1}
				</div>
				</div>
				<!-- Number Indicator -->
				 <!-- The indicator should be at the center of the scrollbar vetically. We can achieve this simply by using a flex and aligning the text to the center. -->
				<div class="text-sm absolute w-auto flex items-center justify-center left-0 right-0 mx-auto hidden" style:top={
					`calc(${(currentPage / pages) * 100}% + 5px)`
				}
				style:height="calc((100% / {pages}) - 10px)"
				>
				<span class="bg-black w-[12px] h-[12px] text-center">
					{currentPage+1}
				</span>
				</div>
		</div>
		{#await qr then src}
			<img src={src} alt="QR Code" />
		{/await}
	</div>
	<div class="col grow">
		{@render children()}
	</div>
</div>



<style lang="postcss">
	:global(body) {
		@apply bg-gray-100 text-black relative block origin-top-left;
		width: 296px;
		height: 128px;
		transform: scale(2);
	}
	</style>