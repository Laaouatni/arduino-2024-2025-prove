<script lang="ts">
  let isLedOn = $state(true);

  $effect(() => {
    const url = `http://192.168.163.49/led${isLedOn ? "On" : "Off"}`
    fetch(url);
  });
</script>

<main class="p-2">
  <input type="checkbox" bind:checked={isLedOn} />
  <p>{isLedOn}</p>
</main>
