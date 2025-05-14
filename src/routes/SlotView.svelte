<script lang="ts">
  import {
    explainAction,
    isMacroCommand,
    type Actions,
    type SlotCommand,
  } from "$lib/types";

  let { slot }: { slot: SlotCommand } = $props();
</script>

{#if isMacroCommand(slot)}
  <div>
    <span class="name">{slot.name}</span>
    {#if "description" in slot}
      <p class="desc">{slot.description}</p>
    {/if}
  </div>
  <ol>
    {#each slot.actions as action}
      <li>{@render renderAction(action)}</li>
    {/each}
  </ol>
{:else if Array.isArray(slot)}
  <ol>
    {#each slot as action}
      <li>{@render renderAction(action)}</li>
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
