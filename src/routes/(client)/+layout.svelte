<script lang="ts">
	import '../../app.postcss';
	let { children, data } = $props();

	const showSidebar = false;
</script>

<div class="pageLayout">

	<div class="navbar bg-base-100 flex-wrap text-base-content border border-black rounded-box">
		<div class="flex-1">
			<a href="/" class="btn btn-ghost text-lg hidden sm:flex max-w-full h-auto text-left">Royal Society of Besties</a>
			<a href="/" class="btn btn-ghost text-lg flex sm:hidden">RSB</a>
		</div>
		<div class="flex-none">
			<ul class="menu menu-horizontal px-1">
				<li><a href="/device">Device Manager</a></li>
			</ul>
			</div>	
		<div class="dropdown dropdown-end">
      <div tabindex="0" role="button" class="btn btn-ghost btn-circle avatar">
        <div class="w-10 rounded-full">
          <img
            alt={data.account?.name}
            src={data.account?.image} />
        </div>
      </div>
      <!-- svelte-ignore a11y_no_noninteractive_tabindex -->
      <ul
        tabindex="0"
        class="menu menu-sm dropdown-content bg-base-100 rounded-box z-[1] mt-3 w-52 p-2 shadow text-sm">
        <li><a href="/auth/signout">Logout</a></li>
      </ul>
    </div>

	</div>
	<div class="flex flex-wrap mt-4 gap-4" style:max-width="calc(100vw - 2rem)">
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