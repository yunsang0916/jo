int redPin = 13;
int yellowPin = 12;
int greenPin = 11;
int aPin = 4;
int bPin = 2;
int buttonPin = 3;

int state = 0;
int longPeriod = 5000; //초록색이나 빨간색일 때 불이 들어오는 시간
int shortPeriod = 700; //신호가 바뀔떄의 시간
int targetCount = shortPeriod;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(aPin, INPUT_PULLUP);
  pinMode(bPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  count++;
  if (digitalRead(buttonPin) == LOW)
  {
    setLights(HIGH, HIGH, HIGH);
  }
  else
  {
    int change = getEncoderTurn();
    int newPeriod = longPeriod + (change * 1000);
    if (newPeriod >= 1000 && newPeriod <= 10000)
    {
      longPeriod = newPeriod;
    }
    if (count > targetCount)
    {
      setState();
      count = 0;
    }
  }
  delay(1);
}

int getEncoderTurn()
{
  // -1, 0 , +1 중 하나를 변환한다 
  static int oldA = LOW;
  static int oldB = LOW;
  int result = 0;
  int newA = digitalRead(aPin);
  int newB = digitalRead(bPin);
  if (newA != oldA || newB != oldB)
  {
    //바뀐 값이 있을 때
    if (oldA == LOW && newA == HIGH)
    {
      result = -(oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
  }

  int setState()
  {
    if (state == 0)
    {
      setLights(HIGH, LOW, LOW);
      targetCount = longPeriod;
      state = 1;
    }
    else if (state == 1)
  {
     setLights(HIGH, HIGH, LOW);
      targetCount = shortPeriod;
      state = 2;
  }
  else if (state == 2)
  {
     setLights(LOW, LOW, HIGH);
      targetCount = longPeriod;
      state = 3;
  }
  else if (state == 3)
  {
     setLights(LOW, HIGH, LOW);
      targetCount = shortPeriod;
      state = 0;
  }
}

void setLights(int red, int yellow, int green)
{
  digitalWrite(redPin, red);
  digitalWrite(yellow, yellow);
  digitalWrite(green, green);
}

