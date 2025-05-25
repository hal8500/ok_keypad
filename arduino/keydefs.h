#ifndef OK_KEY_DEFS_H
#define OK_KEY_DEFS_H

//----------------------------------------//
// AE_KEYPAD4X3   ------   Arduino UNO    //
//                                        //
//   |>        <------       3.3V         //
//   X         ------>       GP17 | GP21  //
//   Y         ------>       GP18 | GP22  //
//   Z         ------>       GP19 | GP23  //
//   A         <------       GP20 | GP24  //
//   B         <------       GP21 | GP25  //
//   C         <------       GP22 | GP26  //
//   D         <------       GP26 | GP27  //
//----------------------------------------//


#define V1

#ifdef V1

// V1用ピンマップ
const byte _KEY_X = 17;
const byte _KEY_Y = 18;
const byte _KEY_Z = 19;
const byte _KEY_A = 20;
const byte _KEY_B = 21;
const byte _KEY_C = 22;
const byte _KEY_D = 26;

#else

// V2用ピンマップ
const byte _KEY_X = 21;
const byte _KEY_Y = 22;
const byte _KEY_Z = 23;
const byte _KEY_A = 24;
const byte _KEY_B = 25;
const byte _KEY_C = 26;
const byte _KEY_D = 27;

#endif




const byte ROWS = 4;  //four rows
const byte COLS = 3;  //three columns
const byte NUM_KEYS = ROWS * COLS;
const char CANCEL_KEY = '*';
const char KEYS[NUM_KEYS] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '#', '0', CANCEL_KEY};

byte rowPins[ROWS] = { _KEY_D, _KEY_C, _KEY_B, _KEY_A };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { _KEY_X, _KEY_Y, _KEY_Z };          //connect to the column pinouts of the keypad


#endif