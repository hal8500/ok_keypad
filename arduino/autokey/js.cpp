#include "js.h"

JSONVar loadDefaultItemsJson() {
  return JSON.parse(F(R"(
["1","2","3","4","5","6","7","8","9"]
)"));
}

uint8_t parseKeyLabel(const String &value) {

  if (value == "BACKSPACE") return 42;
  if (value == "CAPS_LOCK") return 57;
  if (value == "DELETE") return 76;
  if (value == "DOWN_ARROW") return 81;
  if (value == "END") return 77;
  if (value == "ESC") return 41;
  if (value == "F1") return 58;
  if (value == "F10") return 67;
  if (value == "F11") return 68;
  if (value == "F12") return 69;
  if (value == "F13") return 104;
  if (value == "F14") return 105;
  if (value == "F15") return 106;
  if (value == "F16") return 107;
  if (value == "F17") return 108;
  if (value == "F18") return 109;
  if (value == "F19") return 110;
  if (value == "F2") return 59;
  if (value == "F20") return 111;
  if (value == "F21") return 112;
  if (value == "F22") return 113;
  if (value == "F23") return 114;
  if (value == "F24") return 115;
  if (value == "F3") return 60;
  if (value == "F4") return 61;
  if (value == "F5") return 62;
  if (value == "F6") return 63;
  if (value == "F7") return 64;
  if (value == "F8") return 65;
  if (value == "F9") return 66;
  if (value == "HOME") return 74;
  if (value == "INSERT") return 73;
  if (value == "KP_0") return 98;
  if (value == "KP_1") return 89;
  if (value == "KP_2") return 90;
  if (value == "KP_3") return 91;
  if (value == "KP_4") return 92;
  if (value == "KP_5") return 93;
  if (value == "KP_6") return 94;
  if (value == "KP_7") return 95;
  if (value == "KP_8") return 96;
  if (value == "KP_9") return 97;
  if (value == "KP_ASTERISK") return 85;
  if (value == "KP_DOT") return 99;
  if (value == "KP_ENTER") return 88;
  if (value == "KP_MINUS") return 86;
  if (value == "KP_PLUS") return 87;
  if (value == "KP_SLASH") return 84;
  if (value == "LEFT_ALT") return 226;
  if (value == "LEFT_ARROW") return 80;
  if (value == "LEFT_CTRL") return 224;
  if (value == "LEFT_GUI") return 227;
  if (value == "LEFT_SHIFT") return 225;
  if (value == "MENU") return 101;
  if (value == "NUM_LOCK") return 83;
  if (value == "PAGE_DOWN") return 78;
  if (value == "PAGE_UP") return 75;
  if (value == "PAUSE") return 72;
  if (value == "PRINT_SCREEN") return 70;
  if (value == "RETURN") return 40;
  if (value == "RIGHT_ALT") return 230;
  if (value == "RIGHT_ARROW") return 79;
  if (value == "RIGHT_CTRL") return 228;
  if (value == "RIGHT_GUI") return 231;
  if (value == "RIGHT_SHIFT") return 229;
  if (value == "SCROLL_LOCK") return 71;
  if (value == "TAB") return 43;
  if (value == "UP_ARROW") return 82;

  Serial.print("Unknown keyID: ");
  Serial.println(value);
  return 0;
}

const char *getKeyLabel(int key) {
  switch (key) {
    case 40: return "RETURN";
    case 41: return "ESC";
    case 42: return "BACKSPACE";
    case 43: return "TAB";
    case 57: return "CAPS_LOCK";
    case 58: return "F1";
    case 59: return "F2";
    case 60: return "F3";
    case 61: return "F4";
    case 62: return "F5";
    case 63: return "F6";
    case 64: return "F7";
    case 65: return "F8";
    case 66: return "F9";
    case 67: return "F10";
    case 68: return "F11";
    case 69: return "F12";
    case 70: return "PRINT_SCREEN";
    case 71: return "SCROLL_LOCK";
    case 72: return "PAUSE";
    case 73: return "INSERT";
    case 74: return "HOME";
    case 75: return "PAGE_UP";
    case 76: return "DELETE";
    case 77: return "END";
    case 78: return "PAGE_DOWN";
    case 79: return "RIGHT_ARROW";
    case 80: return "LEFT_ARROW";
    case 81: return "DOWN_ARROW";
    case 82: return "UP_ARROW";
    case 83: return "NUM_LOCK";
    case 84: return "KP_SLASH";
    case 85: return "KP_ASTERISK";
    case 86: return "KP_MINUS";
    case 87: return "KP_PLUS";
    case 88: return "KP_ENTER";
    case 89: return "KP_1";
    case 90: return "KP_2";
    case 91: return "KP_3";
    case 92: return "KP_4";
    case 93: return "KP_5";
    case 94: return "KP_6";
    case 95: return "KP_7";
    case 96: return "KP_8";
    case 97: return "KP_9";
    case 98: return "KP_0";
    case 99: return "KP_DOT";
    case 101: return "MENU";
    case 104: return "F13";
    case 105: return "F14";
    case 106: return "F15";
    case 107: return "F16";
    case 108: return "F17";
    case 109: return "F18";
    case 110: return "F19";
    case 111: return "F20";
    case 112: return "F21";
    case 113: return "F22";
    case 114: return "F23";
    case 115: return "F24";
    case 224: return "LEFT_CTRL";
    case 225: return "LEFT_SHIFT";
    case 226: return "LEFT_ALT";
    case 227: return "LEFT_GUI";
    case 228: return "RIGHT_CTRL";
    case 229: return "RIGHT_SHIFT";
    case 230: return "RIGHT_ALT";
    case 231: return "RIGHT_GUI";
  }
  return "unknown";
}

uint8_t parseMouseButtonLabel(const String &value) {
  if (value == "LEFT") return 1;
  if (value == "RIGHT") return 2;
  if (value == "MIDDLE") return 4;

  Serial.print("Unknown MouseButtonID: ");
  Serial.println(value);
  return 0;
}

std::unique_ptr<Executable> buildAction(JSONVar json) {

  if (JSON.typeof(json) == "string") {
    return std::make_unique<TypeAction>((String)json);
  }

  if (JSON.typeof(json) == "number") {
    return std::make_unique<DelayAction>((unsigned long)json);
  }

  if (json.hasOwnProperty("type")) {
    return std::make_unique<TypeAction>((String)json["type"]);
  }

  if (json.hasOwnProperty("tap")) {
    String str = (String)json["tap"];
    if (str.length() == 1) {
      return std::make_unique<TapAction>(str[0]);
    }
    uint8_t id = parseKeyLabel(str);
    if (id != 0) {
      return std::make_unique<TapIdAction>(id);
    }
  }

  if (json.hasOwnProperty("press")) {
    String str = (String)json["press"];
    if (str.length() == 1) {
      return std::make_unique<PressAction>(str[0]);
    }
    uint8_t id = parseKeyLabel(str);
    if (id != 0) {
      return std::make_unique<PressIdAction>(id);
    }
  }

  if (json.hasOwnProperty("release")) {
    String str = (String)json["release"];
    if (str.length() == 1) {
      return std::make_unique<ReleaseAction>(str[0]);
    }
    if (str == "ALL") {
      return std::make_unique<ReleaseAllAction>();
    }
    uint8_t id = parseKeyLabel(str);
    if (id != 0) {
      return std::make_unique<ReleaseIdAction>(id);
    }
  }

  if (json.hasOwnProperty("move")) {
    int x = (int)json["move"]["x"];
    int y = (int)json["move"]["y"];
    return std::make_unique<MouseMoveAction>(x, y);
  }

  if (json.hasOwnProperty("click")) {
    String str = (String)json["click"];
    uint8_t id = parseMouseButtonLabel(str);
    if (id != 0) {
      return std::make_unique<MouseClickAction>(id);
    }
  }

  if (json.hasOwnProperty("delay")) {
    unsigned long ms = (unsigned long)json["delay"];
    return std::make_unique<DelayAction>(ms);
  }

  return std::make_unique<Executable>();
}

void checkJSON(JSONVar json) {
  Serial.println("Checking ");
  Serial.print("has name :");
  Serial.println(json.hasOwnProperty("name"));
  Serial.print("has actions :");
  Serial.println(json.hasOwnProperty("actions"));
  Serial.print("action type :");
  Serial.println(JSON.typeof(json["actions"]));

  Serial.print("len name :");
  Serial.println(json["name"].length());
}

bool isMacroCommand(JSONVar json) {
  return json.hasOwnProperty("name") && json.hasOwnProperty("actions") && JSON.typeof(json["actions"]) == "array";
}

std::unique_ptr<MacroCommand> buildMacroCommand(JSONVar json) {
  String name = (String)json["name"];
  String description = (String)json["description"];
  JSONVar j_actions = json["actions"];
  int size = j_actions.length();

  std::unique_ptr<std::unique_ptr<Executable>[]> actions = std::make_unique<std::unique_ptr<Executable>[]>(size);

  for (size_t i = 0; i < size; i++) {
    actions[i] = buildAction(j_actions[i]);
  }

  return std::make_unique<MacroCommand>(size, std::move(name), std::move(description), std::move(actions));
}

std::unique_ptr<MacroCommand> buildMacroCommandFromArray(JSONVar json) {
  String name = "Array macro";
  String description = "";
  JSONVar j_actions = json;
  int size = j_actions.length();

  std::unique_ptr<std::unique_ptr<Executable>[]> actions = std::make_unique<std::unique_ptr<Executable>[]>(size);

  for (size_t i = 0; i < size; i++) {
    actions[i] = buildAction(j_actions[i]);
  }

  return std::make_unique<MacroCommand>(size, std::move(name), std::move(description), std::move(actions));
}

std::unique_ptr<Bindable> buildSlotCommand(JSONVar json) {
  if (JSON.typeof(json) == "array") {
    return buildMacroCommandFromArray(json);
  }

  if (isMacroCommand(json)) {
    return buildMacroCommand(json);
  }

  if (JSON.typeof(json) == "string" || json.hasOwnProperty("type") || json.hasOwnProperty("click")) {
    return std::make_unique<MacroCommand>("", "", buildAction(json));
  }

  if (json.hasOwnProperty("button") && JSON.typeof(json["button"]) == "string") {
    return std::make_unique<ButtonAssign>((String)json["button"]);
  }

  return nullptr;
}


bool DelayAction::exec() {
  if (end_ == 0) {
    end_ = millis() + delay_;
    return false;
  }

  if (end_ < millis()) {
    end_ = 0;
    return true;
  }

  return false;
}

MacroCommand::MacroCommand()
  : isActive_{ false }, index_{ 0 } {
  size_ = 3;
  name_ = "hello";
  description_ = "hi";
  actions_ = std::make_unique<std::unique_ptr<Executable>[]>(size_);

  actions_[0] = std::make_unique<TapAction>('a');
  actions_[1] = std::make_unique<TapAction>('b');
  actions_[2] = std::make_unique<TapAction>('c');

  Serial.println("macro command new");
}

bool MacroCommand::exec() {
  if (index_ == size_) {
    index_ = 0;
    isActive_ = false;
    return true;
  }

  if (actions_[index_]->exec()) {
    index_ += 1;
  }

  return false;
}

void MacroCommand::cancel() {
  if (isActive_ && index_ < size_) {
    actions_[index_]->cancel();
  }
  Keyboard.releaseAll();
  index_ = 0;
  isActive_ = false;
}

void MacroCommand::desc() {
  if (name_ != "") {
    Serial.print("macro: ");
    Serial.print(name_);
  } else if (1 <= size_) {
    actions_[0]->desc();
  } else {
    Serial.print("nope");
  }
}

ButtonAssign::ButtonAssign(const String &button)
  : isActive_{ false } {
  if (button.length() == 1) {
    key_ = button[0];
    type_ = ButtonType::Char;
    return;
  }

  uint8_t id = parseKeyLabel(button);
  if (id != 0) {
    key_ = id;
    type_ = ButtonType::Id;
    return;
  }

  id = parseMouseButtonLabel(button);
  if (id != 0) {
    key_ = id;
    type_ = ButtonType::Mouse;
  }
}

void ButtonAssign::onPress() {
  isActive_ = true;
  switch (type_) {
    case ButtonType::Char:
      Keyboard.press(key_);
      break;
    case ButtonType::Id:
      Keyboard.pressID(key_);
      break;
    case ButtonType::Mouse:
      Mouse.press(key_);
      break;
  }
}

void ButtonAssign::onRelease() {
  this->cancel();
}

bool ButtonAssign::isActive() {
  return isActive_;
}

bool ButtonAssign::exec() {
  return false;
}

void ButtonAssign::cancel() {
  isActive_ = false;
  switch (type_) {
    case ButtonType::Char:
      Keyboard.release(key_);
      break;
    case ButtonType::Id:
      Keyboard.releaseID(key_);
      break;
    case ButtonType::Mouse:
      Mouse.release(key_);
      break;
  }
}

void ButtonAssign::desc() {
  Serial.print("button: ");
  switch (type_) {
    case ButtonType::Char:
      Serial.print((char)key_);
      break;
    case ButtonType::Id:
      Serial.print(getKeyLabel(key_));
      break;
    case ButtonType::Mouse:
      Serial.print(getKeyLabel(key_));
      break;
  }
}


void SlotList::loadJson(JSONVar &json) {

  if (JSON.typeof(json) != "array") {
    Serial.println("設定用jsonのルート要素は配列である必要があります。");
    return;
  }

#ifdef JS_DEBUG
  Serial.print("loading json size_ = ");
  Serial.println(size_);
#endif

  for (size_t i = 0; i < size_; i++) {
    JSONVar jslot = json[i];
    if (JSON.typeof(jslot) != "null") {

#ifdef JS_DEBUG
      Serial.print("loading slot ");
      Serial.println(i);
      Serial.println(JSON.stringify(jslot));
#endif

      slots_[i] = buildSlotCommand(jslot);
    } else {

#ifdef JS_DEBUG
      Serial.print("null slot ");
      Serial.println(i);
      Serial.println(JSON.stringify(jslot));
#endif
      slots_[i] = nullptr;
    }
  }
}

bool SlotList::update() {
  // 実行中マクロがないなら終了
  if (!executing_) return false;

  executing_ = false;
  for (size_t i = 0; i < size_; i++) {
    if (slots_[i] != nullptr) {
      if (slots_[i]->isActive()) {
        slots_[i]->exec();
        executing_ = true;
      }
    }
  }
  return true;
}


void SlotList::onPress(size_t i) {

#ifdef JS_DEBUG
  Serial.print("slot list onpress ");
  Serial.println(i);

  Serial.print("executing ");
  Serial.println(executing_);
#endif

  // 実行中のマクロがある場合は何もしない
  if (executing_) return;
  if (size_ <= i) return;

  if (slots_[i] != nullptr) {
    slots_[i]->onPress();
    executing_ = true;
  }
}
void SlotList::onRelease(size_t i) {
  if (size_ <= i) return;
  if (slots_[i] != nullptr) {
    slots_[i]->onRelease();
  }
}

void SlotList::cancel() {
#ifdef JS_DEBUG
  Serial.println("slotlist cancel ");
#endif
  for (size_t i = 0; i < size_; i++) {
    if (slots_[i] != nullptr) {
      if (slots_[i]->isActive()) {
        slots_[i]->cancel();
      }
    }
  }
  executing_ = false;
}

void SlotList::desc() {
  for (int i = 0; i < size_; i++) {
    Serial.print("slot[");
    Serial.print(i + 1);
    Serial.print("] = ");
    slots_[i]->desc();
    Serial.println();
  }
}
