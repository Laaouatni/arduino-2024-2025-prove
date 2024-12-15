<script lang="ts">
  let isLedOn = $state(true);
  const esp32adress = "192.168.21.49";

  $effect(() => {
    const choosedPath = `led${isLedOn ? "On" : "Off"}`;
    const url = `http://${esp32adress}/${choosedPath}`
    fetch(url);
  });
</script>

<main class="p-2">
  <input type="checkbox" bind:checked={isLedOn} />
  <p>{isLedOn}</p>
</main>
