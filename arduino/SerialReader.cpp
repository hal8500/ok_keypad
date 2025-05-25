#include "SerialReader.h"

bool SerialReader::update() {
  if (Serial.available()) {
    String str = Serial.readString();
    buffer.concat(str);
    if (buffer.indexOf('\n') != -1) {
      return true;
    }
  }

  return false;
}

String SerialReader::getLine() {
  int idx = buffer.indexOf('\n');
  if (idx != -1) {
    String line = buffer.substring(0, idx);
    buffer = buffer.substring(idx + 1);
    line.trim();
    buffer.trim();
    return line;
  } else {
    return "";
  }
}

