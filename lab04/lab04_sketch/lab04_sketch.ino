// даём разумные имена для пинов со светодиодом
// и потенциометром (англ potentiometer или просто «pot»)
#define LED_PIN1 9
#define LED_PIN2 5
#define POT_PIN A0


void setup()
{
 // пин со светодиодом — выход, как и раньше...
 pinMode(LED_PIN1, OUTPUT);
 pinMode(LED_PIN2, OUTPUT);
 // ...а вот пин с потенциометром должен быть входом
 // (англ. «input»): мы хотим считывать напряжение,
 // выдаваемое им
 pinMode(POT_PIN, INPUT);
}


void loop()
{
 // заявляем, что далее мы будем использовать 2 переменные с
 // именами rotation и brightness, и что хранить в них будем
 // целые числа (англ. «integer», сокращённо просто «int»)
 int rotation, brightness1, brightness2;
 // считываем в rotation напряжение с потенциометра:
 // микроконтроллер выдаст число от 0 до 1023
 // пропорциональное углу поворота ручки
 rotation = analogRead(POT_PIN);
 // в brightness записываем полученное ранее значение rotation
 // делённое на 4. Поскольку в переменных мы пожелали хранить
 // целые значения, дробная часть от деления будет отброшена.
 // В итоге мы получим целое число от 0 до 255
 brightness1 = rotation / 4;
 brightness2 = brightness1 / 8;
 // выдаём результат на светодиод
 analogWrite(LED_PIN1, brightness1);
 analogWrite(LED_PIN2, brightness2);
}
