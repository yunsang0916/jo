// 프로젝트 20 빛 하프
int soundPin = 11;
int pitchInputPin = 0;
int volumeInputPin = 1;
int ldrDim = 400;

int ldrBright = 800;

byte sine[] = {0, 22, 44, 64, 82, 98, 111, 120, 126, 127, 126, 120, 111, 98, 82, 64, 44, 22, 0, -22, -44, -64, -82, -98, -111, -120, -126, -128, -126, -120, -111, -98, -82, -64, -44, -22};

long lastCheckTime = millis();
int pitchDelay;
int volume;

void setup() {
  // put your setup code here, to run once:
 // PWM 주파수를 63kHz로 변경한다.
 cli(); //레지스터를 설정하는 동안 인터럽트를 막는다.
 bitSet(TCCR2A, WGM20);
 bitSet(TCCR2A, WGM21); // Timer2를 빠른 PWM 모드로 바꾼다(PWM 주파수를 두 배로 높인다)
 bitSet(TCCR2B, CS20);
 bitClear(TCCR2B, CS21);
 bitClear(TCCR2B, CS22);
 sei(); // 레지스터 설정을 마쳤으니 다 인터럽트를 받는다.
 pinMode(soundPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long now = millis();
  if (now > lastCheckTime + 20L)
  {
    pitchDelay = map(analogRead(pitchInputPin), ldrDim, ldrBright, 10, 30);
    volume = map(analogRead(volumeInputPin), ldrDim, ldrBright, 1, 4);
    lastCheckTime = now;
  }
  playSine(pitchDelay, volume);
}

void playSine(int period, int volume)
{
  for( int i = 0; i < 36; i++)
  {
    analogWrite(soundPin, (sine[i] / volume) + 128);
    delayMicroseconds(period);
  }
}