const int sensorPIR = 2;
const int ledAmarelo = 3;
const int ledVerde = 4;

void setup() {
  pinMode(sensorPIR, INPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int movimento = digitalRead(sensorPIR);

  if (movimento == HIGH) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    Serial.println("Movimento detectado!");
  } 
  else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
  }

  delay(100);
}
