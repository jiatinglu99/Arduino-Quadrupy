//slave code for motor control
//linked to master through A4 and A5
//June 12th, 2018 by Terry Lu

#include <Wire.h>

char commandLine[] = "-5050505011|";

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
}

bool isNum(char t){
  if (t - '0' < 10 && t - '0' >= 0) return true;
  return false;
}

void loop() {
  delay(100);
  Serial.println(commandLine);
}

void receiveEvent(int howMany){
  int count = 0;
  while(0 < Wire.available()){
    char c = Wire.read();
    if (c == '-')
      count = 0;
    else if (isNum(c))
      commandLine[++count] = c;
    else if (c == '|')
      break;
  }
}

