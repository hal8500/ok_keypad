export type KeyIds =
  | "LEFT_CTRL"
  | "LEFT_SHIFT"
  | "LEFT_ALT"
  | "LEFT_GUI"
  | "RIGHT_CTRL"
  | "RIGHT_SHIFT"
  | "RIGHT_ALT"
  | "RIGHT_GUI"
  | "RETURN"
  | "ESC"
  | "BACKSPACE"
  | "TAB"
  | "CAPS_LOCK"
  | "PRINT_SCREEN"
  | "SCROLL_LOCK"
  | "PAUSE"
  | "INSERT"
  | "HOME"
  | "PAGE_UP"
  | "DELETE"
  | "END"
  | "PAGE_DOWN"
  | "RIGHT_ARROW"
  | "LEFT_ARROW"
  | "DOWN_ARROW"
  | "UP_ARROW"
  | "MENU"
  | "NUM_LOCK"
  | "KP_SLASH"
  | "KP_ASTERISK"
  | "KP_MINUS"
  | "KP_PLUS"
  | "KP_ENTER"
  | "KP_1"
  | "KP_2"
  | "KP_3"
  | "KP_4"
  | "KP_5"
  | "KP_6"
  | "KP_7"
  | "KP_8"
  | "KP_9"
  | "KP_0"
  | "KP_DOT"
  | "F1"
  | "F2"
  | "F3"
  | "F4"
  | "F5"
  | "F6"
  | "F7"
  | "F8"
  | "F9"
  | "F10"
  | "F11"
  | "F12"
  | "F13"
  | "F14"
  | "F15"
  | "F16"
  | "F17"
  | "F18"
  | "F19"
  | "F20"
  | "F21"
  | "F22"
  | "F23"
  | "F24";

/**
 * @minLength 1
 * @maxLength 1
 */
export type Char = string;

/**
 * 一連の文字列をタイプします
 */
export type TypeAction = {
  /**
   * 一連の文字列をタイプします
   */
  type: string;
};

/**
 * 指定されたキーを押して離します
 */
export type TapAction = {
  /**
   * 指定されたキーを押して離します
   */
  tap: Char;
};

/**
 * 指定されたキーを押して離します
 */
export type TapIdAction = {
  /**
   * 指定されたキーを押して離します
   */
  tap: KeyIds;
};

/**
 * 指定されたキーを押します
 */
export type PressAction = {
  /**
   * 指定されたキーを押します
   */
  press: Char;
};

/**
 * 指定されたキーを押します
 */
export type PressIdAction = {
  /**
   * 指定されたキーを押します
   */
  press: KeyIds;
};

/**
 * 指定されたキーを離します
 */
export type ReleaseAction = {
  /**
   * 指定されたキーを離します
   */
  release: Char;
};

/**
 * 指定されたキーを離します
 */
export type ReleaseIdAction = {
  /**
   * 指定されたキーを離します
   */
  release: KeyIds;
};

/**
 * 指定されたキーを離します
 */
export type ReleaseAllAction = {
  /**
   * 指定されたキーを離します
   */
  release: "ALL";
};

/**
 * 指定されたミリ秒だけ、動作を停止します
 */
export type DelayAction = {
  /**
   * 指定されたミリ秒だけ、動作を停止します
   */
  delay: number;
};

/**
 * マウスの指定されたボタンをクリックします
 */
export type MouseClickAction = {
  /**
   * マウスの指定されたボタンをクリックします
   */
  click: "LEFT" | "RIGHT" | "MIDDLE";
};

/**
 * マウスを指定された量だけ移動します
 */
export type MouseMoveAction = {
  /**
   * マウスを指定された量だけ移動します
   */
  move: { x: number; y: number };
};

/**
 * ボタンを指定されたキーとして機能させます
 */
export type ButtonAssign = {
  /**
   * ボタンを指定されたキーとして機能させます
   */
  button: Char;
};

/**
 * ボタンを指定されたキーとして機能させます
 */
export type ButtonIdAssign = {
  /**
   * ボタンを指定されたキーとして機能させます
   */
  button: KeyIds;
};

export type SingleActions =
  | TypeAction
  | ButtonAssign
  | ButtonIdAssign
  | string
  | MouseClickAction;

