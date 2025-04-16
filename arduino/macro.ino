
void MACRO_Init() {
  Keyboard.begin(KeyboardLayout_ja_JP);
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
    case 7:
      MACRO_winget_adobe_reader();
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

void nav_papas_download_teamview() {
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
  open_chrome("https://papas.jp");
}

void MACRO_download_secret_teamview() {
  open_secret_chrome("https://papas.jp");
  nav_papas_download_teamview();
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