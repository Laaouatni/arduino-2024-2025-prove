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
  <div class="flex w-full group h-full gap-2">
    {#each pianoButtons as thisPianoButton}
      <button class="flex-grow active:flex-[8] rounded-lg bg-slate-200 p-2 grid place-items-center font-bold hover:shadow-lg transition-all active:bg-blue-500 text-[3vw] active:text-[15vw]">
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
