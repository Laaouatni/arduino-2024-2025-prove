<script lang="ts">
  let isLedOn = $state(true);
  const esp32adress = "192.168.21.49";

  $effect(() => {
    const choosedPath = `digitalWrite`;
    const url = `http://${esp32adress}/${choosedPath}/2/${isLedOn}`;
    fetch(url);
  });
</script>

<main class="p-2">
  <input type="checkbox" bind:checked={isLedOn} />
  <p>{isLedOn}</p>
</main>
