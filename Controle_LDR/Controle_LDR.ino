const int ldr = A0;
const int ledVerde = 2;

const int limiteLuz = 500;

void setup() {
  pinMode(ledVerde, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int luminosidade = analogRead(ldr);

  Serial.println(luminosidade);

  if (luminosidade < limiteLuz) {
    // Está escuro
    digitalWrite(ledVerde, HIGH);
  } 
  else {
    // Há luz
    digitalWrite(ledVerde, LOW);
  }

  delay(100);
}


