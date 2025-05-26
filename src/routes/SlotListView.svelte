<script lang="ts">
  import type { SlotList } from "$lib/types";
  import SlotView from "./SlotView.svelte";

  let { slotlist }: { slotlist: SlotList } = $props();

  let dtext = $state("");

  function onDragOver(
    e: DragEvent & {
      currentTarget: EventTarget & HTMLSpanElement;
    },
  ) {
    if (e.dataTransfer) {
      const idx = parseInt(e.dataTransfer.getData("text/index"));
      e.preventDefault();
      e.dataTransfer.dropEffect = "move";

      const h = e.currentTarget.clientHeight;
      const tidx = e.currentTarget.tabIndex;
      dtext = `pos: ox=${e.offsetX}, oy=${e.offsetY}, ch=${h}, idx=${idx} tidx=${tidx}`;
    }
  }
</script>

<p>{dtext}</p>
<ol>
  {#each slotlist as slot, i}
    <li
      draggable="true"
      ondragstart={(e) => {
        if (e.dataTransfer) {
          e.dataTransfer.setData("text/index", i.toString());
          e.dataTransfer.setData("text/plain", JSON.stringify(slot));
        }
      }}
    >
      <span
        class="mark"
        role="row"
        tabindex={i}
        aria-dropeffect="move"
        ondragenter={onDragOver}
        ondragover={onDragOver}>Button {i + 1}</span
      >
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
