<script lang="ts">
	import type { LayoutData } from './$types';
	import '../../app.postcss';
	let { children, data } = $props();
	


	let stockPages = 1; // Home and QR
	let pages = stockPages + data.messages.length
	let currentPage = data.page || 0;
	const setTime = () => {
		return new Date().toLocaleString('en-NZ', {
		hour: 'numeric',
		minute: 'numeric',
		second: 'numeric',
		hour12: false
	})
	}
	let time = $state(setTime());
	setInterval(() => {
		time = setTime();
	}, 1000);

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
	<div class="col bg-black text-white w-[29px] shrink-0 h-full rounded p-[2px] flex flex-col">
		<div class="grow py-[5px] relative mx-auto text-sm">
				<!-- Sidebar scroller -->
				<div class="w-[9px] text-center bg-white h-full rounded-full relative overflow-clip">
					<div style:width="calc(100% - 2px)" class="bg-black left-0 right-0 mx-auto rounded-full absolute transition leading-none flex items-center text-center justify-center"
					style:height="calc({(1 / (pages-1)) * 100}% - 4px)"
					style:top="calc({(currentPage / (pages-1)) * 100}% + 2px)"
					>
					{currentPage + 1}
				</div>
				</div>
		</div>
		<div class="qrHolder w-[25px] h-[25px]">
		{#await qr then src}
			<img class="mx-auto w-full h-full" src={src} alt="QR Code"  />
		{/await}
		</div>
	</div>
	<div class="col grow overflow-hidden relative p-[2px]">
		<div class="header absolute flex gap-[2px] text-sm justify-end w-full right-[2px]">
			{time}
		</div>
		{@render children()}
	</div>
</div>



<style lang="postcss">
	:global(body) {
		@apply bg-white text-black relative block origin-top-left;
		width: 296px;
		height: 128px;
	}
	</style>