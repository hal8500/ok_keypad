<script lang="ts">
  import { OkSerial, type SlotList } from "$lib/ok_serial.svelte";
  import SlotListView from "./SlotListView.svelte";

  const ok = new OkSerial();
  ok.reloadPorts();

  async function connect(port: SerialPort) {
    try {
      await ok.openPort(port);
      await ok.requestList();
    } catch (e) {
      console.error(e);
    }
  }
</script>

<h1>OkeyPad configurator</h1>
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

{#if ok.slots}
  <SlotListView slotlist={ok.slots} />
{/if}

<pre><code>{ok.message}</code></pre>
<pre><code>{JSON.stringify(ok.slots)}</code></pre>
