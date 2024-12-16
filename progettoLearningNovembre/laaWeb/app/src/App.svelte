<script lang="ts">
  let isLedOn = $state(true);
  const esp32adress = "192.168.21.49";

  $effect(() => {
    const choosedPath = `digitalWrite`;
    const url = `http://${esp32adress}/${choosedPath}`
    fetch(url, {
      method: "POST",
      body: {
        pin: {
          id: 5,
          value: 1
        }
      }
    });
  });
</script>

<main class="p-2">
  <input type="checkbox" bind:checked={isLedOn} />
  <p>{isLedOn}</p>
</main>
