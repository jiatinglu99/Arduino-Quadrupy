//slave code for motor control
//linked to master through A4 and A5
//June 12th, 2018 by Terry Lu

#include <Wire.h>
#include <Servo.h>

char commandLine[] = "-5050505011|";
Servo servos[12];

class Central{
public:
  int x1, y1, x2, y2, picker;
  Central();
  void init(){
    x1 = 50;
    x2 = 50;
    y1 = 50;
    y2 = 50;
    picker = 0;
    for (int i = 0; i < 12; i++){
      pinMode(i+2, OUTPUT);
      servos[i].attach(i+2);
    }
  }
  int strToInt(int b){
    int temp = 10*(commandLine[2*b - 1]-'0')+ commandLine[2*b]-'0';
    return temp;
  }
  void dataUpdate(){
    x1 = strToInt(1);
    picker = strToInt(5);
  }
  void testMotor(){
    servos[picker].write(x1);
  }
} central;

Central::Central (){}

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
  central.dataUpdate();
  central.testMotor();
}

void setup() {
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  central.init();
}

bool isNum(char t){
  if (t - '0' < 10 && t - '0' >= 0) return true;
  return false;
}



void loop() {
  //Serial.println(commandLine);
  //delay(200);
}


