// Огромное количество готового кода уже написано другими людьми
// и хранится в виде отдельных файлов, которые называются
// библиотеками. Для использования кода из библиотеки, её нужно
// подключить (англ. include). Библиотека «math» даёт разные
// математические функции, в том числе функцию логарифма
// (англ. log), которая нам понадобится далее
#include <math.h>
#define FIRST_LED_PIN 2
#define LED_COUNT 10
// Параметр конкретного типа термистора (из datasheet):
#define TERMIST_B 4300
#define VIN 5.0
void setup()
{
  for (int i = 0; i < LED_COUNT; ++i) {
    pinMode(i + FIRST_LED_PIN, OUTPUT);
    digitalWrite(i + FIRST_LED_PIN, HIGH);
  }
  Serial.begin(9600);
}
void loop()
{
  // вычисляем температуру в °С с помощью магической формулы.
  // Используем при этом не целые числа, а вещественные. Их ещё
  // называют числами с плавающей (англ. float) точкой. В
  // выражениях с вещественными числами обязательно нужно явно
  // указывать дробную часть у всех констант. Иначе дробная
  // часть результата будет отброшена
  float voltage = analogRead(A0) * VIN / 1023.0;
  float r1 = voltage / (VIN - voltage);
  float temperature = 1./( 1./(TERMIST_B)*log(r1)+1./(25. + 273.) ) - 273;
  Serial.println(temperature);
  for (int i = 0; i < LED_COUNT; ++i) {
    // при 21°С должен гореть один сегмент, при 22°С — два и
    // т.д. Определяем должен ли гореть i-й нехитрым способом
    boolean enableSegment = (temperature >= 25+i);
    digitalWrite(i + FIRST_LED_PIN, enableSegment);
  }
}
