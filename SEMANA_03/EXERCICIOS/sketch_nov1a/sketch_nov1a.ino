#include <string> 
#include <LiquidCrystal_I2C.h>

#define LED_BRANCO 9
#define LED_VERDE 8
#define LED_AZUL 16
#define LED_VERMELHO 6
#define BUZZER 5
#define LDR 7
#define SAVE_BUTTON 41
#define PLAY_BUTTON 38


int ldrValue = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(LED_BRANCO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(SAVE_BUTTON, INPUT_PULLUP);
  pinMode(PLAY_BUTTON, INPUT_PULLUP);
  Wire.begin(8, 9);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
}

int value = 0;
int divisao[4];
int x = 0;
int vetoresSalvos[100];

void converte(int numero) {

  for (int i = 0; i < 4; i++) {

    divisao[i] = numero % 2;
    numero = numero / 2;
  }
}

int portasLeds[4] = { 6, 16, 8, 9 };

void ligarLed(int aux_num) {

  converte(aux_num);


  for (int j = 0; j < 4; j++) {


    if (divisao[j] == 1) {
      digitalWrite(portasLeds[j], HIGH);
    } else if (divisao[j] == 0) {
      digitalWrite(portasLeds[j], LOW);
    }
  }
  delay(500);
}

void buzzer(int freq) {

  tone(BUZZER, freq * 100, 500);
}

void salvarToque(int leitura) {

  vetoresSalvos[x] = leitura;
  buzzer(vetoresSalvos[x]);
  ligarLed(vetoresSalvos[x]);
  x += 1;
}

void tocar() {

  for (int t = 0; t < x; t++) {

    buzzer(vetoresSalvos[t]);
    ligarLed(vetoresSalvos[t]);
    vetoresSalvos[t] = 0;
  }
  x = 0;
}

void display(int digito) {

  lcd.print(std::string header(divisao, 4);)
  delay(500);

}


void loop() {

  ldrValue = analogRead(LDR);  //Reads the Value of LDR(light).
  int aux_value = (ldrValue) / 273;
  Serial.println(analogRead(7));

  if (digitalRead(SAVE_BUTTON) == LOW) {
    salvarToque(aux_value);
    while (digitalRead(SAVE_BUTTON) == LOW)
      ;
  }

  if (digitalRead(PLAY_BUTTON) == LOW) {

    tocar();
    while (digitalRead(PLAY_BUTTON) == LOW)
      ;
  }


  delay(10);  // this speeds up the simulation
}