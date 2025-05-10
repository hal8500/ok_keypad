<script lang="ts">
  import {
    explainAction,
    isMacroDescription,
    type Actions,
    type SlotCommand,
  } from "$lib/types";

  let { slot }: { slot: SlotCommand } = $props();
</script>

{#if Array.isArray(slot)}
  {#if isMacroDescription(slot[0])}
    {@const desc = slot[0]}
    <div>
      <span class="name">{desc.name}</span>
      {#if "description" in desc}
        <p class="desc">{desc.description}</p>
      {/if}
    </div>
  {/if}
  <ol>
    {#each slot as action}
      {#if !isMacroDescription(action)}
        <li>{@render renderAction(action)}</li>
      {/if}
    {/each}
  </ol>
{:else}
  {@render renderAction(slot)}
{/if}

{#snippet renderAction(action: Actions)}
  {@const { name, arg, type } = explainAction(action)}
  <span class="type">{name}</span>
  <span class={[type, "value"]}>{arg}</span>
{/snippet}

<style>
  .type {
    font-family: monospace;
    color: rgb(10, 81, 139);
  }
  .type::after {
    content: ":";
  }

  .name {
    font-weight: 500;
    color: rgb(18, 84, 207);
  }
  .desc {
    color: saddlebrown;
    font-weight: 400;
    font-size: small;
    margin: 0.2em;
    max-width: 400px;
  }

  .value {
    font-family: monospace;
    color: rgb(121, 79, 2);
  }

  .text::before,
  .text::after {
    content: '"';
  }

  .ms::after {
    content: "ms";
  }
  .key {
    border: solid 1px gray;
    background-color: rgb(243, 243, 243);
    border-radius: 3px;
    padding: 0 0.3em;
  }
  .mouse {
    border: solid 1px gray;
    background-color: rgb(66, 66, 66);
    color: white;
    border-radius: 5px;
    padding: 0 0.3em;
  }
</style>
