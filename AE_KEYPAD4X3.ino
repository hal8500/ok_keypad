//----------------------------------------//
// AE_KEYPAD4X3   ------   Arduino UNO    //
//                                        //
//   |>        <------       3.3V         //
//   X         ------>       GP17         //
//   Y         ------>       GP18         //
//   Z         ------>       GP19         //
//   A         <------       GP20         //
//   B         <------       GP21         //
//   C         <------       GP22         //
//   D         <------       GP26         //
//----------------------------------------//


// KEYPAD用のピン記述
#define _KEY_X 17
#define _KEY_Y 18
#define _KEY_Z 19
#define _KEY_A 20
#define _KEY_B 21
#define _KEY_C 22
#define _KEY_D 26


//----------------------------------------------------//
// KEYPAD用の入出力ピン設定                             //
//----------------------------------------------------//
void AE_KEYPAD4X3_Init(void) {
  pinMode(_KEY_X, OUTPUT);
  pinMode(_KEY_Y, OUTPUT);
  pinMode(_KEY_Z, OUTPUT);
  pinMode(_KEY_A, INPUT);
  pinMode(_KEY_B, INPUT);
  pinMode(_KEY_C, INPUT);
  pinMode(_KEY_D, INPUT);
  digitalWrite(_KEY_X, 1);
  digitalWrite(_KEY_Y, 1);
  digitalWrite(_KEY_Z, 1);
}

//----------------------------------------------------//
// 押されたキーを検出し、数字を返します。
//----------------------------------------------------//
int AE_KEYPAD4X3_getKey(void) {
  digitalWrite(_KEY_X, 0);
  digitalWrite(_KEY_Y, 1);
  digitalWrite(_KEY_Z, 1);
  if (digitalRead(_KEY_A) == 0)
    return 10;
  if (digitalRead(_KEY_B) == 0)
    return 7;
  if (digitalRead(_KEY_C) == 0)
    return 4;
  if (digitalRead(_KEY_D) == 0)
    return 1;

  digitalWrite(_KEY_X, 1);
  digitalWrite(_KEY_Y, 0);
  digitalWrite(_KEY_Z, 1);
  if (digitalRead(_KEY_A) == 0)
    return 11;
  if (digitalRead(_KEY_B) == 0)
    return 8;
  if (digitalRead(_KEY_C) == 0)
    return 5;
  if (digitalRead(_KEY_D) == 0)
    return 2;

  digitalWrite(_KEY_X, 1);
  digitalWrite(_KEY_Y, 1);
  digitalWrite(_KEY_Z, 0);
  if (digitalRead(_KEY_A) == 0)
    return 12;
  if (digitalRead(_KEY_B) == 0)
    return 9;
  if (digitalRead(_KEY_C) == 0)
    return 6;
  if (digitalRead(_KEY_D) == 0)
    return 3;

  return 0;
}

//----------------------------------------------------//
// 押されたキーを検出し、数字を返します。
//----------------------------------------------------//
int AE_KEYPAD4X3_getKeys(void) {
  int res = 0;
  digitalWrite(_KEY_X, 0);
  digitalWrite(_KEY_Y, 1);
  digitalWrite(_KEY_Z, 1);
  if (digitalRead(_KEY_A) == 0)
    res |= (1 << 10);
  if (digitalRead(_KEY_B) == 0)
    res |= (1 << 7);
  if (digitalRead(_KEY_C) == 0)
    res |= (1 << 4);
  if (digitalRead(_KEY_D) == 0)
    res |= (1 << 1);

  digitalWrite(_KEY_X, 1);
  digitalWrite(_KEY_Y, 0);
  digitalWrite(_KEY_Z, 1);
  if (digitalRead(_KEY_A) == 0)
    res |= (1 << 11);
  if (digitalRead(_KEY_B) == 0)
    res |= (1 << 8);
  if (digitalRead(_KEY_C) == 0)
    res |= (1 << 5);
  if (digitalRead(_KEY_D) == 0)
    res |= (1 << 2);

  
  digitalWrite(_KEY_X, 1);
  digitalWrite(_KEY_Y, 1);
  digitalWrite(_KEY_Z, 0);
  if (digitalRead(_KEY_A) == 0)
    res |= (1 << 12);
  if (digitalRead(_KEY_B) == 0)
    res |= (1 << 9);
  if (digitalRead(_KEY_C) == 0)
    res |= (1 << 6);
  if (digitalRead(_KEY_D) == 0)
    res |= (1 << 3);

  return res;
}

//----------------------------------------------------//
// 押されたキーを検出し、一文字を返します。
//----------------------------------------------------//
char AE_KEYPAD4X3_getKeyChar(void) {
  int key = AE_KEYPAD4X3_getKey();
  if (key == 1) return '1';
  else if (key == 2) return '2';
  else if (key == 3) return '3';
  else if (key == 4) return '4';
  else if (key == 5) return '5';
  else if (key == 6) return '6';
  else if (key == 7) return '7';
  else if (key == 8) return '8';
  else if (key == 9) return '9';
  else if (key == 10) return '*';
  else if (key == 11) return '0';
  else if (key == 12) return '#';
  else return '\0';
}
