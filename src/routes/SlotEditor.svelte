<script lang="ts">
    import { KEY_TABLE } from '$lib/types';

    const slotTypes = [
        { id: "type", text: "文字入力" },
        { id: "button", text: "ボタン割り当て" },
        { id: "click", text: "マウスクリック" },
        { id: "macro", text: "マクロ" },
    ];
    
    let selectedSlotType = $state("type");

    let keyParam = $state("");

    function validateKey(key: string) : boolean {
        if (key in KEY_TABLE) return true;
        if (key.length == 1 && key.charCodeAt(0) < 128) return true;
        return false;
    } 
</script>

<div>
    {@render roleSelect2()}
    <span>選択した役割: {selectedSlotType}</span>
    {#if selectedSlotType == "type"}
    {@render keyParameter()}
    {/if}
</div>

{#snippet roleSelect1()}
    <div>
        <span>役割</span>
        <select bind:value={selectedSlotType}>
            {#each slotTypes as slotType}
                <option value={slotType}>{slotType.text}</option>
            {/each}
        </select>
    </div>
{/snippet}

{#snippet roleSelect2()}
    <div>
        <span>役割</span>
        {#each slotTypes as slotType}
            <label>
                <input type="radio" name="role" value={slotType.id} bind:group={selectedSlotType} />
                {slotType.text}
            </label>
        {/each}
    </div>
{/snippet}

{#snippet keyParameter()}
    <div>
        {#if validateKey(keyParam)}
        <code>o</code>
        {:else}
        <code>x</code>
        {/if}
        <input bind:value={keyParam} list="keycodes">
        
    </div>
{/snippet}

<datalist id="keycodes">
    {#each Object.entries(KEY_TABLE) as key}
        <option value={key[0]} ></option>
    {/each}
</datalist>