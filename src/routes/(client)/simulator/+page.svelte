<script lang="ts">
  import FrontFace from "$lib/components/preview/front-face.svelte";

  const { data } = $props();
</script>

<FrontFace page={0} live={true} userData={data.user} />
