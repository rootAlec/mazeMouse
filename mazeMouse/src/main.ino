#include <Arduino.h>
const int trackPin_1000 = A5;
const int trackPin_0100 = A4;
const int trackPin_0010 = A3;
const int trackPin_0001 = A2;
char lineState[5];

void setup() {
  Serial.begin(9600);
}

String chooseRoute(char l, int r)
{
  String s1 = "Turn Left";
  String s2 = "Turn Right";
  String s3 = "This is fork";
  String s4 = "This is Straight Line";
  if(l == '1' && r == '0')
  {
    return s1;
  }
  else if(l == '0' && r == '1')
  {
    return s2;
  }
  else if(l == '0' && r == '0')
  {
    return s3;
  }
  else
  {
    return s4;
  }
}

void loop() {
  
  char t = '1'; char f = '0';
  lineState[0] = digitalRead(trackPin_1000) == 0 ? t : f;
  lineState[1] = digitalRead(trackPin_0100) == 0 ? t : f;
  lineState[2] = digitalRead(trackPin_0010) == 0 ? t : f;
  lineState[3] = digitalRead(trackPin_0001) == 0 ? t : f;
  //black is 0;
  String ans;
  ans = chooseRoute(lineState[0], lineState[3]);
  Serial.println(ans);
  delay(100);
  
}
