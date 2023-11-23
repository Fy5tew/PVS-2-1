// управлять сервоприводами (англ. servo motor) самостоятельно
// не так то просто, но в стандартной библиотеке уже всё
// заготовлено, что делает задачу тривиальной
#include <Servo.h>
#define MAX_VALUE 830
#define MIN_VALUE 760
// объявляем объект типа Servo с именем myServo. Ранее мы
// использовали int, boolean, float, а теперь точно также
// используем тип Servo, предоставляемый библиотекой. В случае
// Serial мы использовали объект сразу же: он уже был создан
// для нас, но в случае с Servo, мы должны сделать это явно.
// Ведь в нашем проекте могут быть одновременно несколько
// приводов, и нам понадобится различать их по именам
Servo myServo;
void setup()
{
 // прикрепляем (англ. attach) нашу серву к 9-му пину. Явный
 // вызов pinMode не нужен: функция attach сделает всё за нас
 myServo.attach(9);
 Serial.begin(9600);
}
void loop()
{
 int val = analogRead(A0);
 // на основе сигнала понимаем реальный угол поворота движка.
 // Используем вещественные числа в расчётах, но полученный
 // результат округляем обратно до целого числа
  int valPercent = int(float((val - MIN_VALUE)) / float((MAX_VALUE - MIN_VALUE)) * 100);
 int angle = int(valPercent * 180 / 100);
 if (valPercent < 0) {
  angle = 0;
 }
 if (valPercent > 100) {
  angle = 180;
 }
 Serial.print(val);
 Serial.print(" ");
 Serial.print(valPercent);
 Serial.print(" ");
 Serial.println(angle);
 // обычная серва не сможет повторить угол потенциометра на
 // всём диапазоне углов. Она умеет вставать в углы от 0° до
 // 180°. Ограничиваем угол соответствующе
 angle = constrain(angle, 0, 180);
 // и, наконец, подаём серве команду встать в указанный угол
 myServo.write(angle);
 delay(100);
}
