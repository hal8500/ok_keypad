<script lang="ts">
    const slotTypes = [
        { id: "type", text: "文字入力" },
        { id: "button", text: "ボタン割り当て" },
        { id: "click", text: "マウスクリック" },
        { id: "macro", text: "マクロ" },
    ];
    let selectedSlotType = $state();
</script>

<div>
    <div>
        <span>機能</span>
        <select bind:value={selectedSlotType}>
            {#each slotTypes as slotType}
                <option value={slotType}>{slotType.text}</option>
            {/each}
        </select>
    </div>
</div>