export type MacroActions =
  | TypeAction
  | TapAction
  | TapIdAction
  | PressAction
  | PressIdAction
  | ReleaseAction
  | ReleaseIdAction
  | ReleaseAllAction
  | DelayAction
  | MouseClickAction
  | MouseMoveAction
  | string
  | number;

export type MacroCommand = {
  /**
   * マクロの名称を記述します
   */
  name: string;
  /**
   * マクロの用途を記述します
   */
  description?: string;

  /**
   * マクロの内容を定義します
   */
  actions: MacroActions[];
};

export type Actions = SingleActions | MacroActions;

export type SlotCommand = SingleActions | MacroCommand | MacroActions[];
export type SlotList = SlotCommand[];

export function isTypeAction(obj: any): obj is TypeAction {
  return "type" in obj && typeof obj.type == "string";
}

export function isTapAction(obj: any): obj is TapAction {
  return "tap" in obj && typeof obj.tap == "string";
}

export function isPressAction(obj: any): obj is PressAction {
  return "press" in obj && typeof obj.press == "string";
}

export function isReleaseAction(obj: any): obj is ReleaseAction {
  return "release" in obj && typeof obj.release == "string";
}

export function isDelayAction(obj: any): obj is DelayAction {
  return "delay" in obj && typeof obj.delay == "number";
}

export function isMouseClickActionAction(obj: any): obj is MouseClickAction {
  return "click" in obj && typeof obj.click == "string";
}

export function isMouseMoveActionAction(obj: any): obj is MouseMoveAction {
  if ("move" in obj && typeof obj.move == "object") {
    if (typeof obj.move.x == "number" && typeof obj.move.y == "number") {
      return true;
    }
  }
  return false;
}

export function isButtonAssign(obj: any): obj is ButtonAssign {
  return "button" in obj && typeof obj.button == "string";
}

export function isSlotList(obj: any): obj is SlotList {
  if (!Array.isArray(obj)) return false;
  return obj.every((v) => isSlotCommand(v));
}

export function isSlotCommand(obj: any): obj is SlotCommand {
  if (isMacroCommand(obj)) {
    return true;
  } else if (Array.isArray(obj)) {
    return obj.every((v) => isMacroActions(v));
  } else {
    return isSingleActions(obj);
  }
}

export function isMacroCommand(obj: any): obj is MacroCommand {
  if (typeof obj == "object" && "name" in obj && typeof obj.name == "string") {
    if ("actions" in obj && Array.isArray(obj.actions)) {
      return obj.actions.every((v: any) => isMacroActions(v));
    }
  }
  return false;
}

export function isSingleActions(obj: any): obj is SingleActions {
  if (typeof obj == "string") return true;
  if (isTypeAction(obj)) return true;
  if (isButtonAssign(obj)) return true;
  if (isMouseClickActionAction(obj)) return true;
  return false;
}

export function isMacroActions(obj: any): obj is MacroActions {
  if (typeof obj == "number") return true;
  if (typeof obj == "string") return true;
  if (isTypeAction(obj)) return true;
  if (isTapAction(obj)) return true;
  if (isPressAction(obj)) return true;
  if (isReleaseAction(obj)) return true;
  if (isDelayAction(obj)) return true;
  if (isMouseClickActionAction(obj)) return true;
  if (isMouseMoveActionAction(obj)) return true;
  return false;
}

export function explainAction(action: Actions) {
  if (typeof action == "string") {
    return { name: "type", arg: action, type: "text" };
  }
  if (typeof action == "number") {
    return { name: "delay", arg: action, type: "ms" };
  }
  if (isTypeAction(action)) {
    return { name: "type", arg: action.type, type: "text" };
  }
  if (isTapAction(action)) {
    return { name: "tap", arg: action.tap, type: "key" };
  }
  if (isPressAction(action)) {
    return { name: "press", arg: action.press, type: "key" };
  }
  if (isReleaseAction(action)) {
    return { name: "release", arg: action.release, type: "key" };
  }
  if (isDelayAction(action)) {
    return { name: "delay", arg: action.delay, type: "ms" };
  }
  if (isMouseClickActionAction(action)) {
    return { name: "click", arg: action.click, type: "mouse" };
  }
  if (isMouseMoveActionAction(action)) {
    return {
      name: "move",
      arg: `(${action.move.x}, ${action.move.y})`,
      type: "pos",
    };
  }
  if (isButtonAssign(action)) {
    return { name: "button", arg: action.button, type: "key" };
  }
  return { name: "unknown", arg: "", type: "" };
}

