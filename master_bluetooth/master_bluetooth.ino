//master code for bluetooth control
//linked to slave through A4 and A5
//June 12th, 2018 by Terry Lu

#include <Wire.h>

bool firstTime = true;
long lastConnection, firstConnection;
char commandLine[] = "-0000000000|"; //sample

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

bool isNum(char t) {
  if (t - '0' < 10 && t - '0' >= 0) return true;
  return false;
}

void receiveData() {
  //if (Serial.available()){
  //  char c = Serial.read();
  //  Serial.print(c);
  //}
  if (Serial.available()) {
    char checkStart = Serial.read();
    if (checkStart == '-') {
      delay(5);
      int count = 0;
      while (Serial.available()) {
        char temp = Serial.read();
        if (isNum(temp)) commandLine[++count] = temp;
        else if (temp == "|") break;
        delay(5);//data recognition buffer
      }
    }
  }
}

void sendSlave() {
  Wire.beginTransmission(8);
  Wire.write(commandLine);
  Wire.endTransmission();
}

void loop() {
  receiveData();
  sendSlave();
  delay(20);
  //Serial.println(commandLine);
}
