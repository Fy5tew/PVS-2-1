#define DATA_PIN 13
#define STORAGE_PIN 12
#define CLOCK_PIN 11


int segments[] = {
  1 << 1,  
  1 << 2, 
  1 << 5, 
  1 << 6, 
  1 << 7,
  1 << 4,
  1 << 3,
};

int digits[] = {
  segments[0] | segments[1] | segments[2] | segments[3] | segments[4] | segments[5],  // 0 
  segments[1] | segments[2], // 1
  segments[0] | segments[1] | segments[6] | segments[4] | segments[3], // 2
  segments[0] | segments[1] | segments[2] | segments[3] | segments[6], // 3
  segments[1] | segments[2] | segments[5] | segments[6], // 4 
  segments[0] | segments[2] | segments[3] | segments[5] | segments[6], // 5
  segments[0] | segments[2] | segments[3] | segments[4] | segments[5] | segments[6], // 6
  segments[0] | segments[1] | segments[2], // 7
  segments[0] | segments[1] | segments[2] | segments[3] | segments[4] | segments[5] | segments[6], // 8
  segments[0] | segments[1] | segments[2] | segments[3] | segments[5] | segments[6], // 9
};

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(STORAGE_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void loop() {
  for (int i = 99; i >= 0; i--) {
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, digits[i % 10]);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, digits[i / 10]);
    digitalWrite(STORAGE_PIN, LOW);
    digitalWrite(STORAGE_PIN, HIGH);
    delay(1000);
  }
}