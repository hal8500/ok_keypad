export type MacroCommand = {
  name: string;
  acts: [
    {
      type: "print" | "press" | "release" | "releaseAll" | "delay" | "move";
      arg: number | undefined;
      x: number | undefined;
      y: number | undefined;
    }
  ];
};
export type SlotCommand = string | MacroCommand;
export type SlotList = SlotCommand[];

export class OkSerial {
  ports: SerialPort[] = $state([]);
  currentPort: SerialPort | null = $state(null);
  message: string = $state("");

  async reloadPorts() {
    if (!navigator.serial) return;
    const v = await navigator.serial.getPorts();
    this.ports = v;
  }

  async requestPort() {
    const port = await navigator.serial.requestPort();
    this.message = JSON.stringify(port.getInfo());
    await this.reloadPorts();
  }

  async openPort(port: SerialPort) {
    if (port == this.currentPort) return;

    await this.close();

    try {
      await port.open({ baudRate: 9600 });
      this.currentPort = port;
      this.message = "port connected";
    } catch (e) {
      console.log(e);
      this.message = "failed to connect serial port";
    }
  }

  async close() {
    if (this.currentPort == null) return;
    try {
      await this.currentPort.close();
    } catch (e) {
      console.log(e);
    }
    this.currentPort = null;
  }

  async fetch(text: string): Promise<string | null> {
    if (this.currentPort === null) return null;

    const textDecoder = new TextDecoderStream();
    const readableStreamClosed = this.currentPort.readable.pipeTo(
      textDecoder.writable
    );
    const reader = textDecoder.readable.getReader();

    const textEncoder = new TextEncoderStream();
    const writableStreamClosed = textEncoder.readable.pipeTo(
      this.currentPort.writable
    );
    const writer = textEncoder.writable.getWriter();
    await writer.write(text);
    writer.releaseLock();

    const readUntilClosed = async () => {
      let res = "";
      let i = 0;
      while (true) {
        const response = await reader.read();
        console.log(`read[${i++}] = ${response.value}`);
        if (response.value) {
          res += response.value;
        }
        if (response.done) {
          break;
        }
      }
      reader.releaseLock();
      await this.close();
      return res;
    };

    const readtask = readUntilClosed();
    await delay(100);
    try {
      await reader.cancel();
    } catch (e) {
      console.log(e);
    }

    return await readtask;
  }

  async getList(): Promise<SlotList | null> {
    if (this.currentPort === null) return null;
    this.message = "reading list";

    const r = await this.fetch("list_json\n");

    if (r) {
      console.log(r);
      let j = r.slice(r.indexOf("\n"));
      const slotlist = JSON.parse(j) as SlotList;
      return slotlist;
    }
    return null;
  }
}

const delay = (msec: number) => {
  return new Promise((resolve) => setTimeout(resolve, msec));
};
