<script lang="ts">
	import '../../app.postcss';
	let { children, data } = $props();
  import numConvert from "number-to-words";

	const showSidebar = true;
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
		{#if data.user.streak}	
		<div class="flex-none">
			<div class="badge mr-4 py-3"
			class:badge-success={data.lastMessage}
			class:badge-warning={!data.lastMessage}
			>
				🔥 {data.user.streak} day{data.user.streak > 1 ? 's' : ''}
			</div>
		</div>	
		{/if}
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
		<div class="sidebar w-full basis-80 lg:basis-96 col-span-1 bg-base-100 text-base-content card card-bordered border-black grow xl:grow-0 order-1 xl:order-none">
			<div class="card-body">
				<h1 class="daydream daydream-lg">Community</h1>

				<div>
					<p class="text-[12px]">
						<span class="capitalize">
							{numConvert.toWords(data.userList.length)}
						</span>
						folk have logged in and gained access, and {numConvert.toWords(
							data.userList.filter((u) => u[1]).length
						)} 
						{data.userList.filter((u) => u[1]).length === 1 ? 'has' : 'have'}
						 sent a message today:
					</p>
					<ul class="list-inside mt-2 text-[12px]">
						{#each data.userList.sort((a,b)=> b[2] - a[2]) as user}
							<li class="flex items-center w-full mt-3 gap-2">
								<span
									class="checkbox checkbox-sm"
									aria-hidden="true"
									aria-checked={user[1]}
								></span>
								<span title="{user[0]} - {user[1] ? 'has posted' : 'has not posted'}">
									{user[0]}
									{#if user[1]}
										<span class="font-sans"> 🎉 </span>
									{/if}
								</span>
								<div class="grow"></div>
								{#if user[2]}
									<!-- Current Streak -->
									<span class="badge badge-success">
										{user[2]}
										<span class="font-sans ml-2"> 🔥 </span>
									</span>
								{/if}
							</li>
						{/each}
					</ul>
				</div>
			</div>
		</div>
		{/if}
		<div class="grow shrink basis-[768px] min-w-64">
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