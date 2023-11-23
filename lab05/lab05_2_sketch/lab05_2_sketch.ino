#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11


void setRed(int power) {
  analogWrite(RED_PIN, power);
}


void setGreen(int power) {
  analogWrite(GREEN_PIN, power);
}


void setBlue(int power) {
  analogWrite(BLUE_PIN, power);
}


String clear(String str) {
  str.toLowerCase();
  str.replace(" ", "");
  str.replace("(", "");
  str.replace(")", "");
  return str;
}


int getCountOf(char ch, String str) {
  int count = 0;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == ch) {
      count++;
    }
  }
  return count;
}


bool isValidPower(int power) {
  return power >= 0 && power <= 255;
}


void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);
}


bool isWorking = false;
int redPower = 0;
int greenPower = 0;
int bluePower = 0;


void loop() {
  while (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    message.toLowerCase();
    message = clear(message);
 
    if (getCountOf(',', message) > 0) {
      int r, g, b;
      sscanf(message.c_str(), "%d,%d,%d", &r, &g, &b);
      if (!isValidPower(r) || !isValidPower(g) || !isValidPower(b)) {
        Serial.println("Some numbers are invalid. It's should be between 0 and 255");
      }
      else {
        redPower = r;
        greenPower = g;
        bluePower = b;
        Serial.print("New light power: (");
        Serial.print(redPower);
        Serial.print(", ");
        Serial.print(greenPower);
        Serial.print(", ");
        Serial.print(bluePower);
        Serial.println(")");
      }
    }
    else {
      if (message == "?") {
        Serial.println("System info:");
        Serial.print("\tCurrent status: ");
        Serial.println(isWorking ? "on" : "off");
        Serial.print("\tCurrent light power: (");
        Serial.print(redPower);
        Serial.print(", ");
        Serial.print(greenPower);
        Serial.print(", ");
        Serial.print(bluePower);
        Serial.println(")");
      }
      else if (message == "on") {
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
      else {
        Serial.println("Unknown operation");
      }
    }

    if (isWorking) {
      setRed(redPower);
      setGreen(greenPower);
      setBlue(bluePower);
    }
    else {
      setRed(LOW);
      setGreen(LOW);
      setBlue(LOW);
    }
  }
}
