<script lang="ts">
  import type { Action, SlotCommand } from "$lib/ok_serial.svelte";

  let { slot }: { slot: SlotCommand } = $props();
</script>

{#if typeof slot == "string"}
  {@render renderAction({ type: "print", arg: slot })}
{:else}
  <div>
    <span class="type">Name</span>
    <span>:</span>
    <span class="value">{slot.name}</span>
    <ol>
      {#each slot.acts as act}
        <li>{@render renderAction(act)}</li>
      {/each}
    </ol>
  </div>
{/if}

{#snippet renderAction(action: Action)}
  <span class="type">{action.type}</span>
  {#if action.arg}
    <span>:</span>
    <span class="value">{JSON.stringify(action.arg)}</span>
  {/if}
{/snippet}

<style>
  .type {
    font-family: monospace;
    color: rgb(10, 81, 139);
  }
  .value {
    font-family: monospace;
    color: rgb(121, 79, 2);
  }
</style>
