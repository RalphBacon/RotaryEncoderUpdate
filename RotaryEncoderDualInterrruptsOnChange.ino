// Used for generating interrupts using CLK signal
const int pinA = 2;

// Used for reading DT signal
const int pinB = 3;

// Keep track of last rotary value
int lastCount = 50;

// Updated by the ISR (Interrupt Service Routine)
volatile int virtualPosition = 50;

// Updated by ISR for each pin
volatile bool pinAStateHigh;
volatile bool pinBStateHigh;

// Old values of pin state so we can compare
bool oldPinAStateHigh;
bool oldPinBStateHigh;

// Delay to counteract switch bounce (milliseconds)
char bounce = 10;

// ------------------------------------------------------------------
// INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT
// ------------------------------------------------------------------
void isrA ()  {
  static unsigned long lastInterruptTimeA = 0;
  unsigned long interruptTimeA = millis();

  // If interrupts come faster than Xms, assume it's a bounce and ignore
  if (interruptTimeA - lastInterruptTimeA > bounce) {

    // We are here because pinA has CHANGED
    pinAStateHigh = !pinAStateHigh;
    //pinAStateHigh = digitalRead(pinA) == HIGH;

    // Don't do this for real!
    //Serial.print("\nPin A state="); Serial.print(pinAStateHigh ? "HIGH" : "LOW");
    //Serial.print(" (Pin B state="); Serial.print(pinBStateHigh ? "HIGH)" : "LOW)");
  }

  // Keep track of when we were here last
  lastInterruptTimeA = interruptTimeA;
}

void isrB ()  {
  static unsigned long lastInterruptTimeB = 0;
  unsigned long interruptTimeB = millis();

  // If interrupts come faster than Xms, assume it's a bounce and ignore
  if (interruptTimeB - lastInterruptTimeB > bounce) {

    // We are here because pinB has CHANGED
    pinBStateHigh = !pinBStateHigh;
    //pinBStateHigh = digitalRead(pinB) == HIGH;

    // Don't do this for real!
    //Serial.print("\nPin B state="); Serial.print(pinBStateHigh ? "HIGH" : "LOW");
    //Serial.print(" (Pin A state="); Serial.print(pinAStateHigh ? "HIGH)" : "LOW)");
  }

  // Keep track of when we were here last
  lastInterruptTimeB = interruptTimeB;
}

// ------------------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
// ------------------------------------------------------------------
void setup() {
  // Just whilst we debug, view output on serial monitor
  Serial.begin(115200);

  // Rotary pulses are INPUTs
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);

  // Set initial state of PinA & PinB by reading the pins
  pinAStateHigh = digitalRead(pinA) == HIGH;
  pinBStateHigh = digitalRead(pinB) == HIGH;
  Serial.print("Initial state Pin A = "); Serial.println(pinAStateHigh ? "HIGH" : "LOW");
  Serial.print("Initial state Pin B = "); Serial.println(pinBStateHigh ? "HIGH" : "LOW");

  // So we remember what the state was (can detect the change)
  oldPinAStateHigh = pinAStateHigh;
  oldPinBStateHigh = pinBStateHigh;

  // Attach the routine to service the interrupts
  attachInterrupt(digitalPinToInterrupt(pinA), isrA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), isrB, CHANGE);

  // Ready to go!
  Serial.println("Start");
}

// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
void loop() {

  // Pin A changed? What direction?
  if (pinAStateHigh != oldPinAStateHigh) {

    // Pin A is HIGH
    if (pinAStateHigh) {
      // Pin B is LOW
      if (!pinBStateHigh) {
        // Clockwise
        virtualPosition++;
      }
      else {
        // Anticlockwise
        virtualPosition--;
      }
    } else {
      // Pin A just went low and B is HIGH
      if (pinBStateHigh) {
        // Clockwise
        virtualPosition++;
      }
      else {
        // Anticlockwise
        virtualPosition--;
      }
    }

    // Keep track of state of Pin A
    oldPinAStateHigh = pinAStateHigh;
  }

  // Pin B changed? What direction?
  if (pinBStateHigh != oldPinBStateHigh) {
    if (pinBStateHigh) {
      if (pinAStateHigh) {
        virtualPosition++;
      }
      else {
        virtualPosition--;
      }
    } else {
      // Pin B just went low
      if (!pinAStateHigh) {
        virtualPosition++;
      }
      else {
        virtualPosition--;
      }
    }
    oldPinBStateHigh = pinBStateHigh;
  }

  // If the current rotary switch position has changed then update everything
  if (virtualPosition != lastCount) {

    // Write out to serial monitor the value and direction
    Serial.print(virtualPosition > lastCount ? " Up:" : " Down:");
    Serial.println(virtualPosition);

    // Keep track of this new value
    lastCount = virtualPosition ;
  }
}

