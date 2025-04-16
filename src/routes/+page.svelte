<script lang="ts">
  import { OkSerial, type SlotList } from "$lib/ok_serial.svelte";

  const ok = new OkSerial();
  ok.reloadPorts();

  let slotList: SlotList | null = $state(null);

  async function connect(port: SerialPort) {
    try {
      await ok.openPort(port);
      slotList = await ok.getList();
    } catch (e) {
      console.error(e);
    }
  }
</script>

<h1>Welcome to SvelteKit</h1>
<hr />
<div>
  <h2>ports</h2>
  <ul>
    {#each ok.ports as port}
      <li>
        <pre><code>{JSON.stringify(port.getInfo())}</code></pre>
        {#if port == ok.currentPort}
          <span>connected</span>
          <button onclick={() => ok.close()}>disconnect</button>
        {:else}
          <button onclick={() => connect(port)}>connect</button>
        {/if}
      </li>
    {/each}
  </ul>
</div>
<hr />
<div>
  <button onclick={() => ok.requestPort()}>request</button>
</div>
<hr />
{#if slotList && ok.currentPort}
  <pre><code>{JSON.stringify(slotList)}</code></pre>
{/if}

<pre><code>{ok.message}</code></pre>
