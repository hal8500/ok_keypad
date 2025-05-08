const int NUM_ITEMS = 9;
const String FILE_PATH = "/j.json";


/*
items = [
  "text",
  {name: string, actions:[ {type:"print"|"press(ID)?"|"release(ID)?"|"write(ID)?"|"releaseAll"|"delay"|"move"|"click", arg:int|string, x:int, y|int} ]},
]

# pressとpressIDの違い 
pressはcharとして出力する。pressIDはUSB HID Usage IDとして出力する？

https://bsakatu.net/doc/usb-hid-to-scancode/
*/

const String DEFAULT_ITEMS_JSON = R"(
  [
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    {
        "name": "chrome setup",
        "actions": [
            {
                "type": "print",
                "arg": "\t"
            },
            {
                "type": "pressID",
                "arg": 81
            },
            {
                "type": "delay",
                "arg": 1500
            },
            {
                "type": "releaseAll"
            },
            {
                "type": "print",
                "arg": " "
            },
            {
                "type": "delay",
                "arg": 500
            },
            {
                "type": "print",
                "arg": "aaaaaa"
            },
            {
                "type": "print",
                "arg": "\t"
            },
            {
                "type": "print",
                "arg": "p"
            },
            {
                "type": "print",
                "arg": "\t"
            },
            {
                "type": "print",
                "arg": "password"
            }
        ]
    }
]
)";

class Okeypad {
private:
  bool isFileLoaded;

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
};

void Okeypad::init() {
  isFileLoaded = false;
  debug = false;

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

Okeypad okeypad;

void okeypad_setup() {
  Serial.setTimeout(20);
  LittleFS.begin();
  okeypad.init();
  okeypad.load();
}
