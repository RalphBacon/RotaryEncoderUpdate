// Used for generating interrupts using CLK signal
const unsigned int pinA = 2;

// Used for reading DT signal
const unsigned int pinB = 3;

// Updated by ISR for each pin
volatile int pinACount;
volatile int pinBCount;

// Delay to counteract switch bounce (milliseconds)
char bounce = 15;

// ------------------------------------------------------------------
// INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT
// ------------------------------------------------------------------
void isrA ()  {
  static unsigned long lastInterruptTimeA = 0;
  unsigned long interruptTimeA = millis();

  // If interrupts come faster than Xms, assume it's a bounce and ignore
  if (interruptTimeA - lastInterruptTimeA > bounce) {

    pinACount++;

    // Keep track of when we were here last
    lastInterruptTimeA = interruptTimeA;
  }
}

void isrB ()  {
  static unsigned long lastInterruptTimeB = 0;
  unsigned long interruptTimeB = millis();

  // If interrupts come faster than Xms, assume it's a bounce and ignore
  if (interruptTimeB - lastInterruptTimeB > bounce) {

    pinBCount++;

    // Keep track of when we were here last
    lastInterruptTimeB = interruptTimeB;
  }
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
  static long lastPrintTime = millis();

  // Print the total every few seconds
  if (millis() > lastPrintTime + 2000) {

    // Write out to serial monitor the value and direction
    Serial.print("A="); Serial.print(pinACount); Serial.print(" B="); Serial.println(pinBCount);

    // Keep track of print time
    lastPrintTime = millis();
  }
}

