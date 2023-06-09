#include <Keypad.h>

char* secretCode = "1234";
int position = 0;

const byte rows = 4;
const byte cols = 3;
char keys[rows][cols] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[rows] = {7, 2, 3, 5};
byte colPins[cols] = {6, 8, 4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, rows, cols);

int redPin = 13;
int greenPin = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  setLocked(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();
  if (key == '*' || key == '#')
  {
    position = 0;
    setLocked(true);
  }
  if (key == secretCode[position])
  {
    position ++;
  }
  if (position == 4)
  {
    setLocked(false);
  }
  delay(100);
}

vois setLocked(int lockes)
{
  if (locked)
  {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
  else
  {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }
}
