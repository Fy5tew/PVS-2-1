// Подключаем библиотеку для работы с жидкокристаллическим
// экраном (англ. Liquid Crystal Display или просто LCD)
#include "LiquidCrystalRus.h"
#define COLS 16
#define ROWS 2
#define DELAY_TIME 100
// Объявляем объект, для управления дисплеем. Для его создания
// необходимо указать номера пинов, к которым он подключен в
// порядке: RS E DB5 DB6 DB7 DB8
LiquidCrystalRus lcd(13, 12, 11, 10, 9, 8);
void setup()
{
 // начинаем работу с экраном. Сообщаем объекту количество
 // строк и столбцов. Опять же, вызывать pinMode не требуется:
 // функция begin сделает всё за нас
 lcd.begin(COLS, ROWS);
}

const String message = "Турчинович Никита Александрович, Авдей Алексей Юрьевич";
void loop()
{
  lcd.setCursor(16, 0);
  lcd.autoscroll();
  
  for (int i = 0; i < message.length(); i++) {
    lcd.print(message[i]);
    delay(DELAY_TIME);
  }

  lcd.noAutoscroll();
  lcd.clear();
}
