#include <Arduino.h>
#include <Mouse.h>
#include "KeyboardPico.h"
#include <Keypad.h>
#include <Arduino_JSON.h>
#include <LittleFS.h>

#include "keydefs.h"
#include "js.h"
#include "SerialReader.h"

const String FILE_PATH = "/j.json";

Keypad keypad = Keypad(makeKeymap(KEYS), rowPins, colPins, ROWS, COLS);
SerialReader sr;

SlotList slotList(NUM_SLOTS);

void setup() {
  Serial.setTimeout(20);
  Serial.begin(9600);
  LittleFS.begin();
  Keyboard.begin(KeyboardLayout_ja_JP);
  Mouse.begin();

  pinMode(_POWER_LED, OUTPUT);
  digitalWrite(_POWER_LED, 1);

  pinMode(_ACT_LED, OUTPUT);
  digitalWrite(_ACT_LED, 0);

  pinMode(_DRAIN_LED, OUTPUT);
  digitalWrite(_DRAIN_LED, 0);

  keypad.addEventListener(keypadEvent);

  load();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
  }

  // マクロ実行中ならtrue ACTLEDを光らせる
  if (slotList.update()) {
    digitalWrite(_ACT_LED, 1);
  } else {
    digitalWrite(_ACT_LED, 0);
  }

  if (sr.update()) {
    String line = sr.getLine();
    handleCommand(line);
  }
}

size_t getKeyIndex(KeypadEvent key) {
  for (size_t i = 0; i < NUM_KEYS; i++) {
    if (key == KEYS[i]) {
      return i;
    }
  }
  Serial.println("error key index.");
  return 0;
}

void keypadEvent(KeypadEvent key) {
  size_t index = getKeyIndex(key);
  KeyState state = keypad.getState();

  if (state == PRESSED) {
    if (key == CANCEL_KEY) {
      slotList.cancel();
    } else {
      slotList.onPress(index);
    }
  }

  if (state == RELEASED) {
    slotList.onRelease(index);
  }

  if (key == '#' && state == PRESSED) {
    Keyboard.println();
  }

  if (key == '0' && state == PRESSED) {
    Keyboard.println("https://hal8500.github.io/ok_keypad/");
  }
}

void handleCommand(String &command) {
  Serial.print("command > ");
  Serial.println(command);
  slotList.cancel();

  if (command.startsWith("set ")) {
    set(command);
  } else if (command.startsWith("set_json ")) {
    setJson(command);
  } else if (command == "list") {
    list();
  } else if (command == "list_json") {
    listJson();
  } else if (command == "init") {
    init();
  } else if (command == "help") {
    help();
  }
}

void set(String &command) {
  char slot_c = command[4];
  int slot = slot_c - '1';

  if (slot < 0 || NUM_SLOTS <= slot) {
    Serial.print("out of slots: ");
    Serial.println(slot);
    return;
  }

  JSONVar json = loadFile();

  if (command.length() < 7) {
    json[slot] = "";
    Serial.print("clear slot[");
    Serial.print(slot + 1);
    Serial.print("]");
    Serial.println(json[slot]);
  } else {
    String str = command.substring(6);
    json[slot] = str;
    Serial.print("set slot[");
    Serial.print(slot + 1);
    Serial.print("] = ");
    Serial.println(json[slot]);
  }

  slotList.loadJson(json);
  saveFile(json);
}

void setJson(String &command) {
  String json_str = command.substring(9);
  JSONVar json = JSON.parse(json_str);

  String res = validateJsonVar(json);
  if (res.equals("ok")) {
    slotList.loadJson(json);
    saveFile(json);
  }
  Serial.println(res);
}

String validateJsonVar(JSONVar &j) {
  if (JSON.typeof(j) != "array") {
    return "JSONのルート要素は配列である必要があります。";
  }

  return "ok";
}

void list() {
  slotList.desc();
}

void listJson() {
  File f = LittleFS.open(FILE_PATH, "r");

  if (!f || !f.available()) {
    Serial.println("failed to open file for reading");
    return;
  }

  Serial.println(f.readString());
  f.close();
}

void init() {
  JSONVar json = loadDefaultItemsJson();
  slotList.loadJson(json);
  saveFile(json);
}

void load() {
  JSONVar json = loadFile();
  if (JSON.typeof(json) == "array") {
    slotList.loadJson(json);
  } else {
    init();
  }
}

JSONVar loadFile() {
  File f = LittleFS.open(FILE_PATH, "r");

  if (!f || !f.available()) {
    Serial.println("failed to open file for reading");
    return nullptr;
  }

  Serial.println("loading items");

  String json_str = f.readString();
  f.close();

  return JSON.parse(json_str);
}

void saveFile(JSONVar &json) {
  File f = LittleFS.open(FILE_PATH, "w");

  if (!f) {
    Serial.println("failed to open file for writing");
    return;
  }

  f.print(JSON.stringify(json));
  f.close();
}

void help() {
  Serial.println(F(R"(
OkeyPad v0.2.0
commands
- list :現在のボタン割り当てを表示します。
- set [slot] [text] :slot番号が押されたときにtextを印字するように設定します。
- help :このメッセージを表示します。

  )"));
}
