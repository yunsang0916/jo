int led = 12;

char*letters[] = {
  ".-", "-...","-.-.","-..",".","..-.","--.","....","..", //A~I
  ".---","-.-",".-..","--","-.","---",".--.","--.-",".-.",//J~R
  "...","-","..-","...-",".--","-..-","-.--","--.."//S~Z
};

char* numbers[] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};//1~9

int dotDelay = 200;

void setup() {
  // put your setup code here, to run once:
pinMode(led, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  char ch;
  if (Serial.available())// USB에서 어떤 것이 읽혔는가?
  {
    ch = Serial.read();// read a single letter
    if (ch >= 'a'&& ch <= 'z')
    {
      flashSequence(letters[ch - 'a']);
    }
    else if (ch >= 'A'&& ch <= 'Z')
    {
      flashSequence(letters[ch - 'A']);
    }
    else if (ch >= '0'&& ch <= '9')
    {
      flashSequence(numbers[ch - '0']);
    }
    else if (ch == ' ')
    {
      delay(dotDelay * 4);//단어 사이의 간격
    }
  }
}

void flashSequence(char* sequence)
{
  int i = 0;
  while (sequence[i] != NULL)
  {
    flashDotOrDash(sequence[i]);
    i++;
  }
  delay(dotDelay * 3); //단어 사이의 간격
}

void flashDotOrDash(char dotOrDash)
{
  digitalWrite(led, HIGH);
  if (dotOrDash == '.')
  {
    delay(dotDelay);
  } 
  else // a -가 필요함
  {
    delay(dotDelay * 3);
  }
  digitalWrite(led, LOW);
  delay(dotDelay); //플래시 사이의 간격
}