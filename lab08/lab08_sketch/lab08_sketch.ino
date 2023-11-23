#define RED_LED 12
#define YELLOW_LED 11
#define GREEN_LED 10

#define COUNTER_LIMIT 100
#define COUNTER_DELAY 10

#define MODE_OFF 'O'
#define MODE_NORMAL 'N'
#define MODE_SLEEP 'S'
#define MODE_RED 'R'
#define MODE_GREEN 'G'


char mode = MODE_OFF;
int currentState = 1;
int counter = 0;


void setLights(int redPower, int yellowPower, int greenPower) {
  digitalWrite(RED_LED, redPower);
  digitalWrite(YELLOW_LED, yellowPower);
  digitalWrite(GREEN_LED, greenPower);
}


void offLights() {
  setLights(LOW, LOW, LOW);
}


void setMode(int newMode) {
  if (mode == newMode) {
    return;
  }
  mode = newMode;
  currentState = 1;
}


void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Serial.begin(9600);
}


void loop() {
  counter++;

  if (Serial.available()) {
    char inputChar = Serial.read();
    switch (toupper(inputChar)) {
      case MODE_OFF:
        setMode(MODE_OFF);
        Serial.println("Selected mode: OFF");
        break;
      case MODE_NORMAL:
        setMode(MODE_NORMAL);
        Serial.println("Selected mode: NORMAL");
        break;
      case MODE_SLEEP:
        setMode(MODE_SLEEP);
        Serial.println("Selected mode: SLEEP");
        break;
      case MODE_RED:
        setMode(MODE_RED);
        Serial.println("Selected mode: RED");
        break;
      case MODE_GREEN:
        setMode(MODE_GREEN);
        Serial.println("Selected mode: GREEN");
        break;
      case ' ':
      case '\n':
      case '\t':
      case '\r':
        break;
      default:
        Serial.print("Unknown option: ");
        Serial.println(inputChar);
        break;
    }
  }

  if (counter == COUNTER_LIMIT) {
    counter = 0;
    switch (toupper(mode)) {
      case MODE_OFF:
        offLights();
        break;
      case MODE_NORMAL:
        normalModeStatemachine(currentState);
        break;
      case MODE_SLEEP:
        sleepModeStatemachine(currentState);
        break;
      case MODE_RED:
        redModeStatemachine(currentState);
        break;
      case MODE_GREEN:
        greenModeStatemachine(currentState);
        break;
    }
  }

  delay(COUNTER_DELAY);
}


void normalModeStatemachine(int& state) {
  switch (state) {
    case 1:
      setLights(HIGH, LOW, LOW);
      state = 2;
      break;
    case 2:
      setLights(HIGH, HIGH, LOW);
      state = 3;
      break;
    case 3:
      setLights(LOW, LOW, HIGH);
      state = 4;
      break;
    case 4:
      setLights(LOW, HIGH, LOW);
      state = 1;
      break;
    default:
      state = 1;
      break;
  }
}


void sleepModeStatemachine(int& state) {
  switch (state) {
    case 1:
      setLights(LOW, HIGH, LOW);
      state = 2;
      break;
    case 2:
      offLights();
      state = 1;
      break;
    default:
      state = 1;
      break;
  }
}


void redModeStatemachine(int& state) {
  setLights(HIGH, LOW, LOW);
}


void greenModeStatemachine(int& state) {
  setLights(LOW, LOW, HIGH);
}
