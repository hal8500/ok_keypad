export type Action = {
  type:
    | "print"
    | "press"
    | "release"
    | "releaseAll"
    | "delay"
    | "move"
    | "click";
  arg?: string | number;
  x?: number;
  y?: number;
};

export type MacroCommand = {
  name?: string;
  actions: Action[];
};

export type SlotCommand = string | MacroCommand;
export type SlotList = SlotCommand[];

class LineBreakTransformer implements Transformer<string, string> {
  chunks: string;

  constructor() {
    this.chunks = "";
  }

  transform(chunk: string, controller: TransformStreamDefaultController) {
    this.chunks += chunk;
    const lines = this.chunks.split("\r\n");
    this.chunks = lines.pop() ?? "";
    lines.forEach((line) => controller.enqueue(line));
  }

  flush(controller: TransformStreamDefaultController) {
    controller.enqueue(this.chunks);
  }
}

export const SLOTS_DEFAULT: SlotList = [
  "aiueo",
  "test@example.com",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  {
    name: "macro",
    actions: [
      { type: "press", arg: 114 },
      { type: "delay", arg: 1000 },
      { type: "releaseAll" },
      { type: "print", arg: "mcr" },
    ],
  },
];

function isSlotList(json: any): json is SlotList {
  if (!("length" in json)) {
    return false;
  }
  if (json.length != 9) {
    return false;
  }
  for (const s of json) {
    if (typeof s == "string") {
      continue;
    }
    if (!("actions" in s) || !("length" in s.actions)) {
      return false;
    }
    for (const a of s.actions) {
      if (!("type" in a)) {
        return false;
      }
    }
  }
  return true;
}

export class OkSerial {
  ports: SerialPort[] = $state.raw([]);
  currentPort: SerialPort | null = $state.raw(null);
  message: string = $state("");
  slots: SlotList | null = $state(null);
  editingSlots: SlotList = $state(SLOTS_DEFAULT);
  edited: boolean = $state(false);
  writer: WritableStreamDefaultWriter<string> | null = null;

  closer: (() => Promise<void>) | null = null;

  async reloadPorts() {
    if (!navigator.serial) return;
    const v = await navigator.serial.getPorts();
    this.ports = v;
  }

  async requestPort() {
    const port = await navigator.serial.requestPort();
    this.message = JSON.stringify(port.getInfo());
    await this.openPort(port);
    await this.requestList();
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
      return;
    }

    const textDecoder = new TextDecoderStream();
    const readableStreamClosed = this.currentPort.readable.pipeTo(
      textDecoder.writable
    );
    const reader = textDecoder.readable
      .pipeThrough(new TransformStream(new LineBreakTransformer()))
      .getReader();

    (async () => {
      while (true) {
        const { value, done } = await reader.read();
        if (value) {
          this.onRecieve(value);
        }
        if (done) {
          reader.releaseLock();
          break;
        }
      }
    })();

    const textEncoder = new TextEncoderStream();
    const writableStreamClosed = textEncoder.readable.pipeTo(
      this.currentPort.writable
    );
    this.writer = textEncoder.writable.getWriter();

    this.closer = async () => {
      reader.cancel();
      await readableStreamClosed.catch(() => {
        /* Ignore the error */
      });

      this.writer?.close();
      await writableStreamClosed;

      await port.close();
    };
  }

  async close() {
    if (this.currentPort == null || this.closer == null) return;
    try {
      await this.closer();
    } catch (e) {
      console.log(e);
    }
    this.currentPort = null;
    this.writer = null;
    this.slots = null;
    this.edited = false;
    this.closer = null;
  }

  async onRecieve(line: string) {
    console.log("> " + line);
    if (!line.startsWith("[") && !line.startsWith("{")) {
      return;
    }
    try {
      const j = JSON.parse(line);
      if (isSlotList(j)) {
        this.slots = j;
      } else {
        console.log("invalid items");
        this.slots = null;
      }
    } catch (e) {
      console.log("failed to parse");
      console.log(e);
      this.slots = null;
    }
    this.edited = this.isDirty();
  }

  async send(text: string) {
    if (this.writer === null) return null;
    console.log("< " + text);
    await this.writer.write(text);
  }

  async requestList() {
    if (this.currentPort === null) return null;
    this.message = "reading list";
    const r = await this.send("list_json\n");
  }

  loadSlotsToEditing() {
    if (this.slots) {
      this.editingSlots = $state.snapshot(this.slots);
      this.edited = false;
    }
  }

  async saveSlotsFromEditing() {
    if (this.slots) {
      const b = JSON.stringify(this.editingSlots);
      await this.send(`set_json ${b} \n`);
      await this.send("list_json \n");
      // list_jsonの結果でthis.slotsが更新される
    }
  }

  updateEditing(value: string) {
    try {
      const v = JSON.parse(value);
      this.editingSlots = v;
      this.edited = this.isDirty();
    } catch {}
  }

  isDirty() {
    if (this.slots) {
      const a = JSON.stringify(this.slots);
      const b = JSON.stringify(this.editingSlots);
      return a != b;
    }
    return false;
  }
}

const delay = (msec: number) => {
  return new Promise((resolve) => setTimeout(resolve, msec));
};
