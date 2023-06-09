int red = 12;
void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  flash(200); flash(200); flash(200); //S
  delay(300);
  flash(500); flash(500); flash(500); // O
  flash(200); flash(200); flash(200); //S
  delay(1000);
}
void flash(int duration){
  digitalWrite(red, HIGH);
  delay(duration);
  digitalWrite(red, LOW);
  delay(duration);
}