#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

const byte ROWS = 4; //qtde linhas
const byte COLS = 4; //qtde colunas

//definição das teclas
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//definição das portas para o teclado
byte rowPins[ROWS] = {3, 4, 5, 6};  //pinos das linhas (azul, roxo, cinza, branco)
byte colPins[COLS] = {7, 8, 9, 10}; //pinos das colunas (marrom, laranja, amarelo, verde)

//criação dos objetos
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal_I2C lcd(0x27,16,2);   //endereço, colunas, linhas   

void setup(){
  lcd.init();
  lcd.init();

  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.blink();  //habilita o cursor piscante

  //Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    //Serial.println(customKey);
    lcd.print(customKey);
  }
}
