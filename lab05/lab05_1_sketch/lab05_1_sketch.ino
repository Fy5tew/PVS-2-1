#define LED_PIN 9


void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}


bool isWorking = false;
int power = 1;
bool isAllNum = true;
String message = "";

void loop() {
  while (Serial.available()) {
    char incomingChar = Serial.read();

    if (incomingChar == '\n') {
      message.toLowerCase();
      if (isAllNum) {
        int value = message.toInt();
        if (value <= 0 || value > 255) {
          Serial.println("Invalid number. It should be between 1 and 255");
        }
        else {
          power = value;
          Serial.print("New light power: ");
          Serial.println(power);
        }
      }
      else {
        if (message == "on") {
            if (isWorking) {
              Serial.println("System is already on");
            }
            else {
              isWorking = true;
              Serial.println("System is on");
            }
        }
        else if (message == "off") {
            if (!isWorking) {
              Serial.println("System is already off");
            }
            else {
              isWorking = false;
              Serial.println("System is off");
            }
        }
        else if (message == "?") {
          Serial.println("System info:");
          Serial.print("\tCurrent status: ");
          Serial.println(isWorking ? "on" : "off");
          Serial.print("\tCurrent light power: ");
          Serial.println(power);
        }
        else {
          Serial.println("Unknown operation");
        }
      }
      if (isWorking) {
        analogWrite(LED_PIN, power);
      }
      else {
        analogWrite(LED_PIN, LOW);
      }

      isAllNum = true;
      message = "";
      break;
    }

    if (incomingChar < '0' || incomingChar > '9') {
      isAllNum = false;
    }
    message += incomingChar;
  }
}
