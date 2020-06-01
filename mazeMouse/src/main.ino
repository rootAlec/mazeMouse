#include <Arduino.h>
#include <Servo.h>

// Sensor setup
const int trackPin_1000 = A5;
const int trackPin_0100 = A4;
const int trackPin_0010 = A3;
const int trackPin_0001 = A2;
char lineState[5];

// Motor setup




// Struct setup
struct Position
{
    int x;
    int y;
};

// Make motor run
void motorRun(String type)
{
    if(type == "Left")
    {
        /**/
    }
    else if(type == "Right")
    {
        /**/
    }
    else if(type == "Fork")
    {
        /**/
    }
    else if(type == "Straight_Line")
    {
        /**/
    }
}

// for Depth_First_Search


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
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            map[i][j] = Serial.read();           
        }
    }
    
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
String chooseRoute(char l, char r)
{
  String s1 = "Left";
  String s2 = "Right";
  String s3 = "Fork";
  String s4 = "Straight_Line";
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
  //Depth_First_Search();
  //showPath();
  String route_type;
  route_type = chooseRoute(lineState[0], lineState[3]);
  Serial.println(route_type);
  //motorRun(route_type);
  delay(100);
  
}
