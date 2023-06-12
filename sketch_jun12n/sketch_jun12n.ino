//서보로 조종하는 레이저
#include <Servo.h>

int laserPin = 4;
Servo servoV;
Servo servoH;

int x = 90;
int y = 90;
int minX = 10;
int maxX = 170;
int minY = 50;
int maxY = 130;

void setup() {
  // put your setup code here, to run once:
  servoH.attach(3);
  servoV.attach(2);
  pinMode(laserPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char ch;
  if (Serial.available())
  {
    ch = Serial.read();
    if (ch == '0')
    {
      digitalWrite(laserPin, LOW);
    }
    else if (ch == '-')
    {
      delay(100);
    }
    else if (ch == 'c')
    {
      x = 90;
      y = 90;
    }
    else if (ch == '1' || ch == 'r' || ch == 'u' || ch == 'd')
    {
      moveLaser(ch, 1);
    }
    else if (ch == 'L' || ch == 'R' || ch == 'U' || ch == 'D')
    {
      moveLaser(ch, 5);
    }
  }
  servoH.write(x);
  servoV.write(y);
  delay(15);
}

void moveLaser(char dir, int amount)
{
  if ((dir == 'r' || dir == 'R') && x > minX)
  {
    x = x - amount;
  }
  else if ((dir == 'l' || dir == 'L') && x < maxX)
  {
    x = x + amount;
  }
  else if ((dir == 'u' || dir == 'U') && y < maxY)
  {
    y = y + amount;
  }
  else if ((dir == 'd' || dir == 'D') && x > minY)
  {
    y = y - amount;
  }
}
// USB 케이블을 동태 명령을 보낼 수 있도록 만든다. 명령어는 글자. 대문자 R, L, U, D는 각각 레어저를 오른쪽, 왼쪽, 위쪽, 아래쪽으로 5도씩 기울인다. 
// r, l, u, d는 더 섬세하게 1도씩 움직인다. 빛을 그만 쏘거나 레이저 이동을 멈추려면 대시(-) 문자를 보내면 된다.
// 3가지 명령어가 더 있다. c는 레이저를 기본 위치인 가운데로 움직이고, 1과 0은 각각 레이저를 켜고 끈다.