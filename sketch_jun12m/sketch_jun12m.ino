// 프로젝트 24 - 최면 장치

int enable1Pin = 11;
int in1Pin = 10;
int in2Pin = 9;

int speeds[] = {80, 100, 160, 240, 250, 255, 250, 240, 160, 100, 80, -80, -100, -160, -240, -250, -255, -250, -240, -160, -100, -80};

int i = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(enable1Pin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int speed = speeds[i];
  i++;
  if (i == 22)
  {
    i = 0;
  }
  drive(speed);
  delay(1500);
}

void drive(int speed)
{
  if (speed > 0)
  {
    analogWrite(enable1Pin, speed);
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
  }
  else if (speed < 0)
  {
    analogWrite(enable1Pin, -speed);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
  }
}
// 이 스케치는 speeds 배열을 사용해 원판의 진행 상태를 제어한다. 덕분에 우리는 원판을 한쪽 방향으로 계속 빠르게 돌린 다음 방향이 반대로 바뀔 때까지 천천히
// 속도를 늦추다가 방향이 바뀌고 나면 바뀐 방향으로 점점 빠르게 돌리기를 반복할 수 있다. 모터마다 배열 안에 저장해야 하는 속도가 다르기 때문에 값을 조정해야만 한다.