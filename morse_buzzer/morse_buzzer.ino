# define BUZZER_PIN  12

# define TIME_UNIT 100 // You can change WPM using this parameter

# define DIT_UNITS 1
# define DAH_UNITS 3
# define INTRA_CHARACTER_UNITS 1
# define INTER_CHARACTER_UNITS 3
# define WORD_SPACE_UNITS 7

typedef struct {
  char letter;
  String sequence;
} morse_letter;

const morse_letter morse_dictionary[26] {
  {'A', ".-"},
  {'B', "-..."},
  {'C', "-.-."},
  {'D', "-.."},
  {'E', "."},
  {'F', "..-."},
  {'G', "--."},
  {'H', "...."},
  {'I', ".."},
  {'J', ".---"},
  {'K', "-.-"},
  {'L', ".-.."},
  {'M', "--"},
  {'N', "-."},
  {'O', "---"},
  {'P', ".--."},
  {'Q', "--.-"},
  {'R', ".-."},
  {'S', "..."},
  {'T', "-"},
  {'U', "..-"},
  {'V', "...-"},
  {'W', ".--"},
  {'X', "-..-"},
  {'Y', "-.--"},
  {'Z', "--.."}
};

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  pinMode(BUZZER_PIN, OUTPUT);
}

String input;

void loop() {
  if (Serial.available() > 0) {
    input = Serial.readString();
  }
  if (input) {
    reproduceMessage(input);
  }
}

void reproduceMessage(String message) {
  Serial.println("Reproducing message: " + message);
  int length = message.length();
  for (int i = 0; i < length; i++) {
    if (message[i] == ' ') {
      delay(TIME_UNIT * WORD_SPACE_UNITS);
    }
    else {
      reproduceSequence(parseLetter(message[i]));
    }
  }
  delay(TIME_UNIT * WORD_SPACE_UNITS);
}

void reproduceSequence(String sequence) {
  Serial.println("Reproducing sequence: " + sequence);
  int length = sequence.length();
  for (int i = 0; i < length; i++) {
    if (sequence[i] == '.') {
      buzz(TIME_UNIT * DIT_UNITS);
    }
    else if (sequence[i] == '-') {
      buzz(TIME_UNIT * DAH_UNITS);
    }
    delay(TIME_UNIT * INTRA_CHARACTER_UNITS);
  }
  delay(TIME_UNIT * INTER_CHARACTER_UNITS);
}

String parseLetter(char letter) {
  Serial.println("Parsing letter: " + letter);
  int length = sizeof morse_dictionary;
  for (int i = 0; i < length; i++) {
    if(morse_dictionary[i].letter == letter) {
      Serial.println("Letter found! Correspoding sequence: " + morse_dictionary[i].sequence);
      return morse_dictionary[i].sequence;
    }
  }
  return "";
}

void buzz(int time) {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(time);
  digitalWrite(BUZZER_PIN, LOW);
}
