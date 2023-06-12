// 프로젝트 22 - LCD 온도 조절기
#include <LiquidCrystal.h>

// LiquidCrystal(rs, rw, enable, d4, d5, d6, d7)
LiquidCrystal lcd(2, 3, 4, 9, 10, 11, 12);

int relayPin = A3;
int aPin = A4;
int bPin = A1;
int buttonPin = A2;
int analogPin = A0;

float setTemp = 20.0;
float measuredTemp;
char mode = 'C'; // F로 바꿀 수 있다
boolean override = false;
float hysteresis = 0.25;

void setup() {
  // put your setup code here, to run once:
   lcd.begin(2, 16);
   pinMode(relayPin, OUTPUT);
   pinMode(aPin, INPUT_PULLUP);
   pinMode(bPin, INPUT_PULLUP);
   pinMode(buttonPin, INPUT_PULLUP);
   lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  static int count = 0;
  measuredTemp = readTemp();
  if (digitalRead(buttonPin) == LOW)
  {
    override = ! override;
    updateOutput();
    count = 0;
  }
  count ++;
}

int getEncoderTurn()
{
  // -1, 0, +1 중 하나를 반환
  static int oldA = LOW;
  static int oldB = LOW;
  int result = 0;
  int newA = digitalRead(aPin);
  int newB = digitalRead(bPin);
  if (newA != oldA || newB != oldB)
  {
    // 바뀐 값이 있음
    if (oldA == LOW && newA == HIGH)
    {
      result = -(oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
}
float readTemp()
{
  int a = analogRead(analogPin);
  float volts = a / 205.0;
  float temp = (volts - 0.5) * 100;
  return temp;
}

void updateOutput()
{
  if (override || measuredTemp < setTemp - hysteresis)
  {
    digitalWrite(relayPin, HIGH);
  }
  else if (!override && measuredTemp > setTemp + hysteresis)
  {
    digitalWrite(relayPin, LOW);
  }
}

void updateDisplay()
{
  lcd.setCursor(0,0);
  lcd.print("Actual: ");
  lcd.print(adjustUnits(measuredTemp));
  lcd.print(" o");
  lcd.print(mode);
  lcd.print(" ");
  lcd.setCursor(0,1);
  if (override)
  {
    lcd.print(" OVERRIDE ON");
  }
  else
  {
    lcd.print("Set: ");
    lcd.print(adjustUnits(setTemp));
    lcd.print("o");
    lcd.print(mode);
    lcd.print(" ");
  }
}

float adjustUnits(float temp)
{
  if (mode == 'C')
  {
    return temp;
  }
  else
  {
    return (temp * 9) / 5 + 32;
  }
}