const int NUM_ITEMS = 9;
const String FILE_PATH = "/j.json";

/*
# pressとpressIDの違い 
pressはcharとして出力する。pressIDはUSB HID Usage IDとして出力する？

https://github.com/HisashiKato/KeyboardPicoJP
https://bsakatu.net/doc/usb-hid-to-scancode/

JSONVarの読み出しについて
存在しないプロパティや型が一致しない読み出しを行うと型のデフォルト値が返される
JSONVar json = JSON.parse("{ a: "aa" }")
int x = (int)json["a"] // x = 0
int y = (int)json["?"] // y = 0

文字列のJSONVarにlength()を呼び出すと文字列の長さを返す
*/

const String DEFAULT_ITEMS_JSON = R"(
[
  "1",
  {"type":"hello world"},
  {"button":"a"},
  {"button":"TAB"},
  [{"name":"sample macro 1"},{"type":"this is macro 1"}],
  [{"name":"sample macro 2","description":"これは説明用のサンプルマクロです"},
  {"press":"a"},{"delay":1000},{"release":"ALL"}],
  [{"name":"sample macro 3","description":"これは説明用のサンプルマクロです。長いタイプの説明文です。あああああ本日は晴天なり"},{"press":"a"},{"delay":1000},{"release":"ALL"},{"click":"LEFT"},{"move":{"x":10,"y":30}}],
  [{"press":"r"},{"delay":1000},{"release":"ALL"},{"type":"macro"}],
  [
    {"name":"chrome setup","description":"chromeのセットアップ自動化マクロ"},
    {"tap":"TAB"},
    {"press":"DOWN_ARROW"},
    {"delay":1500},
    {"release":"DOWN_ARROW"},
    {"type":" "},
    {"delay":500},
    {"type":"ssid aaaa"},
    {"tap":"TAB"},
    {"tap":"p"},
    {"tap":"TAB"},
    {"type":"password"}
  ]
]
)";

const String KEY_TABLE_JSON = R"(
  {
  "LEFT_CTRL": 224,
  "LEFT_SHIFT": 225,
  "LEFT_ALT": 226,
  "LEFT_GUI": 227,
  "RIGHT_CTRL": 228,
  "RIGHT_SHIFT": 229,
  "RIGHT_ALT": 230,
  "RIGHT_GUI": 231,
  "RETURN": 40,
  "ESC": 41,
  "BACKSPACE": 42,
  "TAB": 43,
  "CAPS_LOCK": 57,
  "PRINT_SCREEN": 70,
  "SCROLL_LOCK": 71,
  "PAUSE": 72,
  "INSERT": 73,
  "HOME": 74,
  "PAGE_UP": 75,
  "DELETE": 76,
  "END": 77,
  "PAGE_DOWN": 78,
  "RIGHT_ARROW": 79,
  "LEFT_ARROW": 80,
  "DOWN_ARROW": 81,
  "UP_ARROW": 82,
  "MENU": 101,
  "NUM_LOCK": 83,
  "KP_SLASH": 84,
  "KP_ASTERISK": 85,
  "KP_MINUS": 86,
  "KP_PLUS": 87,
  "KP_ENTER": 88,
  "KP_1": 89,
  "KP_2": 90,
  "KP_3": 91,
  "KP_4": 92,
  "KP_5": 93,
  "KP_6": 94,
  "KP_7": 95,
  "KP_8": 96,
  "KP_9": 97,
  "KP_0": 98,
  "KP_DOT": 99,
  "F1": 58,
  "F2": 59,
  "F3": 60,
  "F4": 61,
  "F5": 62,
  "F6": 63,
  "F7": 64,
  "F8": 65,
  "F9": 66,
  "F10": 67,
  "F11": 68,
  "F12": 69,
  "F13": 104,
  "F14": 105,
  "F15": 106,
  "F16": 107,
  "F17": 108,
  "F18": 109,
  "F19": 110,
  "F20": 111,
  "F21": 112,
  "F22": 113,
  "F23": 114,
  "F24": 115,
  "LEFT": 1,
  "RIGHT": 2,
  "MIDDLE": 4
}
    
)";

class Okeypad {
private:
  bool isFileLoaded;
  JSONVar keyTable;

  void set(String &command);
  void setJson(String &command);
  void list();
  void listJson();
  void save();
  void help();

  String validateJsonVar(JSONVar &j);

public:
  bool debug;
  JSONVar items;

  void init();
  void handle(String &command);
  void load();
  void exec(int slot);
  void exec_command(const JSONVar &item);
};

void Okeypad::init() {
  isFileLoaded = false;
  debug = false;

  keyTable = JSON.parse(KEY_TABLE_JSON);
  items = JSON.parse(DEFAULT_ITEMS_JSON);
}

void Okeypad::handle(String &command) {
  Serial.print("command > ");
  Serial.println(command);

  if (command.startsWith("set ")) {
    set(command);
  } else if (command.startsWith("set_json ")) {
    setJson(command);
  } else if (command == "list") {
    list();
  } else if (command == "list_json") {
    listJson();
  } else if (command == "load") {
    load();
  } else if (command == "init") {
    init();
    save();
  } else if (command == "help") {
    help();
  }
}

