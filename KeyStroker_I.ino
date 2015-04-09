
#include "UsbKeyboard.h"

#define PIN_BUTTON 7             // the button attached to pin 7
long counter = 0;                // Used to delay the call to send the output string
int runStatus = LOW;             // variable to determine whether or not to send the text string
long numCycles = 2000000;        // this is the check value as a replacement for the delay() function
int led = 13;                    // LED light on the board to show that the unit is currently sending value


void setup() {
  
  // set the button pin to receive mode
  pinMode(PIN_BUTTON, INPUT);
  
  // set the led pin to send mode
  pinMode(led, OUTPUT);
  
  // USB setup
  // Disable the timer0 since it can mess with the USB timing.  Note that
  // this means some functions, such as delay() will no longer work.
  TIMSK0 &= !(1<TOIE0);
  
  // clear interrupts while performing time-critical operations
  cli();
  
  // Force re-enumeration so the host will detect the usb device
  usbDeviceDisconnect();
  delayMs(250);
  usbDeviceConnect();
  
  // Set interrupts
  sei();
}


void loop() {
  
  // update USB device state
  UsbKeyboard.update();
  
  // check if a button-press has occurred
  if( (digitalRead(PIN_BUTTON) == HIGH)  && (runStatus == LOW) ) {
    runStatus = HIGH;
    delayMs(15);  
  } else if ( (digitalRead(PIN_BUTTON) == HIGH) && (runStatus == HIGH) ) {
      runStatus = LOW;
      delayMs(15);
      counter = 0;
      digitalWrite(led, LOW);
  }
  
  // Check if the project was set to run
  if ( runStatus == HIGH ) {
    counter++;
    digitalWrite(led, HIGH);
     
    // Check if the appropriate number of cycles have occurred to ensure the right "delay()" has been met    
    if (counter > numCycles) {
      sendMessage();
      counter = 0;
   }
  }
    
}

void delayMs(unsigned int ms) {
  for ( int i = 0; i<ms; i++) {
    delayMicroseconds(1000);
  }
}


// The message sent out
void sendMessage() {
    
    UsbKeyboard.sendKeyStroke(KEY_B, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_M, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_W, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_SPACE);
    UsbKeyboard.sendKeyStroke(KEY_R, MOD_SHIFT_LEFT);
    UsbKeyboard.sendKeyStroke(KEY_U);
    UsbKeyboard.sendKeyStroke(KEY_L);
    UsbKeyboard.sendKeyStroke(KEY_Z);
    UsbKeyboard.sendKeyStroke(KEY_ENTER);
}


