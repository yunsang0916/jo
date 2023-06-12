// 프로젝트 18 - 오실로스코프
int analogPin = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(analogPin);
  byte data = (value >> 2);
  Serial.write(data);
}
