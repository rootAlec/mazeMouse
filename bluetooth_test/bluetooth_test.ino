#include <SoftwareSerial.h>
const int rxpin = A1; // 接收 pin
const int txpin = A0; // 發送 pin
SoftwareSerial bluetooth(rxpin, txpin); // 建立虛擬序列埠

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600); // 初始化藍芽序列埠
}

void loop() {
  if (bluetooth.available())
  {
    char c = bluetooth.read();
    Serial.print(c);
  }
  if (Serial.available())
  {
    char c = Serial.read();
    bluetooth.print(c);
  }
}
