#include <LiquidCrystal.h> // Подключим библиотеку для работы с дисплеем

#define DELAY_SEC 990 // Пауза для отсчета секунд (подбирается эксперементально)


// Подключение лисплея к пинам ардуино в моем случае УНО
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, DB4, DB5, DB6, DB7)

int h = 20; // Часы
int m = 5; // Минуты
int s = 30;  // Секунды

void setup() {
  lcd.begin(16, 2); // Задаем размерность экрана формат : кол-во символов в строке на кол-во строк
}

void loop() {
  s++; // Считаем секунды
  delay(DELAY_SEC);
  if (s == 60) // При 60секундах 
  {            
    s = 0; // Обнуляем секунды
    m++; // Добавляем минуту
    if(m == 60) // При 60 минутах
    {
      m = 0; // Обнуляем минуты
      h++; // Добавляем час
      if (h == 24) // При 24 часах
      {
        h = 0; // Обнуляем часы
      }
    }
  }

  // Вывод на дисплей
  // Вывод времени
  lcd.clear();
  lcd.setCursor(0, 0);  // Устанавливаем курсор в начало 1й строки  
  lcd.print("Time: ");   // Выводим надпись "Time:"
  lcd.print(h);         // Выводим часы  
  lcd.print(":");       // Вывод двоеточие
  lcd.print(m);         // Выводим минуты
  lcd.print(":");       // Вывод двоеточие
  lcd.print(s);         // Выводим секунды
}