void Okeypad::set(String &command) {
  char slot_c = command[4];
  int slot = slot_c - '1';

  if (slot < 0 || NUM_ITEMS <= slot) {
    Serial.print("out of slots: ");
    Serial.println(slot);
    return;
  }

  if (command.length() < 7) {
    items[slot] = "";
    Serial.print("clear slot[");
    Serial.print(slot + 1);
    Serial.print("]");
    Serial.println(items[slot]);
  } else {
    String str = command.substring(6);
    items[slot] = str;
    Serial.print("set slot[");
    Serial.print(slot + 1);
    Serial.print("] = ");
    Serial.println(items[slot]);
  }

  save();
}

void Okeypad::setJson(String &command) {
  String json_str = command.substring(9);
  JSONVar j = JSON.parse(json_str);

  String res = validateJsonVar(j);
  if (res.equals("ok")) {
    items = j;
    save();
  }
  Serial.println(res);
}

String Okeypad::validateJsonVar(JSONVar &j) {
  if (JSON.typeof(j) != "array") {
    return "The root must be an array.";
  }

  if (j.length() != NUM_ITEMS) {
    return "The root array lengths do not match.";
  }

  for (int i = 0; i < NUM_ITEMS; i++) {
    JSONVar item = j[i];
    String type = JSON.typeof(item);
    if (type.equals("string")) {
      continue;
    } else if (type.equals("object")) {
      if (item.hasOwnProperty("name")) {
        continue;
      } else {
        return "Item must have name.";
      }
    }
  }

  return "ok";
}

void Okeypad::list() {
  for (int i = 0; i < NUM_ITEMS; i++) {
    Serial.print("slot[");
    Serial.print(i + 1);
    Serial.print("] = ");
    if (JSON.typeof(items[i]) == "string") {
      Serial.println(items[i]);
    } else {
      Serial.println(items[i]["name"]);
    }
  }
}

void Okeypad::listJson() {
  Serial.println(items);
}

void Okeypad::exec(int code) {
  if (code < 0 || NUM_ITEMS <= code) {
    return;
  }

  JSONVar item = items[code];
  exec_command(item);


  if (JSON.typeof(item) == "string") {
    Keyboard.print((const char *)item);
  } else {
    Serial.print("call macro: ");
    Serial.println(item["name"]);

    JSONVar actions = item["actions"];

    for (int i = 0; i < actions.length(); i++) {
      JSONVar act = actions[i];
      Serial.print("act => ");
      Serial.println(act);
      if (act.hasPropertyEqual("type", "print")) {
        Keyboard.print((const char *)act["arg"]);
      } else if (act.hasPropertyEqual("type", "press")) {
        Keyboard.press((uint8_t)act["arg"]);
      } else if (act.hasPropertyEqual("type", "pressID")) {
        Keyboard.pressID((uint8_t)act["arg"]);
      } else if (act.hasPropertyEqual("type", "release")) {
        Keyboard.release((uint8_t)act["arg"]);
      } else if (act.hasPropertyEqual("type", "releaseID")) {
        Keyboard.releaseID((uint8_t)act["arg"]);
      } else if (act.hasPropertyEqual("type", "write")) {
        Keyboard.write((uint8_t)act["arg"]);
      } else if (act.hasPropertyEqual("type", "writeID")) {
        Keyboard.writeID((uint8_t)act["arg"]);
      } else if (act.hasPropertyEqual("type", "releaseAll")) {
        Keyboard.releaseAll();
      } else if (act.hasPropertyEqual("type", "delay")) {
        delay((unsigned long)act["arg"]);
      }
    }
  }
}

void Okeypad::load() {
  File f = LittleFS.open(FILE_PATH, "r");

  if (!f || !f.available()) {
    Serial.println("failed to open file for reading");
    return;
  }

  Serial.println("loading items");

  String json_str = f.readString();
  items = JSON.parse(json_str);

  f.close();
}

void Okeypad::save() {
  File f = LittleFS.open(FILE_PATH, "w");

  if (!f) {
    Serial.println("failed to open file for writing");
    return;
  }

  String json_str = JSON.stringify(items);
  f.print(json_str);
  f.close();
}

void Okeypad::help() {
  Serial.println();
  Serial.println("OkeyPad v0.1");
  Serial.println();
  Serial.println("commands");
  Serial.println("- list               Print all stored items.");
  Serial.println("- set [slot] [text]  Set text to specified slot. example: set 1 hello world!");
  Serial.println("- help               Print this message. ");
  Serial.println();
  Serial.println();
}

void Okeypad::exec_command(const JSONVar &item) {
  if (JSON.typeof(item) == "string") {
    Keyboard.print((const char *)item);
  } else if (JSON.typeof(item) == "number") {
    delay((unsigned long)item);
  } else if (JSON.typeof(item) == "object") {
    if (item.hasOwnProperty("type")) {
      String arg = (String)item["type"];
      Keyboard.print(arg);
    } else if (item.hasOwnProperty("click")) {
      String arg = (String)item["click"];
      if (keyTable.hasOwnProperty(arg)) {
        int btn = (int)keyTable[arg];
        Mouse.click(btn);
      }
    }
  }
}

Okeypad okeypad;

void okeypad_setup() {
  Serial.setTimeout(20);
  LittleFS.begin();
  okeypad.init();
  okeypad.load();
}
