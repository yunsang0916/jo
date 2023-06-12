// 프로젝트 26 거짓말 탐지기
int redPin = 11; 
int greenPin = 10;
int bluePin = 9;
int buzzerPin = 7;

int potPin = 1;
int sensorPin = 0;

long red = 0xFF0000;
long green = 0x00FF00;
long blue = 0x000080;

int band = 10;
// 감도 조정용

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int gsr = analogRead(sensorPin);
  int pot = analogRead(potPin);
  if (gsr > pot + band)
  {
    setColor(red);
    beep();
  }
  else if (gsr < pot - band)
  {
    setColor(blue);
  }
  else
  {
    setColor(green);
  }
}

void setColor(long rgb)
{
  int red = rgb >> 16;
  int green = (rgb >> 8) & 0xFF;
  int blue = rgb & 0xFF;
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void beep()
{
  // 5분의 1초간 5Khz
  for (int i = 0; i < 1000; i++)
  {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(100);
  }
}
// 이 프로젝트의 스크립트는 A0과 A1의 전압을 비교하는 것이 전부다. 두 핀의 전압이 거의 비슷하면 LED는 초록색으로 설정될 것이다.
// 손가락 센서(A0)에서 읽은 전압이 A1보다 상당히 높으면 가변 저항이 피부 저항의 저하를 일으켜서 LED가 빨간색으로 바뀌고 부저가 울릴 것이다. 
// 반면 A0가 A1보다 상당히 낮으면 LED 색이 파란색으로 변해 피부 저항이 상승했음을 알릴 것이다. 부저를 울리려면 초당 5000번, 즉 5Khz의 주파수가 필요하다.
// 적당한 핀을 시간 간격을 두고 켜고 끄는 명령을 내리는 간단한 for 반복문으로 이 주파수를 만들어낼 수 있다.