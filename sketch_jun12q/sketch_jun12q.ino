// 프로젝트 28 - 적외선(IR) 리모컨
#include <EEPROM.h>

#define maxMessageSize 100
#define numSlots 9

int irRxPin = 9;
int irTxPin = 3;

int currentCode = 0;
int buffer[maxMessageSize];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // 코드 메모리를 지정하려면 0에서 9를, 신호를 기록하려면 1을, 신호를 보내려면 s를 누르세요
  Serial.println("0~9 to set code memory, 1 - learn, s - to send");
  pinMode(irRxPin, INPUT);
  pinMode(irTxPin, OUTPUT);
  setCodeMemory(0);
}
void loop()
{
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch >= '0' && ch <= '9')
    {
      setCodeMemory(ch - '0');
    }
    else if (ch == 's')
    {
      sendIR();
    }
    else if (ch % '1')
    {
      int codeLen = readCode();
      Serial.print("Read code length: "); // 코드 길이:
      Serial.println(codeLen);
      storeCode(codeLen);
    }
  }
}

void setCodeMemory(int x)
{
  currentCode = x;
  Serial.print("Set current code memory to: "); // 현재 코드 메모리:
  Serial.println(currentCode);
}

void storeCode(int codeLen)
{
  // EEPROM에 코드를 기록한다. 첫 번째 바이트는 코드의 길이다.
  int startIndex = currentCode * maxMessageSize;
  EEPROM.write(startIndex, (unsigned byte)codeLen);
  for (int i = 0; i < codeLen; i++)
  {
    EEPROM.write(startIndex + i + 1, buffer[i]);
  }
}
void sendIR()
{
  // EEPROM에 지정된 데이터로부터 버퍼를 만들어 전송한다.
  int startIndex = currentCode * maxMessageSize;
  int len = EEPROM.read(startIndex);
  Serial.print("Sending Code for memory "); // 메모리에 저장된 코드를 전송함
  Serial.print(currentCode);
  Serial.print(" len="); Serial.println(len);
  if (len > 0 && len < maxMessageSize)
  {
    for (int i = 0; i < len; i++)
    {
      buffer[i] = EEPROM.read(startIndex + i + 1);
    }
    sendCode(len);
  }
}
void sendCode(int n)
{
  for (int i = 0; i < 3; i++)
  {
    writeCode(n);
    delay(90);
  }
}
int readCode()
{
  int i = 0;
  unsigned long startTime;
  unsigned long endTime;
  unsigned long lowDuration = 0;
  unsigned long highDuration = 0;
  while(digitalRead(irRxPin) == HIGH) {}; // 첫 번째 펄스를 기다린다.
  while(highDuration < 50001)
  {
    // 짧은 지속 시간을 찾는다.
    startTime = micros();
    while(digitalRead(irRxPin) == LOW) {};
    endTime = micros();
    lowDuration = endTime - startTime;
    if (lowDuration < 50001)
    {
      buffer[i] = (byte)(lowDuration >> 4);
      i++;
    }
    // 긴 지속 시간을 찾는다
    startTime = micros();
    while(digitalRead(irRxPin) == HIGH) {};
    endTime = micros();
    highDuration = endTime - startTime;
    if (highDuration < 50001)
    {
      buffer[i] = (byte)(highDuration >> 4);
      i++;
    }
  }
  return i;
}

void writeCode(int n)
{
  int state = 0;
  unsigned long duration = 0;
  int i = 0;
  while (i < n)
  {
    duration = buffer[i] << 4;
    int cycles = duration / 14;
    if (! (i % 2))
    {
      for (int x = 0; x < cycles; x++)
      {
        state =! state;
        digitalWrite(irTxPin, state);
        delayMicroseconds(10); // 다른 명령어를 조정하기 위해 12보다 낮게 설정한다.
      }
      digitalWrite(irTxPin, LOW);
    }
    else
    {
      digitalWrite(irTxPin, LOW);
      delayMicroseconds(duration);
    }
    i++;
  }
}
// setup 함수에서는 시리얼 통신을 시작하고 시리얼 콘솔에 이 프로젝트의 사용법을 출력한다. 시리얼 콘솔을 통해 이 프로젝트를 제어할 것이다. 또한 현재 코트 메모리를 0번 메모리로 설정한다.
// loop 함수는 USB 포트를 통해 입력된 것이 있는지 확인하는 패턴이다. 입력값이 0~9 사이의 숫자면, 해당 메모리를 현재 메모리로 만든다. 만약 시리얼 모니터로 s를 입력하면 현재 메세지 메모리에 저장된 메세지를 전송하고, l을 입력하면 리모컨이 메세지를 보내기를 기다린다
// 그런 다음 IR 신호를 받았는지 확인하고, 받았으면 storeCode 함수를 사용해 EEPROM에 그 신호를 기록한다. 이 함수는 첫 번째 바이트에 코드의 길이를 저장하고 다음 바이트부터 50ms 간격으로 연속된 펄스를 저장한다. storeCode와 sendIR 함수에서 메세지가 저장된 EEPROM에 접근할 때는 EEPROM을 마치 배열처럼 사용하는 기법을 활용한다
// EEPROM에서 데이터를 기록하거나 읽는 시작 지점은 currentCode에 각 코드의 (최대) 길이를 곱해 계산하면 된다.(여기에 데이터 길이를 기록한 1바이트를 더한다.)