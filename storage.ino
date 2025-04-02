#include <LittleFS.h>

const int NUM_ITEMS = 9;
const String FILE_PATH = "/f.txt";
String items[NUM_ITEMS];
bool isFileLoaded = false;


void setDefaultItems() {
  for (int i = 0; i < NUM_ITEMS; i++) {
    items[i] = String(i + 1);
  }
}

void handleInput(String &command) {
  Serial.print("command > ");
  Serial.println(command);

  if (command.startsWith("set ")) {
    Serial.println("set command");
    handleSetCommand(command);
  } else if (command == "list") {
    Serial.println("list command");
    handleListCommand();
  } else if (command == "load") {
    loadItems();
  }
}

void handleSetCommand(String &command) {

  

  char slot_c = command[4];
  Serial.print("slot: ");
  Serial.println(slot_c);

  int slot = slot_c - '1';

  if (slot < 0 || NUM_ITEMS <= slot) {
    Serial.print("out of range :");
    Serial.println(slot);
    return;
  }

  if (command.length() < 7) {
    Serial.println("set command too short");
    return;
  }

  // "set 7 sab"
  String str = command.substring(6);
  items[slot] = str;

  Serial.print("set items[");
  Serial.print(slot);
  Serial.print("] = ");
  Serial.println(items[slot]);

  saveItems();
}

void handleListCommand() {
  for (int i = 0; i < NUM_ITEMS; i++) {
    Serial.print(i + 1);
    Serial.print(" ");
    Serial.println(items[i]);
  }
}

void loadItems() {
  File f = LittleFS.open(FILE_PATH, "r");

  if (!f) {
    Serial.println("failed to open file for reading");
    return;
  }

  Serial.println("loading items");
  int i = 0;
  while (f.available() && i < NUM_ITEMS) {
    String line = f.readStringUntil('\n');

    Serial.print(" line[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(line);

    items[i++] = line;
  }

  for (int j = i; j < NUM_ITEMS; j++) {
    Serial.print(" line[");
    Serial.print(j);
    Serial.println("] = *");

    items[j] = "";
  }

  f.close();
}

void saveItems() {
  File f = LittleFS.open(FILE_PATH, "w");

  if (!f) {
    Serial.println("failed to open file for writing");
    return;
  }

  Serial.println("saving items");
  for (int i = 0; i < NUM_ITEMS; i++) {
    Serial.print(" line[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(items[i]);

    f.println(items[i]);
  }

  f.close();
}

void storage_setup() {
  Serial.begin(9600);
  Serial.setTimeout(20);  // タイムアウトは2000ミリ秒(2秒)

  LittleFS.begin();

  setDefaultItems();
  loadItems();
}

