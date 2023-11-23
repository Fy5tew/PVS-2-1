// подключение библиотеки Bounce
#include "Bounce2.h";

// Создание объекта Bounce.
// В качестве параметров конструктору передаются номер пина кнопки
// и время дребезга в миллисекундах.
Bounce bouncer = Bounce(2,5);

byte led=0; //Состояние светодиода
byte oldled=1; //Последнее состояние светодиода, для исключения ложных переключений

void setup() {
  pinMode(13,OUTPUT);
  pinMode(2,INPUT);
}

void loop() {
  // Опрос изменения состояния кнопки
  if ( bouncer.update() ) {
    if ( bouncer.read() == HIGH) { //Когда нажата кнопка
     if (led==oldled) { //Проверка, что состояние кнопки изменилось
       led=!led;
     }
    } else { //Когда не нажата
       oldled=led;
    }
  }
digitalWrite(13,led); //Переключаем светодиод
}