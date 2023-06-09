int redPin = 12;
int sensorPin = 0;
double alpha = 0.75;
int period = 20;
double change = 0.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  static double oldValue = 0;
  static double oldChange = 0;
  int rawValue = analogRead(sensorPin);
  double value = alpha * oldValue + (1 - alpha) * rawValue;
  change = value - oldValue;
  digitalWrite(redPin, (change < 0.0 && oldChange > 0.0));
  oldValue = value;
  oldChange = change;
  delay(period);
}
