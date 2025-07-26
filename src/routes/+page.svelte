<script lang="ts">
  import { OkSerial } from "$lib/ok_serial.svelte";
  import { onMount, onDestroy } from "svelte";
  import JsonEdit from "./JsonEdit.svelte";
  import SlotListView from "./SlotListView.svelte";

  const ok = new OkSerial();
  let showEditor = $state(false);
  let dialog: HTMLDialogElement;

  async function connect(port: SerialPort) {
    try {
      await ok.openPort(port);
      await ok.requestList();
    } catch (e) {
      console.error(e);
    }
  }

  onMount(() => {
    ok.reloadPorts();

    navigator.serial.addEventListener("connect", (e) => {
      ok.reloadPorts();
    });

    navigator.serial.addEventListener("disconnect", async (e) => {
      if (e.target == ok.currentPort) {
        await ok.close();
      }
      await ok.reloadPorts();
    });
  });

  onDestroy(() => {
    ok.close();
  });
</script>

<h1>OKeyPad 設定</h1>
<p>
  OKeyPadのキー設定を行うためのサイトです。<br />
  OkeypadとPCをUSBケーブルで接続し、「シリアルポート接続要求」ボタンを押してください。<br
  />
  一度接続要求された機器はリストに表示されるようになります。リストにある場合は「接続」ボタンを押してください。<br
  />
</p>
<hr />
<div class="debuginfo">
  <h2>デバッグ情報</h2>
  <pre><code>{ok.message}</code></pre>
</div>
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
          <button onclick={() => ok.close()}>切断</button>
          <span>connected</span>
        {:else}
          <button onclick={() => connect(port)}>接続</button>
        {/if}
      </li>
    {/each}
  </ul>
</div>

<hr />
<div class="menu">
  <button disabled={ok.slots == null} onclick={() => ok.loadSlotsToEditing()}
    >▶ 機器の設定を取り込む</button
  >
  <button disabled={ok.slots == null} onclick={() => ok.saveSlotsFromEditing()}
    >◀ 設定を機器に書き込む</button
  >
  <button
    onclick={() => {
      dialog.showModal();
      showEditor = true;
    }}
  >
    JSON編集
  </button>
</div>
<div class="container">
  <div class="item">
    <h2>現在のボタン設定</h2>
    {#if ok.slots}
      <SlotListView slotlist={ok.slots} draggable={false} />
    {:else}
      <p>未接続</p>
    {/if}
  </div>
  <div class="item">
    <h2>編集中の設定</h2>
    <SlotListView slotlist={ok.editingSlots} draggable={true} />
  </div>
</div>

<hr />

<dialog
  bind:this={dialog}
  onclose={() => {
    ok.message = "closed";
    showEditor = false;
  }}
>
  {#if showEditor}
    <JsonEdit
      editingSlots={ok.editingSlots}
      onsave={(value) => {
        ok.updateEditing(value);
        dialog.close();
        // TODO: valueが正しい形式でない場合の処理
      }}
      oncancel={() => {
        dialog.close();
      }}
    ></JsonEdit>
  {/if}
</dialog>

<style>
  .container {
    display: flex;
    flex-wrap: wrap;
  }
  .menu {
    margin: 1px;
    padding: 5px;
  }
  .item {
    flex-grow: 1;
    border: solid 1px black;
    border-radius: 5px;
    margin: 5px;
    padding: 5px;
  }
  .debuginfo {
    width: 100%;
    overflow: auto;
  }
  dialog {
    width: 80%;
    border-radius: 9px;
    border: 1px #1e1e1e solid;
    background-color: #1e1e1e;
  }
</style>
