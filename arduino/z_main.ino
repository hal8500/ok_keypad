#define _POWER_LED 25
#define _ACT_LED 2

Shell sh;

void setup() {
  Serial.setTimeout(20);
  Serial.begin(9600);
  okeypad_setup();
  MACRO_Init();

  pinMode(_POWER_LED, OUTPUT);
  digitalWrite(_POWER_LED, 1);

  pinMode(_ACT_LED, OUTPUT);
  digitalWrite(_ACT_LED, 0);
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    int code = kcharToCode(key);

    if (code == 9) {
      Keyboard.println("");
    } else {
      okeypad.exec(code);
    }
  }

  if (sh.update()) {
    String line = sh.getLine();
    okeypad.handle(line);
  }
}
