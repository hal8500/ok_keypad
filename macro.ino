#include <Keyboard.h>

#define SHIFT 0x80
const uint8_t keymap[128] = {
  0x00,  // NUL
  0x00,  // SOH
  0x00,  // STX
  0x00,  // ETX
  0x00,  // EOT
  0x00,  // ENQ
  0x00,  // ACK
  0x00,  // BEL
  0x2a,  // BS   Backspace
  0x2b,  // TAB  Tab
  0x28,  // LF   Enter
  0x00,  // VT
  0x00,  // FF
  0x00,  // CR
  0x00,  // SO
  0x00,  // SI
  0x00,  // DEL
  0x00,  // DC1
  0x00,  // DC2
  0x00,  // DC3
  0x00,  // DC4
  0x00,  // NAK
  0x00,  // SYN
  0x00,  // ETB
  0x00,  // CAN
  0x00,  // EM
  0x00,  // SUB
  0x00,  // ESC
  0x00,  // FS
  0x00,  // GS
  0x00,  // RS
  0x00,  // US

  0x2c,          // " "
  0x1e | SHIFT,  // !
  0x1f | SHIFT,  // "
  0x20 | SHIFT,  // #
  0x21 | SHIFT,  // $
  0x22 | SHIFT,  // %
  0x23 | SHIFT,  // &
  0x24 | SHIFT,  // '
  0x25 | SHIFT,  // (
  0x26 | SHIFT,  // )
  0x34 | SHIFT,  // *
  0x33 | SHIFT,  // +
  0x36,          // ,
  0x2d,          // -
  0x37,          // .
  0x38,          // /
  0x27,          // 0
  0x1e,          // 1
  0x1f,          // 2
  0x20,          // 3
  0x21,          // 4
  0x22,          // 5
  0x23,          // 6
  0x24,          // 7
  0x25,          // 8
  0x26,          // 9
  0x34,          // :
  0x33,          // ;
  0x36 | SHIFT,  // <
  0x2d | SHIFT,  // =
  0x37 | SHIFT,  // >
  0x38 | SHIFT,  // ?
  0x2f,          // @
  0x04 | SHIFT,  // A
  0x05 | SHIFT,  // B
  0x06 | SHIFT,  // C
  0x07 | SHIFT,  // D
  0x08 | SHIFT,  // E
  0x09 | SHIFT,  // F
  0x0a | SHIFT,  // G
  0x0b | SHIFT,  // H
  0x0c | SHIFT,  // I
  0x0d | SHIFT,  // J
  0x0e | SHIFT,  // K
  0x0f | SHIFT,  // L
  0x10 | SHIFT,  // M
  0x11 | SHIFT,  // N
  0x12 | SHIFT,  // O
  0x13 | SHIFT,  // P
  0x14 | SHIFT,  // Q
  0x15 | SHIFT,  // R
  0x16 | SHIFT,  // S
  0x17 | SHIFT,  // T
  0x18 | SHIFT,  // U
  0x19 | SHIFT,  // V
  0x1a | SHIFT,  // W
  0x1b | SHIFT,  // X
  0x1c | SHIFT,  // Y
  0x1d | SHIFT,  // Z
  0x30,          // [
  0x89,          // Yen(Backslash)
  0x31,          // ]
  0x2e,          // ^
  0x87 | SHIFT,  // _
  0x2f | SHIFT,  // @
  0x04,          // a
  0x05,          // b
  0x06,          // c
  0x07,          // d
  0x08,          // e
  0x09,          // f
  0x0a,          // g
  0x0b,          // h
  0x0c,          // i
  0x0d,          // j
  0x0e,          // k
  0x0f,          // l
  0x10,          // m
  0x11,          // n
  0x12,          // o
  0x13,          // p
  0x14,          // q
  0x15,          // r
  0x16,          // s
  0x17,          // t
  0x18,          // u
  0x19,          // v
  0x1a,          // w
  0x1b,          // x
  0x1c,          // y
  0x1d,          // z
  0x30 | SHIFT,  // {
  0x89 | SHIFT,  // |
  0x31 | SHIFT,  // }
  0x2e | SHIFT,  // ~
  0              // DEL
};

void MACRO_Init() {
  Keyboard.begin(keymap);
  Mouse.begin();
}

void MACRO_Switch(int code) {
  switch (code) {
    case 1:
      MACRO_hello();
      break;
    case 2:
      MACRO_move_cursor();
      break;
    case 3:
      MACRO_open_download();
      break;
    case 4:
      MACRO_open_papas();
      break;
    case 5:
      MACRO_download_secret_teamview();
      break;
    case 6:
      MACRO_download_adobe_reader();
      break;
    default:
      break;
  }
}

void MACRO_hello() {
  Keyboard.print("Hello world!");
}

void MACRO_move_cursor() {
  for (int i = 0; i < 10; i ++) {
    Mouse.move(10, 0, 0);
    delay(100);
  }
  for (int i = 0; i < 10; i ++) {
    Mouse.move(0, 10, 0);
    delay(100);
  }
  for (int i = 0; i < 10; i ++) {
    Mouse.move(-10, 0, 0);
    delay(100);
  }
  for (int i = 0; i < 10; i ++) {
    Mouse.move(0, -10, 0);
    delay(100);
  }
}

void MACRO_open_download() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(500);
  Keyboard.println("%userprofile%/downloads");
}

void MACRO_open_chrome(String url) {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.releaseAll();
  delay(500);
  Keyboard.print("chrome");
  delay(500);
  Keyboard.write(KEY_RETURN);
  delay(2000);
  Keyboard.println(url);
  delay(2000);
}

void MACRO_open_secret_chrome(String url) {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.releaseAll();
  delay(500);
  Keyboard.println("chrome");
  delay(1000);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('N');
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.println(url);
  delay(2000);
}

void MACRO_nav_papas_download_teamview() {
  Keyboard.write(KEY_TAB);
  delay(100);
  Keyboard.write(KEY_TAB);
  delay(100);
  Keyboard.write(KEY_TAB);
  delay(100);
  Keyboard.write(KEY_RETURN);
}

void MACRO_nav_download_adobe_reader() {
  Keyboard.write(KEY_TAB);
  delay(100);
  Keyboard.write(KEY_TAB);
  delay(100);
  Keyboard.write(KEY_TAB);
  delay(100);
  Keyboard.write(KEY_TAB);
  delay(100);
  Keyboard.write(KEY_TAB);
  delay(100);
  Keyboard.write(KEY_RETURN);
}

void MACRO_open_papas() {
  MACRO_open_chrome("https://papas.jp");
}

void MACRO_download_secret_teamview() {
  MACRO_open_secret_chrome("https://papas.jp");
  MACRO_nav_papas_download_teamview();
}

void MACRO_download_adobe_reader() {
  MACRO_open_chrome("https://get.adobe.com/jp/reader/");
  MACRO_nav_download_adobe_reader();
}
