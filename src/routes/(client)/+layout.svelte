<script lang="ts">
	import '../../app.postcss';
	let { children, data } = $props();

	const showSidebar = false;
</script>

<div class="pageLayout">

	<div class="navbar bg-base-100 text-base-content border border-black rounded-box">
		<a class="btn btn-ghost text-lg">Paper Messages</a>
	</div>
	<div class="flex flex-wrap mt-4 gap-4">
		{#if showSidebar}
		<div class="sidebar w-full max-w-xs lg:max-w-sm col-span-1 bg-base-100 text-base-content card card-bordered border-black">
			<div class="card-body">
				<h1 class="text-lg font-semibold">Recent Messages</h1>
			</div>
		</div>
		{/if}
		<div class="grow min-w-64">
			{@render children()}
			</div>
	</div>
	
</div>

<style lang="postcss">
	.pageLayout {
		@apply container mx-auto grow grid grid-rows-2;
		grid-template-rows: auto 1fr;
	}

	:global(body) {
		@apply min-h-screen p-4 sm:p-8 flex;
	}

</style>