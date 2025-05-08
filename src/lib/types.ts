export type Action = {
  type:
    | "print"
    | "press"
    | "release"
    | "write"
    | "pressID"
    | "releaseID"
    | "writeID"
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
