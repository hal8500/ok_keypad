<script lang="ts">
  import type { SlotList } from "$lib/types";
  import SlotView from "./SlotView.svelte";

  let { slotlist }: { slotlist: SlotList } = $props();

  let dtext = $state("");
  let draggingIndex = 0;

  function calcDropIndex(
    source: number,
    target: number,
    e: DragEvent & {
      currentTarget: EventTarget & HTMLLIElement;
    },
  ) {
    // 自分自身にはドロップしない
    if (source == target) return -1;

    // 後ろに移動する場合は－１
    if (source < target) {
      target -= 1;
    }

    const r = e.currentTarget.getBoundingClientRect();
    const y = e.clientY - r.top;

    // 要素の上半分なら手前に、下半分なら次に挿入する。
    if (y > r.height / 2) {
      target += 1;
    }

    if (source == target) return -1;
    return target;
  }
</script>

<p>{dtext}</p>
<ol>
  {#each slotlist as slot, i}
    {@const drag = (
      e: DragEvent & {
        currentTarget: EventTarget & HTMLLIElement;
      },
    ) => {
      if (e.dataTransfer) {
        const tidx = calcDropIndex(draggingIndex, i, e);
        if (tidx != -1) {
          e.preventDefault();
          e.dataTransfer.dropEffect = "move";
        }
      }
    }}
    <li
      draggable="true"
      ondragstart={(e) => {
        if (e.dataTransfer) {
          e.dataTransfer.setData("index", i.toString());
          draggingIndex = i;
          e.dataTransfer.setData("text/plain", JSON.stringify(slot));
        }
      }}
      ondragenter={drag}
      ondragover={drag}
      ondrop={(e) => {
        if (e.dataTransfer) {
          const tidx = calcDropIndex(draggingIndex, i, e);
          if (tidx != -1) {
            e.preventDefault();
            const m = slotlist.splice(draggingIndex, 1)[0];
            slotlist.splice(tidx, 0, m);

            e.dataTransfer.dropEffect = "move";
          }
        }
      }}
    >
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
