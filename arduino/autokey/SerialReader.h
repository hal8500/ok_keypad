#ifndef OK_SERIAL_READER_H
#define OK_SERIAL_READER_H

#include <Arduino.h>

class SerialReader {
protected:
  String buffer;

public:
  SerialReader()
    : buffer("") {}
  bool update();
  String getLine();
};

#endif