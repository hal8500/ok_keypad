const int NUM_ITEMS = 9;
const String FILE_PATH = "/j.json";


/*
items = [
  "text",
  {name: string, acts:[ {type:"print"|"press"|"release"|"releaseAll"|"delay"|"move", arg:int, x:int, y|int} ]},
]

*/

class Okeypad {
private:
  bool isFileLoaded;

  void set(String &command);
  void setJson(String &command);
  void list();
  void listJson();
  void save();
  void help();

  String validateJsonVar(JSONVar& j);

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

  for (int i = 0; i < NUM_ITEMS - 1; i++) {
    items[i] = String(i + 1);
  }

  JSONVar last = items[NUM_ITEMS - 1];

  last["name"] = "macro";
  last["acts"][0]["type"] = "press";
  last["acts"][0]["arg"] = 'r';
  last["acts"][1]["type"] = "delay";
  last["acts"][1]["arg"] = 1000;
  last["acts"][2]["type"] = "releaseAll";
  last["acts"][3]["type"] = "print";
  last["acts"][3]["arg"] = "mcr";
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

String Okeypad::validateJsonVar(JSONVar& j) {
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

    JSONVar acts = item["acts"];
    
    for (int i = 0; i < acts.length(); i++) {
      JSONVar act = acts[i];
      Serial.print("act => ");
      Serial.println(act);
      if (act.hasPropertyEqual("type", "print")) {
        Keyboard.print((const char *)act["arg"]);
      } else if (act.hasPropertyEqual("type", "press")) {
        Keyboard.press((uint8_t)act["arg"]);
      } else if (act.hasPropertyEqual("type", "release")) {
        Keyboard.release((uint8_t)act["arg"]);
      } else if (act.hasPropertyEqual("type", "releaseAll")) {
        Keyboard.releaseAll();
      } else if (act.hasPropertyEqual("type", "delay")) {
        delay((unsigned long) act["arg"]);
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
