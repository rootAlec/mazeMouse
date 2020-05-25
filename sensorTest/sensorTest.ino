const int trackPin_1000 = A5;
const int trackPin_0100 = A4;
const int trackPin_0010 = A3;
const int trackPin_0001 = A2;
char lineState[5];

void setup() {
  Serial.begin(9600);
}

char chooseRoute(int L, int R)
{
  char left = 'L'; char right = 'R';
  if(L > 0 && R < 0 )
    return left;
   else if(L < 0 && R > 0)
    return right;
   else
    return left; return right;
}

void loop() {

  char t = '1'; char f = '0';
  lineState[0] = digitalRead(trackPin_1000) == 0 ? t : f;
  lineState[1] = digitalRead(trackPin_0100) == 0 ? t : f;
  lineState[2] = digitalRead(trackPin_0010) == 0 ? t : f;
  lineState[3] = digitalRead(trackPin_0001) == 0 ? t : f;
  
  Serial.println(lineState);
  delay(500);
}
