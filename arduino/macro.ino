void MACRO_Init() {
  Keyboard.begin(KeyboardLayout_ja_JP);
  Mouse.begin();
}

// キャンセル可能なdelay機能
// msミリ秒後にfalseを返す
// それまでの間に*キーを押した場合は即座にtrueを返す
// 使用例
// if (pause(1000)) { Serial.println("中断されました"); return; }
bool pause(int ms) {
  unsigned long start = millis();
  while (true) {
    char key = keypad.getKey();
    if (key == '*') return true;
    unsigned long elapsed = millis() - start;
    if (ms < elapsed) return false;
  }
}

void test_macro() {
  Keyboard.println();
  Keyboard.press(KEY_DOWN_ARROW);
  pause(1000);
  Keyboard.releaseAll();
  Keyboard.println("okm");
  Keyboard.print("\t");
  
  Keyboard.press(KEY_DOWN_ARROW);
  Keyboard.releaseAll();
  Keyboard.press(KEY_DOWN_ARROW);
  Keyboard.releaseAll();
  Keyboard.print("\t");
  Keyboard.print("aieueoe");
}

void MACRO_hello() {
  Keyboard.print("Hello world!");
}

void MACRO_move_cursor() {
  for (int i = 0; i < 10; i++) {
    Mouse.move(10, 0, 0);
    delay(100);
  }
  for (int i = 0; i < 10; i++) {
    Mouse.move(0, 10, 0);
    delay(100);
  }
  for (int i = 0; i < 10; i++) {
    Mouse.move(-10, 0, 0);
    delay(100);
  }
  for (int i = 0; i < 10; i++) {
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

void open_chrome(String url) {
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

void open_secret_chrome(String url) {
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

void MACRO_download_adobe_reader() {
  open_chrome("https://get.adobe.com/jp/reader/");
  MACRO_nav_download_adobe_reader();
}

void open_cmd() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(500);
  Keyboard.println("cmd");
}

void MACRO_winget_adobe_reader() {
  open_cmd();
  delay(500);
  Keyboard.println("winget install Adobe.Acrobat.Reader.64-bit --override \"/sPB /rs /rps /msi EULA_ACCEPT=YES ENABLE_OPTIMIZATION=1 DISABLEDESKTOPSHORTCUT=1\"");
}