export const SLOTS_DEFAULT: SlotList = [
  "1",
  { type: "hello world" },
  { button: "a" },
  { button: "TAB" },
  { name: "sample macro 1", actions: [{ type: "this is macro 1" }] },
  {
    name: "sample macro 2",
    description: "これは説明用のサンプルマクロです",
    actions: [{ press: "a" }, { delay: 1000 }, { release: "ALL" }],
  },

  {
    name: "sample macro 3",
    description:
      "これは説明用のサンプルマクロです。長いタイプの説明文です。あああああ本日は晴天なり",
    actions: [
      { press: "a" },
      { delay: 1000 },
      { release: "ALL" },
      { click: "LEFT" },
      { move: { x: 10, y: 30 } },
    ],
  },

  [{ press: "r" }, { delay: 1000 }, { release: "ALL" }, { type: "macro" }],

  {
    name: "chrome setup",
    description: "chromeのセットアップ自動化マクロ",
    actions: [
      { tap: "TAB" },
      { press: "DOWN_ARROW" },
      { delay: 1500 },
      { release: "DOWN_ARROW" },
      { type: " " },
      { delay: 500 },
      { type: "ssid aaaa" },
      { tap: "TAB" },
      { tap: "p" },
      { tap: "TAB" },
      { type: "password" },
    ],
  },
];

export const KEY_TABLE = {
  LEFT_CTRL: 0xe0,
  LEFT_SHIFT: 0xe1,
  LEFT_ALT: 0xe2,
  LEFT_GUI: 0xe3,
  RIGHT_CTRL: 0xe4,
  RIGHT_SHIFT: 0xe5,
  RIGHT_ALT: 0xe6,
  RIGHT_GUI: 0xe7,
  RETURN: 0x28,
  ESC: 0x29,
  BACKSPACE: 0x2a,
  TAB: 0x2b,
  CAPS_LOCK: 0x39,
  PRINT_SCREEN: 0x46,
  SCROLL_LOCK: 0x47,
  PAUSE: 0x48,
  INSERT: 0x49,
  HOME: 0x4a,
  PAGE_UP: 0x4b,
  DELETE: 0x4c,
  END: 0x4d,
  PAGE_DOWN: 0x4e,
  RIGHT_ARROW: 0x4f,
  LEFT_ARROW: 0x50,
  DOWN_ARROW: 0x51,
  UP_ARROW: 0x52,
  MENU: 0x65,
  NUM_LOCK: 0x53,
  KP_SLASH: 0x54,
  KP_ASTERISK: 0x55,
  KP_MINUS: 0x56,
  KP_PLUS: 0x57,
  KP_ENTER: 0x58,
  KP_1: 0x59,
  KP_2: 0x5a,
  KP_3: 0x5b,
  KP_4: 0x5c,
  KP_5: 0x5d,
  KP_6: 0x5e,
  KP_7: 0x5f,
  KP_8: 0x60,
  KP_9: 0x61,
  KP_0: 0x62,
  KP_DOT: 0x63,
  F1: 0x3a,
  F2: 0x3b,
  F3: 0x3c,
  F4: 0x3d,
  F5: 0x3e,
  F6: 0x3f,
  F7: 0x40,
  F8: 0x41,
  F9: 0x42,
  F10: 0x43,
  F11: 0x44,
  F12: 0x45,
  F13: 0x68,
  F14: 0x69,
  F15: 0x6a,
  F16: 0x6b,
  F17: 0x6c,
  F18: 0x6d,
  F19: 0x6e,
  F20: 0x6f,
  F21: 0x70,
  F22: 0x71,
  F23: 0x72,
  F24: 0x73,
  LEFT: 1,
  RIGHT: 2,
  MIDDLE: 4,
};
