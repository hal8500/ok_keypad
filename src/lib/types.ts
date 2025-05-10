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
  release: KeyIds | "ALL";
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

/**
 * マクロの名称や用途を記述します。
 * マクロの１番目の要素に配置してください。
 */
export type MacroDescription = {
  /**
   * マクロの名称を記述します
   */
  name: string;
  /**
   * マクロの用途を記述します
   */
  description?: string;
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
  | DelayAction
  | MouseClickAction
  | MouseMoveAction
  | MacroDescription
  | string
  | number;

export type Actions = SingleActions | MacroActions;

export type SlotCommand = SingleActions | MacroActions[];
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

export function isMacroDescription(obj: any): obj is MacroDescription {
  return "name" in obj && typeof obj.name == "string";
}

export function isButtonAssign(obj: any): obj is ButtonAssign {
  return "button" in obj && typeof obj.button == "string";
}

export function isSlotList(obj: any): obj is SlotList {
  if (!Array.isArray(obj)) return false;
  return obj.every((v) => isSlotCommand(v));
}

export function isSlotCommand(obj: any): obj is SlotCommand {
  if (Array.isArray(obj)) {
    return obj.every((v) => isMacroActions(v));
  } else {
    return isMacroActions(obj);
  }
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
  if (isMacroDescription(action)) {
    return { name: "name", arg: action.name, type: "desc" };
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
  [{ name: "sample macro 1" }, { type: "this is macro 1" }],
  [
    { name: "sample macro 2", description: "これは説明用のサンプルマクロです" },
    { press: "a" },
    { delay: 1000 },
    { release: "ALL" },
  ],
  [
    {
      name: "sample macro 3",
      description:
        "これは説明用のサンプルマクロです。長いタイプの説明文です。あああああ本日は晴天なり",
    },
    { press: "a" },
    { delay: 1000 },
    { release: "ALL" },
    { click: "LEFT" },
    { move: { x: 10, y: 30 } },
  ],
  "8",
  [{ press: "r" }, { delay: 1000 }, { release: "ALL" }, { type: "macro" }],
];
