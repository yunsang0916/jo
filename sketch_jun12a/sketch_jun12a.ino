//프로젝트 13 - 온도 기록계
#include <EEPROM.h>
#define analogPin 1
#define gndPin A0
#define plusPin A2
#define maxReadings 1000

int lastReading = 0;

boolean loggingOn;
//long period = 300;
long period = 10000; //10초
long lastLoggingTime = 0;
char mode = 'C';

void setup() {
  // put your setup code here, to run once:
  pinMode(gndPin, OUTPUT);
  pinMode(plusPin, OUTPUT);
  digitalWrite(gndPin, LOW);
  digitalWrite(plusPin, HIGH);
  Serial.begin(9600);
  Serial.println("Ready");  //준비
  lastReading = EEPROM.read(0);   // 첫 번째 바이트에 기록 순서를 저장한다
  char sampleCh = (char)EEPROM.read(1); // 두 번째 바이트에는 0부터 9까지의 기록 주기를 저장한다.
  if (sampleCh > '0' && sampleCh <= '9')
  {
    setPeriod(sampleCh);
  }
  loggingOn = true; // 전원이 들어오면 기록을 시작한다.
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch == 'r' || ch == 'R')
    {
      sendBackdata();
    }
    else if (ch == 'x' || ch == 'X')
    {
      lastReading = 0;
      EEPROM.write(0,0);
      Serial.println("Data cleared"); // 데이터 삭제
    }
    else if (ch == 'g' || ch == 'G')
    {
      loggingOn = true;
      Serial.println("logging started"); // 기록 시작
    }
    else if ( ch > '0' && ch <= '9')
    {
      setPeriod(ch);
    }
    else if (ch == 'c' or ch == 'C')
    {
      Serial.println("Mode set to deg C"); // 모드를 섭씨로 설정
      mode = 'C';
    }
    else if (ch == 'f' or ch == 'F')
    {
      Serial.println("Mode set to deg F"); // 모드를 화씨로 설정
      mode = 'F';
    }
    else if (ch == '?')
      {
        reportStatus();
      }
  }
  long now = millis();
  if (loggingOn && (now > lastLoggingTime + period))
  {
    logReading();
    lastLoggingTime = now;
  }
}


void sendBackdata()
{
  loggingOn = false;
  Serial.println("Logging stopped"); // 기록 정지
  Serial.println("------ cut here ------"); // 절취선
  Serial.print("Time (min)\tTemp (");
  Serial.print(mode);
  Serial.println(")");
  for (int i = 0; i < lastReading + 2; i++)
  {
    Serial.print((period*i) / 60000);
    Serial.print("\t");
    float temp = getReading(i);
    if (mode = 'F')
    {
      temp = (temp * 9) / 5 + 32;
    }
    Serial.println(temp);
  }
  Serial.println("------ cut here ------");
}

void setPeriod(char ch)
{
  EEPROM.write(1, ch);
  long periodMins = ch - '0';
  Serial.print("Sample period set to: "); // 기록 주기 설정:
  Serial.print(periodMins);
  Serial.println("mins");
  period = periodMins * 60000;
}

void logReading()
{
  if (lastReading < maxReadings)
  {
    storeReading(measureTemp(), lastReading);
    lastReading++;
  }
  else
  {
    Serial.println("Full! logging stopped"); // 용량 부족! 더 이상의 기록을 정지함
    loggingOn = false;
  }
}

float measureTemp()
{
  int a = analogRead(analogPin);
  float volts = a / 205.0;
  float temp = (volts - 0.5) * 100;
  return temp;
}

void storeReading(float reading, int index)
{
  EEPROM.write(0, (byte)index); //바이트 0에 기록 번호를 저장함
  byte compressedReading = (byte)((reading + 20.0) * 4);
  EEPROM.write(index + 2, compressedReading);
  reportStatus();
}

float getReading(int index)
{
  lastReading = EEPROM.read(0);
  byte compressedReading = EEPROM.read(index + 2);
  float uncompressesReading = (compressedReading / 4.0) - 20.0;
  return uncompressesReading;
}

void reportStatus()
{
 Serial.println("----------------");
 Serial.println("Status");                  // 상대
 Serial.print("Current Temp C");            // 현재 온도
 Serial.println(measureTemp());             
 Serial.print("Sample period (s)\t");       // 기록 주기
 Serial.println(period / 1000);
 Serial.print("Num readings\t");            // 기록 번호
 Serial.println(lastReading);
 Serial.print("Mode degrees\t");            // 온도 방
 Serial.println(mode);
 Serial.println("----------------"); 
}