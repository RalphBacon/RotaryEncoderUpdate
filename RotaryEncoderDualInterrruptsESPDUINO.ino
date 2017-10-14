#include <pins_arduino.h>

// Used for generating interrupts using CLK signal
const int PinA = D4;

// Used for reading DT signal
const int PinB = D5;

// Keep track of last rotary value
int lastCount = 50;

// Updated by the ISR (Interrupt Service Routine)
volatile int virtualPosition = 50;

// ------------------------------------------------------------------
// INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT     INTERRUPT
// ------------------------------------------------------------------
void isrA ()  {
  Serial.println("A");
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  // If interrupts come faster than 5ms, assume it's a bounce and ignore
  if (interruptTime - lastInterruptTime > 20) {

    byte pinB = digitalRead(PinB);
    if (pinB == 1)
    {
      virtualPosition++ ; // Could be -5 or -10
    }
    else {
      virtualPosition-- ; // Could be +5 or +10
    }

    // Restrict value from 0 to +100
    //virtualPosition = min(100, max(0, virtualPosition));
  }

  // Keep track of when we were here last (no more than every 5ms)
  lastInterruptTime = interruptTime;
}

void isrB ()  {
  Serial.println("B");
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  // If interrupts come faster than 5ms, assume it's a bounce and ignore
  if (interruptTime - lastInterruptTime > 20) {

    byte pinA = digitalRead(PinA);
    if (pinA == 0)
    {
      virtualPosition++ ; // Could be -5 or -10
    }
    else{
      virtualPosition-- ; // Could be +5 or +10
    }

    // Restrict value from 0 to +100
    // virtualPosition = min(100, max(0, virtualPosition));
  }
  // Keep track of when we were here last (no more than every 5ms)
  lastInterruptTime = interruptTime;
}

// ------------------------------------------------------------------
// SETUP    SETUP    SETUP    SETUP    SETUP    SETUP    SETUP
// ------------------------------------------------------------------
void setup() {
  // Just whilst we debug, view output on serial monitor
  Serial.begin(9600);

  // Rotary pulses are INPUTs
  pinMode(PinA, INPUT_PULLUP);
  pinMode(PinB, INPUT_PULLUP);

  // Attach the routine to service the interrupts
  attachInterrupt(PinA, isrA, LOW);
  attachInterrupt(PinB, isrB, LOW);

  // Ready to go!
  Serial.println("Monitoring for interrupts");
}

// ------------------------------------------------------------------
// MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP     MAIN LOOP
// ------------------------------------------------------------------
void loop() {

  // If the current rotary switch position has changed then update everything
  if (virtualPosition != lastCount) {

    // Write out to serial monitor the value and direction
    Serial.print(virtualPosition > lastCount ? "Up:" : "Down:");
    Serial.println(virtualPosition);

    // Keep track of this new value
    lastCount = virtualPosition ;
  }
}

// ------------------------------------------------------------------
// Print port value as bit values
// ------------------------------------------------------------------
String printByteAsBin(byte value, const char * channel) {

  String output = "";
  for (int cnt = 0; cnt < 8; cnt++) {
    if (bitRead(value, cnt) == 1) {
      output = "1" + output;
    }
    else {
      output = "0" + output;
    }
  }

  return channel + output;
} 
