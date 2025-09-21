#ifndef OK_JS_H
#define OK_JS_H

#include <Arduino_JSON.h>
#include <Mouse.h>
#include "KeyboardPico.h"
#include <memory>

JSONVar loadDefaultItemsJson();

#define JS_DEBUGx

uint8_t parseKeyLabel(const String &value);
const char *getKeyLabel(int key);

class Executable {
public:
  // アクションを実行する
  // 完了した場合はtrueを返し、継続する内容がある場合はfalseを返す。
  // falseの場合は次のloop関数内で再実行される。
  // exec内で制御のブロックを行ってはならない。
  virtual bool exec() {
    return true;
  };

  // 現在実行中のアクションを中止する。
  virtual void cancel(){};

  // このオブジェクトの概要をコンソールに表示する
  virtual void desc() {
    Serial.print("nope");
  };

  // 派生クラスのリソースが正しく開放されるために必要
  virtual ~Executable() {
#ifdef JS_DEBUG
    Serial.print("x");
#endif
  }
};

class Bindable : public Executable {
public:
  virtual void onPress(){};
  virtual void onRelease(){};
  virtual bool isActive() {
    return false;
  };
};

class TypeAction : public Executable {
private:
  String msg_;

public:
  TypeAction(String &&msg)
    : msg_{ msg } {}

  bool exec() override {
    Keyboard.print(msg_);
    return true;
  }

  void desc() override {
    Serial.print("type: ");
    Serial.print(msg_);
  }
};

class TapAction : public Executable {
private:
  uint8_t key_ = 0;

public:
  TapAction(uint8_t key)
    : key_{ key } {
  }

  bool exec() override {
    Keyboard.write(key_);
    return true;
  }

  void desc() override {
    Serial.print("tap: ");
    Serial.print((char)key_);
  }
};

class TapIdAction : public Executable {
private:
  uint8_t key_ = 0;

public:
  TapIdAction(uint8_t key)
    : key_{ key } {
  }

  bool exec() override {
    Keyboard.writeID(key_);
    return true;
  }

  void desc() override {
    Serial.print("tap id: ");
    Serial.print(getKeyLabel(key_));
  }
};

class PressAction : public Executable {
private:
  uint8_t key_ = 0;

public:
  PressAction(uint8_t key)
    : key_{ key } {
  }

  bool exec() override {
    Keyboard.press(key_);
    return true;
  }

  
  void cancel() override {
    Keyboard.release(key_);
  }

  void desc() override {
    Serial.print("press: ");
    Serial.print((char)key_);
  }
};

class PressIdAction : public Executable {
private:
  uint8_t key_ = 0;

public:
  PressIdAction(uint8_t key)
    : key_{ key } {
  }

  bool exec() override {
    Keyboard.pressID(key_);
    return true;
  }

  void cancel() override {
    Keyboard.releaseID(key_);
  }

  void desc() override {
    Serial.print("press id: ");
    Serial.print(getKeyLabel(key_));
  }
};

class ReleaseAction : public Executable {
private:
  uint8_t key_ = 0;

public:
  ReleaseAction(uint8_t key)
    : key_{ key } {
  }

  bool exec() override {
    Keyboard.release(key_);
    return true;
  }

  void desc() override {
    Serial.print("release: ");
    Serial.print((char)key_);
  }
};

class ReleaseIdAction : public Executable {
private:
  uint8_t key_ = 0;

public:
  ReleaseIdAction(uint8_t key)
    : key_{ key } {
  }

  bool exec() override {
    Keyboard.releaseID(key_);
    return true;
  }

  void desc() override {
    Serial.print("release id: ");
    Serial.print(getKeyLabel(key_));
  }
};

class ReleaseAllAction : public Executable {
public:
  ReleaseAllAction() {
  }

  bool exec() override {
    Keyboard.releaseAll();
    return true;
  }

  void desc() override {
    Serial.print("release all");
  }
};

class MouseMoveAction : public Executable {
private:
  int x_;
  int y_;

public:
  MouseMoveAction(int x, int y)
    : x_{ x }, y_{ y } {
  }

  bool exec() override {
    Mouse.move(x_, y_);
    return true;
  }

  void desc() override {
    Serial.printf("move: %d %d", x_, y_);
  }
};

class MouseClickAction : public Executable {
private:
  uint8_t key_ = 0;

public:
  MouseClickAction(uint8_t key)
    : key_{ key } {
  }

  bool exec() override {
    Mouse.click(key_);
    return true;
  }

  void desc() override {
    Serial.print("click: ");
    Serial.print(key_);
  }
};


class DelayAction : public Executable {
private:
  unsigned long delay_;
  unsigned long end_;

public:
  DelayAction(unsigned long ms)
    : delay_{ ms }, end_{ 0 } {
  }

  bool exec() override;

  void cancel() override {
    end_ = 0;
  }

  void desc() override {
    Serial.print("delay: ");
    Serial.print(delay_);
  }
};

class MacroCommand : public Bindable {
private:
  bool isActive_;
  size_t size_;
  size_t index_;
  String name_;
  String description_;

  // 動的配列に対して１つのUnique Pointerを用意し、それぞれの要素に対してもUnique Pointerを用意する。
  // 明示的にdeleteを呼ばなくてもMacroCommandの開放に合わせてactions_自体とその要素もすべて開放される。
  std::unique_ptr<std::unique_ptr<Executable>[]> actions_;

public:
  MacroCommand();

  MacroCommand(size_t size, String &&name, String &&description, std::unique_ptr<std::unique_ptr<Executable>[]> actions)
    : isActive_{ false }, index_{ 0 }, name_{ name }, description_{ description }, size_{ size }, actions_{ std::move(actions) } {
  }

  MacroCommand(String &&name, String &&description, std::unique_ptr<Executable> &&action)
    : isActive_{ false }, index_{ 0 }, name_{ name }, description_{ description }, size_{ 1 } {

    actions_ = std::make_unique<std::unique_ptr<Executable>[]>(1);
    actions_[0] = std::move(action);
  }

  void onPress() override {
    if (!isActive_) {
      isActive_ = true;
      index_ = 0;
    }
  }

  void onRelease() override {
  }

  bool isActive() override {
    return isActive_;
  }

  bool exec() override;

  void cancel() override;

  void desc() override;
};

enum class ButtonType {
  Char,
  Id,
  Mouse
};

class ButtonAssign : public Bindable {
private:
  bool isActive_;
  uint8_t key_;
  ButtonType type_;

public:
  ButtonAssign(const String &button);
  void onPress() override;
  void onRelease() override;
  bool isActive() override;
  bool exec() override;
  void cancel() override;
  void desc() override;
};

class SlotList {
private:
  size_t size_;
  std::unique_ptr<std::unique_ptr<Bindable>[]> slots_;
  bool executing_ = false;

public:
  SlotList(size_t size)
    : size_{ size } {
    slots_ = std::make_unique<std::unique_ptr<Bindable>[]>(size);
  }

  void loadJson(JSONVar &json);

  bool update();
  void onPress(size_t index);
  void onRelease(size_t index);
  void cancel();

  void desc();
};

bool isMacroCommand(JSONVar json);
std::unique_ptr<MacroCommand> buildMacroCommand(JSONVar json);
std::unique_ptr<Bindable> buildSlotCommand(JSONVar json);

#endif