<script lang="ts">
  import { onDestroy, onMount } from "svelte";
  import type * as Monaco from "monaco-editor/esm/vs/editor/editor.api";
  import { browser } from "$app/environment";
  let editor: Monaco.editor.IStandaloneCodeEditor;
  let monaco: typeof Monaco;
  let editorContainer: HTMLElement;
  import schema from "$lib/slotlist_schema.json";
  import type { SlotList } from "$lib/types";

  let {
    editingSlots,
    onsave,
    oncancel,
  }: {
    editingSlots: SlotList;
    onsave: (value: string) => void;
    oncancel: () => void;
  } = $props();

  if (browser) {
    onMount(async () => {
      monaco = (await import("./monaco")).default;
      const modelUri = monaco.Uri.parse("a://okeypad.config.json");
      monaco.languages.json.jsonDefaults.setDiagnosticsOptions({
        validate: true,
        schemas: [
          {
            uri: "",
            fileMatch: [modelUri.toString()],
            schema,
          },
        ],
      });
      editor = monaco.editor.create(editorContainer, {
        theme: "vs-dark",
      });
      const model = monaco.editor.createModel(
        JSON.stringify(editingSlots, null, 2),
        "json",
        modelUri
      );
      editor.setModel(model);
    });

    onDestroy(() => {
      editor.getValue();
      monaco?.editor.getModels().forEach((model) => model.dispose());
      editor?.dispose();
    });
  }
</script>

<nav>
  <span>ボタン設定</span>
  <div>
    <button onclick={() => onsave(editor.getValue())}>保存</button>
    <button onclick={() => oncancel()}>キャンセル</button>
  </div>
</nav>
<div class="container" bind:this={editorContainer}></div>
<div></div>

<style>
  .container {
    width: 100%;
    height: calc(100vh - 180px);
  }
  nav {
    display: flex;
    justify-content: space-between;
    align-items: flex-start;
    margin: 3px 0 20px 0;
  }
  nav > span {
    color: white;
    font-size: larger;
  }
  nav button {
    color: white;
    background-color: #1e1e1e;
    border: 3px #1e1e1e solid;
  }

  nav button:hover {
    cursor: pointer;
    background-color: #303030;
    border: 3px #777 ridge;
  }
</style>
