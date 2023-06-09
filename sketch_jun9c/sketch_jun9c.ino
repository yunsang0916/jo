int ledPin = 4;
int yellowPin = 3;
int greenPin = 2;
int buttonPin = 5;

int state = 0;

void setup() 
{
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(buttonPin))
  {
    if (state == 0)
    {
      setLights(HIGH, LOW, LOW);
      state = 1;
    }
    else if (state == 1)
    {
      setLights(HIGH, HIGH, LOW);
      state = 2;
    }
    else if (state == 2)
    {
      setLights(LOW, LOW, HIGH);
      state = 3;
    }
    else if (state == 3)
    {
      setLights(LOW, HIGH, LOW);
      state = 0;
    }
    delay(1000);
  }
}

void setLights(int led, int yellow, int green)
{
  digitalWrite(ledPin, led);
  digitalWrite(yellowPin, yellow);
  digitalWrite(greenPin, green);
}
