
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

const byte ROWS = 4;  //four rows
const byte COLS = 3;  //three columns
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '#', '0', '*' }
};

byte rowPins[ROWS] = { _KEY_D, _KEY_C, _KEY_B, _KEY_A };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { _KEY_X, _KEY_Y, _KEY_Z };          //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int kcharToCode(char kc) {
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      if (keys[r][c] == kc) {
        return r * COLS + c;
      }
    }
  }
  return -1;
}