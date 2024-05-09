#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

const byte ROWS = 4;  //qtde linhas
const byte COLS = 4;  //qtde colunas

//definição das teclas
char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

//definição das portas para o teclado
byte rowPins[ROWS] = { 3, 4, 5, 6 };   //pinos das linhas (azul, roxo, cinza, branco)
byte colPins[COLS] = { 7, 8, 9, 10 };  //pinos das colunas (marrom, laranja, amarelo, verde)

//criação dos objetos
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);  //endereço, colunas, linhas

String entrada;
byte modoEdicao = 0;  //0=edicao, 1=apresentacao

void setup() {
  lcd.init();
  lcd.init();

  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.blink();  //habilita o cursor piscante

  entrada = "";
  Serial.begin(9600);
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    if (customKey == 'D') {
      if (modoEdicao == 0) {
        //apaga o ultimo caracter
        lcd.setCursor(entrada.length() - 1, 0);
        lcd.print(" ");
        //volta o cursor
        lcd.setCursor(entrada.length() - 1, 0);
        //remove o ultimo caracter
        entrada.remove(entrada.length() - 1, 1);
      }

    } else if (customKey == '#') {
      if (modoEdicao == 0) {  //muda para apresentacao
        modoEdicao = 1;
        lcd.noBlink();
      } else {  //muda para edicao
        modoEdicao = 0;
        lcd.setCursor(entrada.length(), 0);
        lcd.blink();
      }

    } else if (customKey == '*') {
      int resultado = entrada.toInt();
      Serial.println(resultado + 1000);

    } else {
      if (modoEdicao == 0) {
        lcd.print(customKey);
        entrada = entrada + customKey;
      }
    }
  }
}
