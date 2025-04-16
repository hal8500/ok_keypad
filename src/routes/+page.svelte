<script lang="ts">
  let ports: SerialPort[] = $state([]);
  let message: string = $state("no message");
  let connectedPort: SerialPort | null = $state(null);

  reloadPorts();

  async function reloadPorts() {
    if (!navigator.serial) return;
    const v = await navigator.serial.getPorts();
    ports = v;
  }

  async function requestPort() {
    message = "requested";
    const port = await navigator.serial.requestPort();
    message = JSON.stringify(port.getInfo());
    await reloadPorts();
  }

  async function openPort(port: SerialPort) {
    if (port == connectedPort) return;

    if (connectedPort !== null) {
      try {
        await connectedPort.close();
      } catch (e) {
        console.log(e);
      }
    }
    try {
      await port.open({ baudRate: 9600 });
      connectedPort = port;
      message = "port connected";
    } catch (e) {
      console.log(e);
    }
  }

  async function getList() {
    if (connectedPort === null) return;
    message = "reading list";

    const textDecoder = new TextDecoderStream();
    const readableStreamClosed = connectedPort.readable.pipeTo(
      textDecoder.writable
    );
    const reader = textDecoder.readable.getReader();

    const textEncoder = new TextEncoderStream();
    const writableStreamClosed = textEncoder.readable.pipeTo(
      connectedPort.writable
    );
    const writer = textEncoder.writable.getWriter();

    writer.write();
  }
</script>

<h1>Welcome to SvelteKit</h1>
<hr />
<div>
  <h2>ports</h2>
  <ul>
    {#each ports as port}
      <li>
        <pre><code>{JSON.stringify(port.getInfo())}</code></pre>
        <button onclick={() => openPort(port)}>connect</button>
      </li>
    {/each}
  </ul>
</div>
<hr />
<div>
  <button onclick={requestPort}>request</button>
</div>

<pre><code>{message}</code></pre>
