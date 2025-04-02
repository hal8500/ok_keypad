#include <Mouse.h>
#include <Arduino.h>

#define _POWER_LED 25
#define _ACT_LED 2

void AE_KEYPAD4X3_Init(void);
int AE_KEYPAD4X3_getKey(void);
char AE_KEYPAD4X3_getKeyChar(void);
void MACRO_Init();
void MACRO_Switch(int code);

void setup() {
  Serial.begin(9600);

  pinMode(_POWER_LED, OUTPUT);
  digitalWrite(_POWER_LED, 1);

  pinMode(_ACT_LED, OUTPUT);
  digitalWrite(_ACT_LED, 0);

  MACRO_Init();
  AE_KEYPAD4X3_Init();  //KEYPAD用の入出力ピン設定
}

void loop() {
  int key;

  key = AE_KEYPAD4X3_getKeys();  //押されたキーを文字で出力する 例 '1'や'#'など

  if (key != 0) {
    //digitalWrite(_ACT_LED, 1);
    Serial.println(key);

    //MACRO_Switch(key);

    //delay(1000);
    //digitalWrite(_ACT_LED, 0);
  }

  delay(10);
}


