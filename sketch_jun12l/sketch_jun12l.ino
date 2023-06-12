// 프로젝트 23 - 컴퓨터 조종 선풍기
int motorPin = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);
  analogWrite(motorPin, 0);
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch >= '0' && ch <= '9')
    {
      int speed = ch - '0';
      if (speed == 0)
      {
        analogWrite(motorPin, 0);
      }
      else
      {
      analogWrite(motorPin, 150 + speed * 10);
      }
    }
  }
}
// USB로 0~9의 숫자를 읽고, 이 숫자에 10을 곱한 다음 150을 더한 값과 motorPin을 analogWrite 함수를 호출할 때 매개변수로 입력하면 된다.
// 이러면 150~240 사이의 숫자를 얻을 수 있는데, 150의 여유값을 두는 이유는 팬은 전압이 일정 크기 이상 될때까지 움직이지 않기 때문이다.