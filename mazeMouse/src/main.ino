#include <Arduino.h>
#include <Servo.h>
#include <AFMotor.h>

// Sensor setup
const int trackPin_1000 = A5;
const int trackPin_0100 = A4;
const int trackPin_0010 = A3;
const int trackPin_0001 = A2;
char lineState[5];

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
void Straight_Line(char l, char m1, char m2, char r)
{
    double speed = 200*0.85;
    motor1.setSpeed(speed);
    motor4.setSpeed(200);
    
    motor1.run(FORWARD);
    motor4.run(FORWARD);
    // while(true)
    // {
    //     motor1.run(FORWARD);
    //     motor4.run(FORWARD);
    //     if(l=='0' && r =='0')
    //     {
    //         if(m1=='1')
    //     }
    // }

}

void turn_Right()
{
    motor1.setSpeed(200);
    motor4.setSpeed(250);

    motor1.run(FORWARD);
    motor4.run(FORWARD);
}

void turn_Left()
{
    motor1.setSpeed(100);
    motor4.setSpeed(50);

    motor1.run(FORWARD);
    motor4.run(FORWARD);
}

void reverse()
{
    motor1.setSpeed(200);
    motor4.setSpeed(200);

    motor1.run(BACKWARD);
    motor4.run(BACKWARD);
}

void stopTheCar()
{
    motor1.run(RELEASE);
    motor4.run(RELEASE);
}

void motorRun(String type, char l, char m1, char m2, char r)
{
    if(type == "Straight_Line")
    {
        Straight_Line(l, m1, m2, r);
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
    if(chooseRoute(lineState[0], lineState[1], lineState[2], lineState[3]) == "EMPTY")
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
  if(l == '0' && m1 == '0' && m2 == '0' && r == '1')
  {
        return s1; // Left
  }
  else if(l == '1' && m1 == '0' && m2 == '0' && r == '0')
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

void loop() {
    
    char t = '1'; char f = '0';      //black is 0;
    lineState[0] = digitalRead(trackPin_1000) == 0 ? t : f;
    lineState[1] = digitalRead(trackPin_0100) == 0 ? t : f;
    lineState[2] = digitalRead(trackPin_0010) == 0 ? t : f;
    lineState[3] = digitalRead(trackPin_0001) == 0 ? t : f;
    //Depth_First_Search();
    //showPath();

    String route_type;
    route_type = chooseRoute(lineState[0], lineState[1], lineState[2], lineState[3]);
    motorRun(route_type, lineState[0], lineState[1], lineState[2], lineState[3]);

    delay(100);
}