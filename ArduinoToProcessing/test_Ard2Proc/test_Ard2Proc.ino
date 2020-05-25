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
  for(int i=1; i>0; i++)
  {
    Serial.println(i);
    //delay(100);
  }
}
