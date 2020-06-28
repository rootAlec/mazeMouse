#include <Arduino.h>
#include <Servo.h>
#include <AFMotor.h>
#include <SoftwareSerial.h>

// Sensor setup
const int trackPin_1000 = A5;                       //     4            1
const int trackPin_0100 = A4;                       //    _|_          _|_
const int trackPin_0010 = A3;                       //   |___|        |___|
const int trackPin_0001 = A2;                       //   |_|_|        |_|_|
char l, m1, m2, r;
const int rxpin = A0; // 接收 pin
const int txpin = A1; // 發送 pin
int x;
SoftwareSerial bluetooth(rxpin, txpin); // 建立虛擬序列埠

// Motor setup
AF_DCMotor motor1(1);
AF_DCMotor motor4(4);

// Struct setup
struct Position
{
    int x;
    int y;
};
int crossMark = 1;

// Make motor run
void Straight_Line()
{
    while(l=='1' && r=='1')
    {   
        getStatus();

        if(l!='1' || r!='1')
        {
            reverse();
            return;
            // String route_type;
            // route_type = chooseRoute(l, m1, m2, r);
            // Serial.println(route_type);
            // motorRun(route_type,l, m1, m2, r);
            //return;
        }

        double speed = 80*0.85;
        motor4.setSpeed(80);
        motor1.setSpeed(speed);
        
        motor1.run(FORWARD);
        motor4.run(FORWARD);
        if(m1=='0' && m2=='1') // Right
        {
            int i=2;
            while(m1=='0' && m2!='0')
            {
                getStatus();
                motor4.setSpeed(80);
                motor1.setSpeed(speed+i);
                motor1.run(FORWARD);
                motor4.run(FORWARD);
                i+=3;

                // getStatus();
                // if(l=='1' && m1=='1' && m2=='1' && r=='1')
                // {
                //     stopTheCar();
                // }
            }
        }

        if(m1=='1' && m2=='0') // Left
        {
            int i=2;
            while(m1!='0' && m2=='0')
            {
                getStatus();
                motor4.setSpeed(80+i);
                motor1.setSpeed(speed);
                motor1.run(FORWARD);
                motor4.run(FORWARD);
                i+=2;

                // getStatus();
                // if(l=='1' && m1=='1' && m2=='1' && r=='1')
                // {
                //     motor4.setSpeed(0);
                //     motor1.setSpeed(0);
                //     motor1.run(RELEASE);
                //     motor4.run(RELEASE);
                // }
            }
        }

        

    }
}

void turn_Right()
{

    motor1.setSpeed(0);
    motor4.setSpeed(120);
    motor1.run(FORWARD);
    motor4.run(FORWARD);

    delay(570);

    motor1.setSpeed(0);
    motor4.run(BACKWARD);

    delay(50);
    
    motor1.run(RELEASE);
    motor4.run(RELEASE);

    delay(1000);
}

void turn_Left()
{
    stopTheCar();
    motor1.setSpeed(120);
    motor4.setSpeed(0);
    motor1.run(FORWARD);
    motor4.run(FORWARD);

    delay(460);

    motor4.setSpeed(0);
    motor1.run(BACKWARD);

    delay(50);
    
    motor1.run(RELEASE);
    motor4.run(RELEASE);

    delay(1000);
}

void reverse()
{
    motor1.setSpeed(150);
    motor4.setSpeed(150);

    motor1.run(BACKWARD);
    motor4.run(BACKWARD);
    delay(10);

    motor1.run(RELEASE);
    motor4.run(RELEASE);
    delay(100);
}

void stopTheCar()
{
    motor1.setSpeed(0);
    motor4.setSpeed(0);

    motor1.run(RELEASE);
    motor4.run(RELEASE);
}

void motorRun(String type, char l, char m1, char m2, char r)
{
    if(type == "Straight_Line")
    {
        Straight_Line();
    }
    else if(type == "Left")
    {
        turn_Left();
    }
    else if(type == "Right")
    {
        turn_Right();
    }
    else if(type == "Fork")
    {
        situationOfFork();
    }
}

void situationOfFork()
{
    motor1.setSpeed(50);
    motor4.setSpeed(50);
    if(chooseRoute(l, m1, m2, r) == "EMPTY")
    {
        /**/
    }
}

// for Stack
Position Stack[100];
int stackIndex=0;
int size = 100;

bool isEmpty()
{
    return stackIndex == 0;
}

bool isFull()
{
    return stackIndex == size;
}

void pop()
{
    stackIndex--;
}

void push(Position nowLocation)
{
    Stack[stackIndex++] = nowLocation;
}

Position top()
{
    return Stack[stackIndex-1];
}

