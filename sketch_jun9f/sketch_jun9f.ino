int ledPin = 12;

int period = 100;

char mode = 'o';// o-끄기, s-스트로브, W-파도

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, 255);
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    char ch = Serial.read();
    if (ch=='0')
    {
      mode = 0;
      analogWrite(ledPin, 255);
     }
     else if (ch > '0' && ch <= '9')
     {
       setPeriod(ch);
     }
     else if (ch == 'w' || ch == 's')
     {
       mode = ch;
     }
  }
  if (mode == 'w')
  {
    waveLoop();
  }
  else if (mode == 's')
  {
    strobeLoop();
  }
}

void setPeriod(char ch)
{
  int period1to9 = 9 - (ch - '0');
  period = map(period1to9, 0, 9, 50, 500);
}

void waveLoop()
{
  static float angle = 0.0;
  angle = angle + 0.01;
  if (angle > 3.142)
  {
    angle = 0;
  }
  //analogWrite(ledPin, 255 - (int)255 * sin(angle)); //브래드보드
  analogWrite(ledPin, (int)255 * sin(angle)); //실드
  delay(period / 100);
}
void strobeLoop()
{
  //analogWrite(ledPin, 0); //브래드보드
  analogWrite(ledPin, 255); //실드
  delay(10);
  //analogWrite(ledPin, 255); //브래드보드
  analogWrite(ledPin, 0); //실드
  delay(period);
}