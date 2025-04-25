<script lang="ts">
    import { browser } from "$app/environment";

    const ITEM_KEY = "pg_test_value";
    let ts_value: string | null = $state(null);

    if (browser) {
        ts_value = localStorage.getItem(ITEM_KEY);
        $effect(() => {
            if (ts_value) {
                localStorage.setItem(ITEM_KEY, ts_value);
            }
        });
    }
</script>

<h1>hello</h1>
<p>{ts_value}</p>
<input type="text" bind:value={ts_value} />