// Depth_First_Search Algorithm (DFS)
void Depth_First_Search()
{
    int map[100][100];
    int start_X, start_Y;
    int end_X, end_Y;
    Position nowLocation;

    start_X = Serial.read();
    start_Y = Serial.read();
    end_X = Serial.read();
    end_Y = Serial.read();
    
    // 0-empty 1-wall 2-passed 3-deadend
    nowLocation = {start_X, start_Y};
    map[nowLocation.y][nowLocation.x] = 2;
    push(nowLocation);

    while(!isEmpty())
    {
        nowLocation = top();
        if(nowLocation.x == end_X && nowLocation.y == end_Y)
        {
            break;
        }

        //Right
        if(map[nowLocation.y][nowLocation.x+1]==0 && nowLocation.x+1<10)
        {
            map[nowLocation.y][nowLocation.x+1] = 2;
            push({nowLocation.x+1, nowLocation.y});
            continue;
        }

        //Left
        if(map[nowLocation.y][nowLocation.x-1]==0 && nowLocation.x-1>=0)
        {
            map[nowLocation.y][nowLocation.x-1] = 2;
            push({nowLocation.x-1, nowLocation.y});
            continue;
        }

        //Up
        if(map[nowLocation.y-1][nowLocation.x]==0 && nowLocation.y-1>=0)
        {
            map[nowLocation.y-1][nowLocation.x] = 2;
            push({nowLocation.x, nowLocation.y-1});
            continue;
        }

        //Down
        if(map[nowLocation.y+1][nowLocation.x]==0 && nowLocation.y+1<10)
        {
            map[nowLocation.y+1][nowLocation.x] = 2;
            push({nowLocation.x, nowLocation.y+1});
        }

        pop();
        map[nowLocation.y][nowLocation.x] = 3;

    }
}

// Show the available path
void showPath()
{
    if(isEmpty())
    {
        Serial.println("Sorry, we don't have available path.");
    }
    else
    {
        while(!isEmpty())
        {
            Position ans = top();
            Serial.print("( ");
            Serial.print(ans.x);
            Serial.print(", ");
            Serial.print(ans.y);
            Serial.print(" )");
            pop();
        }
        Serial.print('\n');
    }
    
}

// System setup
void setup() {
    
    Serial.begin(9600);
    Serial.begin(38400);
    //bluetooth.begin(9600); // 初始化藍芽序列埠

}

// Which route
String chooseRoute(char l, char m1, char m2, char r)
{
  String s1 = "Left";
  String s2 = "Right";
  String s3 = "Fork";
  String s4 = "Cross";
  String s5 = "Straight_Line";
  String s6 = "EMPTY";
  if((l == '0' && m1 == '0' && m2 == '0' && r == '1') || (l == '0' && m1 == '1' && m2 == '1' && r == '1'))
  {
        return s1; // Left
  }
  else if((l == '1' && m1 == '0' && m2 == '0' && r == '0') || (l == '1' && m1 == '1' && m2 == '1' && r == '0'))
  {
        return s2; // Right
  }
  else if(l == '0' && m1 == '0' && m2 == '0' && r == '0')
  {
        //motor1.setSpeed(RELEASE);
        //motor4.setSpeed(RELEASE);
        //motor1.setSpeed(10);
        //motor4.setSpeed(10);
        delay(100);
        if(l == '1' && m1 == '1' && m2 == '1' && r == '1')
        {
            return s3; // Fork
        }
        else if(l == '1' && m1 == '0' && m2 == '0' && r == '1')
        {
            return s4; // Cross
        }
  }
  else if(l == '1' && m1 == '0' && m2 == '0' && r == '1')
  {
        return s5; // Straight_Line
  }
  else if(l == '1' && m1 == '1' && m2 == '1' && r == '1')
  {
        return s5; // empty
  }
}

void getStatus()
{
    char t = '1'; char f = '0';      //black is 0;
    l  = digitalRead(trackPin_1000) == 0 ? t : f;
    m1 = digitalRead(trackPin_0100) == 0 ? t : f;
    m2 = digitalRead(trackPin_0010) == 0 ? t : f;
    r = digitalRead(trackPin_0001) == 0 ? t : f;
    /*bluetooth.print("@");
    bluetooth.print(l);
    bluetooth.print(m1);
    bluetooth.print(m2);
    bluetooth.print(r);
    bluetooth.println("#");
    */
}

void loop() {

    //Depth_First_Search();
    //showPath();

    getStatus();
    String route_type;
    route_type = chooseRoute(l, m1, m2, r);
    Serial.println(route_type);
    //bluetooth.println(route_type);
    motorRun(route_type,l, m1, m2, r);

}