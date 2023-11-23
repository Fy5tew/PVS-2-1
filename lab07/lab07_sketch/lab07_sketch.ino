#define RED_LED 12
#define YELLOW_LED 11
#define GREEN_LED 10 


int counter = 0;
int state = 1;


void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}


void loop() {
  counter++;

  if (counter == 100) {
    counter = 0;
    statemachine();
  }

  delay(10);
}


void statemachine() {
  switch (state) {
    case 1:
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      state++;
      break;
    case 2:
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      state++;
      break;
    case 3:
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      state++;
      break;
    case 4:
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      state = 1;
      break;
  }
}
