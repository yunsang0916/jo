// 프로젝트29 릴리패드 시계
#include <TimeLib.h>

int hourLEDs[] = {1, 2, 3, 4};
// 최하위 비트(LSB) 먼저
int minuteLEDs[] = {10, 9, 8, 7, 6, 5};
int secondLEDs[] = {17, 16, 15, 14, 13, 12};

int loopLEDs[] = {17, 16, 15, 14, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

int switchPin = 18;

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 4; i++)
  {
    pinMode(hourLEDs[i], OUTPUT);
  }
  for (int i = 0; i < 6; i++)
  {
    pinMode(minuteLEDs[i], OUTPUT);
  }
  for (int i = 0; i < 6; i++)
  {
    pinMode(secondLEDs[i], OUTPUT);
  }
  setTime(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(switchPin))
  {
    adjustTime(1);
  }
  else if (minute() == 0 && second() == 0)
  {
    spin(hour());
  }
  updateDisplay();
  delay(1);
}

void updateDisplay()
{
  time_t t = now();
  setOutput(hourLEDs, 4, hourFormat12(t));
  setOutput(minuteLEDs, 6, minute(t));
  setOutput(secondLEDs, 6, second(t));
}

void setOutput(int *ledArray, int numLEDs, int value)
{
  for (int i = 0; i < numLEDs; i++)
  {
    digitalWrite(ledArray[i], bitRead(value, i));
  }
}

void spin(int count)
{
  for (int i = 0; i < count; i++)
  {
    for (int j = 0; j < 16; j++)
    {
    digitalWrite(loopLEDs[j], HIGH);
    delay(50);
    digitalWrite(loopLEDs[j], LOW);
    }
  }
}
// LED를 세 개의 묶음으로 나눠 배열에 저장한다. 이 배열을 사용해 LED 설정과 setOutput 함수를 단순화한다. 이 함수는 LED 배열의 이진값을 설정해 이진수를 표시한다. 또 이 함수는 LED 배열의 길이와 그 배열에 대입할 값도 인수로 받는다.
// loop 함수 안에서 시, 분, 초에 따라 LED를 차례대로 설정할 때 이 함수를 호출한다. 이번처럼 함수에 배열을 넘길 때는 함수를 정의할 때 인수 앞에 반드시 별표를 붙여야 한다. 이 시계에는 매시간 정각마다 LED를 차례대로 켜면서 회전하는 기능도 있다 
// 리드 릴레이가 켜지면, adjustTime 함수가 호출되고 1초가 인수로 넘겨진다.
// 1ms 동안 delay를 호출하는 loop 함수 안에서 이 작업이 이루어지기 때문에 빠르게 지나갈 것이다.