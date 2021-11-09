int Ir = A0;

void setup() {
// put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Ir, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int left = analogRead(Ir);
  Serial.println(left);
}
