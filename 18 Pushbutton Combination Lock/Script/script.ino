const uint8_t buttonPins[] = {2, 3, 4};
const uint8_t PASSCODE[] = {0, 1, 2};

constexpr size_t BUTTON_COUNT = sizeof(buttonPins) / sizeof(buttonPins[0]);
constexpr size_t PASSCODE_LENGTH = sizeof(PASSCODE) / sizeof(PASSCODE[0]);
constexpr bool ENABLE_DEBUG = false;

const uint8_t redLedPin = 5;
const uint8_t greenLedPin = 6;
const uint8_t buzzerPin = 9;

const unsigned long DEBOUNCE_MS = 20;
const unsigned long INACTIVITY_RESET_MS = 5000;
const unsigned long GREEN_ON_MS = 2000;
const unsigned long RED_ON_MS = 2000;

const uint16_t SHORT_BEEP_FREQ = 1000;
const unsigned long SHORT_BEEP_MS = 120;

const uint16_t UNLOCK_FREQ = 1500;
const unsigned long UNLOCK_TONE_MS = 200;
const unsigned long UNLOCK_PAUSE_MS = 100;

const uint16_t ERROR_FREQ = 400;
const unsigned long ERROR_TONE_MS = 800;

uint8_t idx = 0;
unsigned long lastPressMillis = 0;

int prevRaw[BUTTON_COUNT];
int stableState[BUTTON_COUNT];
unsigned long lastChangeMillis[BUTTON_COUNT];
bool consumed[BUTTON_COUNT];

unsigned long greenUntil = 0;
unsigned long redUntil = 0;

void handlePress(uint8_t press, unsigned long now);
void playShortBeep();
void playUnlockPattern();
void playErrorTone();
void playToneBlocking(uint16_t freq, unsigned long durationMs);
void logButtonState(const char *label, uint8_t buttonIndex, int raw, int stable);
void logMessage(const char *message);

void setup() {
  for (size_t i = 0; i < BUTTON_COUNT; i++) {
    pinMode(buttonPins[i], INPUT);
    prevRaw[i] = LOW;
    stableState[i] = LOW;
    consumed[i] = false;
  }

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(buzzerPin, LOW);

  if (ENABLE_DEBUG) {
    Serial.begin(115200);
    delay(5);
    logMessage("Lock ready");
  }

  unsigned long start = millis();
  lastPressMillis = start;
  for (size_t i = 0; i < BUTTON_COUNT; i++) {
    lastChangeMillis[i] = start;
  }
}

void loop() {
  unsigned long now = millis();

  for (size_t i = 0; i < BUTTON_COUNT; i++) {
    int raw = digitalRead(buttonPins[i]);

    if (raw != prevRaw[i]) {
      prevRaw[i] = raw;
      lastChangeMillis[i] = now;
      if (ENABLE_DEBUG) {
        logButtonState("raw change", static_cast<uint8_t>(i), raw, stableState[i]);
      }
    }

    if ((now - lastChangeMillis[i]) >= DEBOUNCE_MS && raw != stableState[i]) {
      stableState[i] = raw;
      if (ENABLE_DEBUG) {
        logButtonState("stable", static_cast<uint8_t>(i), raw, stableState[i]);
      }

      if (stableState[i] == HIGH) {
        if (!consumed[i]) {
          consumed[i] = true;
          handlePress(static_cast<uint8_t>(i), now);
        }
      } else {
        consumed[i] = false;
      }
    }
  }

  if (greenUntil != 0 && (long)(now - greenUntil) >= 0) {
    digitalWrite(greenLedPin, LOW);
    greenUntil = 0;
    if (ENABLE_DEBUG) {
      logMessage("green off");
    }
  }

  if (redUntil != 0 && (long)(now - redUntil) >= 0) {
    digitalWrite(redLedPin, LOW);
    redUntil = 0;
    if (ENABLE_DEBUG) {
      logMessage("red off");
    }
  }

  if (idx > 0 && (now - lastPressMillis) >= INACTIVITY_RESET_MS) {
    idx = 0;
    if (ENABLE_DEBUG) {
      logMessage("passcode reset due to inactivity");
    }
  }
}

void handlePress(uint8_t press, unsigned long now) {
  lastPressMillis = now;

  if (ENABLE_DEBUG) {
    char buffer[48];
    snprintf(buffer, sizeof(buffer), "press %u vs expected %u", press, (idx < PASSCODE_LENGTH) ? PASSCODE[idx] : 255);
    logMessage(buffer);
  }

  if (idx < PASSCODE_LENGTH && press == PASSCODE[idx]) {
    playShortBeep();
    idx++;

    if (idx == PASSCODE_LENGTH) {
      digitalWrite(greenLedPin, HIGH);
      greenUntil = now + GREEN_ON_MS;

      digitalWrite(redLedPin, LOW);
      redUntil = 0;

      playUnlockPattern();
      idx = 0;

      if (ENABLE_DEBUG) {
        logMessage("unlock success");
      }
    }
  } else {
    idx = 0;

    digitalWrite(greenLedPin, LOW);
    greenUntil = 0;

    digitalWrite(redLedPin, HIGH);
    redUntil = now + RED_ON_MS;

    playErrorTone();

    if (ENABLE_DEBUG) {
      logMessage("wrong button");
    }
  }
}

// Plays a tone for the requested duration and ensures the buzzer is silent afterwards.
void playToneBlocking(uint16_t freq, unsigned long durationMs) {
  tone(buzzerPin, freq);
  delay(durationMs);
  noTone(buzzerPin);
}

void playShortBeep() {
  playToneBlocking(SHORT_BEEP_FREQ, SHORT_BEEP_MS);
}

void playUnlockPattern() {
  playToneBlocking(UNLOCK_FREQ, UNLOCK_TONE_MS);
  delay(UNLOCK_PAUSE_MS);
  playToneBlocking(UNLOCK_FREQ, UNLOCK_TONE_MS);
}

void playErrorTone() {
  playToneBlocking(ERROR_FREQ, ERROR_TONE_MS);
}

void logButtonState(const char *label, uint8_t buttonIndex, int raw, int stable) {
  if (!ENABLE_DEBUG) {
    return;
  }
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "%s b%u raw=%d stable=%d", label, buttonIndex, raw, stable);
  Serial.println(buffer);
}

void logMessage(const char *message) {
  if (!ENABLE_DEBUG) {
    return;
  }
  Serial.println(message);
}
