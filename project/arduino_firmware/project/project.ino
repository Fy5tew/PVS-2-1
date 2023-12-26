#include <Button.h>
#include <LiquidCrystal_I2C.h>


#define AUDIO_PIN 3
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12
#define YELLOW_LED_PIN 11
#define PREV_SONG_PIN A0
#define PAUSE_SONG_PIN A1
#define NEXT_SONG_PIN A2

#define PRINT_ACTION_STR "PRINT"
#define PREV_SONG_ACTION_STR "PREV_SONG"
#define NEXT_SONG_ACTION_STR "NEXT_SONG"
#define NEXT_NOTE_ACTION_STR "NEXT_NOTE"
#define GET_TITLE_ACTION_STR "GET_TITLE"
#define GET_NOTE_ACTION_STR "GET_NOTE"

#define NEW_NOTE_EVENT_STR "NEW_NOTE"
#define NEW_SONG_EVENT_STR "NEW_SONG"

#define TITLE_DATA_STR "TITLE"
#define NOTE_DATA_STR "NOTE"


const int screen_width = 16;
const int screen_height = 2;


enum EventType {
  NEW_NOTE_EVENT,
  NEW_SONG_EVENT,
  TITLE_DATA,
  NOTE_DATA,
  UNKNOWN,
};


String title = "UNKNOWN";
bool isPlaying = false;

Button prev_song_button(PREV_SONG_PIN);
Button pause_song_button(PAUSE_SONG_PIN);
Button next_song_button(NEXT_SONG_PIN);
LiquidCrystal_I2C lcd(0x27, screen_width, screen_height);


void send(String action) {
  Serial.println(action);
}


void print(String data) {
  send(String(PRINT_ACTION_STR) + ' ' + data);
}


String read_data() {
  return Serial.readStringUntil('\r\n');
}


EventType get_data_type(String data) {
  if (data.startsWith(NEW_NOTE_EVENT_STR)) {
    return EventType::NEW_NOTE_EVENT;
  }
  if (data.startsWith(NEW_SONG_EVENT_STR)) {
    return EventType::NEW_SONG_EVENT;
  }
  if (data.startsWith(TITLE_DATA_STR)) {
    return EventType::TITLE_DATA;
  }
  if (data.startsWith(NOTE_DATA_STR)) {
    return EventType::NOTE_DATA;
  }
  return EventType::UNKNOWN;
}


String parse_title(String data) {
  return data.substring(String(TITLE_DATA_STR).length() + 1, data.length() - 1);
}


void parse_note(String data, int& melody, int& duration) {
  String values = data.substring(String(NOTE_DATA_STR).length() + 1);
  int sepIndex = values.indexOf(' ');
  melody = values.substring(0, sepIndex).toInt();
  duration = values.substring(sepIndex + 1).toInt();
}


void set_led(int power) {
  digitalWrite(RED_LED_PIN, 0);
  digitalWrite(GREEN_LED_PIN, 0);
  digitalWrite(YELLOW_LED_PIN, 0);
  if (power < 0) {

  }
  else if (power <= 300) {
    digitalWrite(YELLOW_LED_PIN, 1);
  }
  else if (power <= 600) {
    digitalWrite(GREEN_LED_PIN, 1);
  }
  else if (power <= 1000) {
    digitalWrite(RED_LED_PIN, 1);
  }
  else {
    digitalWrite(RED_LED_PIN, 1);
    digitalWrite(GREEN_LED_PIN, 1);
    digitalWrite(YELLOW_LED_PIN, 1);
  }
}


void play_note(int melody, int duration) {
  tone(AUDIO_PIN, melody, duration);
  delay(duration);
  noTone(AUDIO_PIN);
}


void update_lcd(String info = "") {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(title);
  lcd.setCursor(0, 1);
  if (info.length()) {
    lcd.print(info);
    lcd.print(" | ");
  }
  lcd.print(isPlaying ? "PLAY" : "PAUSE");
}


void setup() {
  pinMode(AUDIO_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(PREV_SONG_PIN, INPUT_PULLUP);
  pinMode(PAUSE_SONG_PIN, INPUT_PULLUP);
  pinMode(NEXT_SONG_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  lcd.init();                     
  lcd.backlight();

  update_lcd();
}


void loop() {
  if (prev_song_button.released()) {
    send(PREV_SONG_ACTION_STR);
    set_led(10000);
    update_lcd("<<PREV");
  }

  if (pause_song_button.released()) {
    isPlaying = !isPlaying;
    set_led(isPlaying ? 10000 : -1);
    update_lcd();
  }

  if (next_song_button.released()) {
      send(NEXT_SONG_ACTION_STR);
      set_led(10000);
      update_lcd("NEXT>>");
  }

  delay(100);

  set_led(-1);

  if (Serial.available()) {
    String data = read_data();
    switch (get_data_type(data)) {
      case EventType::NEW_NOTE_EVENT: {
        send(GET_NOTE_ACTION_STR);
        break;
      }
      case EventType::NEW_SONG_EVENT: {
        send(GET_TITLE_ACTION_STR);
        break;
      }
      case EventType::TITLE_DATA: {
        title = parse_title(data);
        update_lcd();
        break;
      }
      case EventType::NOTE_DATA: {
        int melody, duration;
        parse_note(data, melody, duration);
        set_led(melody);
        play_note(melody, duration);
        break;
      }
      default: {
        print("UNKNOWN: " + data);
        break;
      }
    }
  }

  if (title == "UNKNOWN" && !Serial.available()) {
    send(GET_TITLE_ACTION_STR);
    delay(400);
  }

  if (!Serial.available() && isPlaying) {
    send(NEXT_NOTE_ACTION_STR);
  }
}
