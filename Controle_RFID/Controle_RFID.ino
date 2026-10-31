
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PINO_SDA 10
#define PINO_RST 9

#define LARGURA_TELA 128
#define ALTURA_TELA 64
#define ENDERECO_OLED 0x3C

const int buzzer = 4;

MFRC522 rfid(PINO_SDA, PINO_RST);

Adafruit_SSD1306 display(
  LARGURA_TELA,
  ALTURA_TELA,
  &Wire,
  -1
);

void mostrarInicio() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("LEITOR RFID");
  display.println("---------------------");
  display.println();
  display.println("Aproxime seu");
  display.println("cartao ou chaveiro");

  display.display();
}

void setup() {
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);

  // Inicializa o display I2C
  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        ENDERECO_OLED)) {
    Serial.println("Erro ao iniciar OLED!");
    while (true) {}
  }

  mostrarInicio();

  // Inicializa o leitor RFID SPI
  SPI.begin();
  rfid.PCD_Init();

  Serial.println("Leitor RFID iniciado!");
  Serial.println("Aproxime um cartao...");
}

void loop() {
  // Aguarda um novo cartao
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Tenta ler o UID
  if (!rfid.PICC_ReadCardSerial()) {
    tone(buzzer, 3500, 250);

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    display.println("ERRO AO LER!");
    display.println("---------------------");
    display.println();
    display.println("Falha na leitura");
    display.println("do cartao.");

    display.display();

    delay(1500);
    mostrarInicio();
    return;
  }

  // Feedback sonoro
  tone(buzzer, 2500, 150);

  // Exibe o UID no Serial e no OLED
  Serial.print("UID do cartao: ");

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.println("CARTAO DETECTADO!");
  display.println("---------------------");
  display.println();
  display.println("UID:");

  display.setCursor(0, 32);

  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
      display.print("0");
    }

    Serial.print(rfid.uid.uidByte[i], HEX);
    display.print(rfid.uid.uidByte[i], HEX);

    if (i < rfid.uid.size - 1) {
      Serial.print(" ");
      display.print(" ");
    }
  }

  Serial.println();
  display.display();

  // Encerra a comunicacao com o cartao
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(2000);

  // Volta para a tela inicial
  mostrarInicio();
}