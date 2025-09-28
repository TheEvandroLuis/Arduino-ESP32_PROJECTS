#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Endereço I2C do display: 0x27, 16 colunas e 2 linhas
const int buttonPin = 2;  // Pino do botão
int contador = 0;  // Inicializa o contador

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("MCA2024 Robotica");
  lcd.setCursor(0, 1);
  lcd.print("Visitantes:");
  
  pinMode(buttonPin, INPUT_PULLUP);  // Define o pino do botão como entrada com pull-up interno
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {  // Verifica se o botão foi pressionado
    delay(50);  // Debounce do botão
    contador++;  // Incrementa o contador
    atualizarDisplay(contador);  // Atualiza o display com o novo valor do contador
    while (digitalRead(buttonPin) == LOW) {
      // Aguarda até que o botão seja solto
    }
    delay(500);
  }
}

void atualizarDisplay(int value) {
  lcd.setCursor(0, 1);
  lcd.print("                    ");  // Limpa a linha do contador
  lcd.setCursor(0, 1);
  lcd.print("Visitantes: ");
  lcd.setCursor(12, 1);
  lcd.print(value);
}