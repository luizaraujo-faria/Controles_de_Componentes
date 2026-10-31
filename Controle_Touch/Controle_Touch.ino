const int touch = 2;
const int ledAmarelo = 3;
const int ledVerde = 4;

void setup() {
  pinMode(touch, INPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int estado = digitalRead(touch);

  if(estado == HIGH){
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVerde, LOW);
  }
  else{
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, HIGH);
  }

  delay(50);
}
