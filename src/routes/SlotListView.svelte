<script lang="ts">
  import type { SlotList } from "$lib/types";
  import SlotView from "./SlotView.svelte";

  let { slotlist }: { slotlist: SlotList } = $props();
</script>

<ol>
  {#each slotlist as slot, i}
    <li>
      <span class="mark">Button {i + 1}</span>
      <div class="slot_body"><SlotView {slot}></SlotView></div>
    </li>
  {/each}
</ol>

<style>
  ol {
    list-style-type: none;
  }

  li {
    margin: 4px 4px;
    padding: 3px 10px;
    display: flex;
  }

  .mark {
    border: 1px solid rgba(0, 0, 0, 0.3);
    border-radius: 4px 0px 0px 4px;
    padding: 1px 4px;
    background-color: rgb(247, 239, 208);
  }

  .slot_body {
    margin-left: 0px;
    background-color: white;
    border: 1px solid rgba(0, 0, 0, 0.3);
    border-left: none;
    border-radius: 0px 4px 4px 0px;
    padding: 1px 8px;
  }
</style>
