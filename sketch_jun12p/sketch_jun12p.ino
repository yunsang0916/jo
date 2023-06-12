// 프로젝트 27 키패드 도어록
#include <keypad.h>
#include <EEPROM.h>

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

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

int redPin = 13;
int greenPin = 12;
int solenoidPin = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(solenoidPin, OUTPUT);
  loadCoad();
  flash();
  lock();
  Serial.begin(9600);
  while(!Serial);
  Serial.print("Code is: ")
  Serial.println(secretCode);
  Serial.println("Change code: cNNNN"); // 비밀번호 변경: cNNNN
  Serial.println("Unlock: u") //잠금 해제 : u
  Serial.println("Lock: l") // 잠금 : l
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == 'u')
    {
      unlock();
    }
    if (c == 'l')
    {
      lock();
    }
    if (c == 'c')
    {
      getNewCode();
    }
  }
  char key = keypad.getKey();
  if (key == '#')
  {
    lock();
  }
  if (key == secretCode[position])
  {
    position ++;
  }
  else if (key != 0)
  {
    lock;
  }
  if (position == 4)
  {
    unlock();
  }
  delay(100);
}

void lock()
{
  position = 0;
  digitalWrite(redPin, HIGH);
  digitalErite(greenPin, LOW);
  Serial.println("LOCKED");
}

void unlock()
{
  digitalWrite(redPin, LOW);
  digitalErite(greenPin, HIGH);
  digitalWrite(solenoidPin, HIGH);
  Serial.println("UN-LOCKED");
  delay(5000);
  lock();
}

void getNewCode()
{
  for (int i = 0; i < 4; i++ )
  {
    char ch = Serial.read();
    secretCode[i] = ch;
  }
  saveCode();
  flash();flash();
  Serial.print("Code changed to:");
  Serial.println(secretCode);
}

void loadCode()
{
  if (EEPROM.read(0) == 1)
  {
    secretCode[0] = EEPROM.read(1);
    secretCode[1] = EEPROM.read(2);
    secretCode[2] = EEPROM.read(3);
    secretCode[3] = EEPROM.read(4);
  }
}

void saveCode()
{
  EEPROM.write(1, secretCode[0]);
  EEPROM.write(2, secretCode[1]);
  EEPROM.write(3, secretCode[2]);
  EEPROM.write(4, secretCode[3]);
  EEPROM.write(0, 1);
}

void flash()
{
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  delay(500);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
}

// 외장 어댑터로 이 프로젝트에 전원을 공급했지만 여전히 컴퓨터와 USB 선으로 연결해 문을 열거나 비밀번호를 바꾸는 등의 명령을 내릴 수 있다.
// setup 함수는 시리얼 모니터를 사용해 비밀번호를 바꾸는 방법을 출력한다. 현재 비밀번호도 함께 출력한다.
// loop 함수는 두 부분으로 나뉜다. 먼저, 시리얼 모니터에서 들어오는 명령어를 기다린 다음, 키가 눌렸는지 확인한다.  어떤 키가 눌렸을 때, 그 키가 비밀번호의 해당 순서의 숫자와 일치하면 count 변수에 1을 더한다. count의 값이 4가 되면 도어록이 열린다.
// 한 문자는 정확히 1바이트이므로, 비밀번호를 EEPROM에 바로 저장할 수 있다. EEPROM의 첫 번째 바이트에는 비밀번호 설정 여부를 표시하기 위해 사용한다. 아직 비밀번호가 설정되지 않았을 경우 기본 비밀번호는 1234이다. 비밀번호를 설정하면 EEPROM의 첫 번째 바이트가 1로 설정될 것이다.