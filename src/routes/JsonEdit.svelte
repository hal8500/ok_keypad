<script lang="ts">
  import { onDestroy, onMount } from "svelte";
  import type * as Monaco from "monaco-editor/esm/vs/editor/editor.api";
  import { browser } from "$app/environment";
  import { type SlotList } from "$lib/ok_serial.svelte";
  let editor: Monaco.editor.IStandaloneCodeEditor;
  let monaco: typeof Monaco;
  let editorContainer: HTMLElement;

  const schema = {
    type: "array",
    minItems: 1,
    maxItems: 9,
    items: { anyOf: [{ type: "object" }, { type: "string" }] },
  };

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
            uri: "https://okeypad.config/config.json",
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

<div class="container" bind:this={editorContainer}></div>
<div>
  <button onclick={() => onsave(editor.getValue())}>保存</button>
  <button onclick={() => oncancel()}>キャンセル</button>
</div>

<style>
  .container {
    width: 100%;
    height: 600px;
  }
</style>
