<script lang="ts">
  import "./app.css";

  const esp32adress = "192.168.21.49";

  let pianoButtons: { key: string; value: boolean }[] = $state(
    [
      { key: "DO" },
      { key: "RE" },
      { key: "MI" },
      { key: "FA" },
      { key: "SOL" },
      { key: "LA" },
      { key: "SI" },
      { key: "DO" },
    ].map((thisObj) => {
      return { ...thisObj, value: false };
    }),
  );

  console.log(pianoButtons);

  // $effect(() => {
  //   const choosedPath = `digitalWrite`;
  //   const url = `http://${esp32adress}/${choosedPath}/2/${Number(isLedOn)}`;
  //   fetch(url, { method: "POST" });
  // });
</script>

<main class="p-4 grid place-items-center">
  <div class="flex w-full group h-full">
    {#each pianoButtons as thisPianoButton}
      <button class="flex-1 rounded-lg bg-slate-200 p-2 grid place-items-center font-bold hover:scale-x-105 hover:shadow-lg transition mx-1 active:mx-5 active:scale-x-150 active:bg-blue-500">
        {thisPianoButton.key}
      </button>
    {/each}
  </div>
</main>

<style>
  :global(body, html, #app, main) {
    @apply h-full;
  }
</style>
