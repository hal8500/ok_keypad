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
<p>
  OkeyPadのキー設定をUSBシリアル経由で行うためのサイトです。<br />
  初めて機器を設定する場合は、機器をUSBケーブルで接続し、「シリアルポート接続要求」ボタンを押してください。<br />
  一度接続要求された機器はリストに表示されるようになります。「接続」ボタンを押してください。<br />
</p>
<hr />
<div>
  <h2>シリアルポート設定</h2>
  <div>
    <button onclick={() => ok.requestPort()}>シリアルポート接続要求</button>
  </div>
  <ul>
    {#each ok.ports as port}
      <li>
        <pre><code>{JSON.stringify(port.getInfo())}</code></pre>
        {#if port == ok.currentPort}
          <span>connected</span>
          <button onclick={() => ok.close()}>切断</button>
        {:else}
          <button onclick={() => connect(port)}>接続</button>
        {/if}
      </li>
    {/each}
  </ul>
</div>


{#if ok.slots}
<hr />

<h2>ボタン設定</h2>

  <SlotListView slotlist={ok.slots} />

{/if}

<hr>
<h2>デバッグ情報</h2>
<pre><code>{ok.message}</code></pre>
<pre><code>{JSON.stringify(ok.slots)}</code></pre>

<style>
  .help_req {
    font-size: smaller;
    color: rgba(0,0,0,0.6)
  }
</style>