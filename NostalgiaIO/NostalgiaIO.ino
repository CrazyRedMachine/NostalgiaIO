#include "PANB.h"

bool passthrough = false;
#define PIN_PASSTHROUGH 7
#define PIN_LED 13

static FILE uartout = {0} ;

static int uart_putchar (char c, FILE *stream)
{
  Serial.write(c) ;
  return 0 ;
}

void setup() {
   
  Serial1.begin(115200);
  Serial.begin(115200);

  pinMode(PIN_PASSTHROUGH, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
  delay(500);
  if (digitalRead(PIN_PASSTHROUGH) == LOW){
    
    //Serial.begin(115200); // use 57600 bps for ACIO compatibility
    
    digitalWrite(PIN_LED, HIGH);
    delay(500);
    digitalWrite(PIN_LED, LOW);
    delay(500);
    digitalWrite(PIN_LED, HIGH);
    delay(500);
    digitalWrite(PIN_LED, LOW);
    delay(500);
    digitalWrite(PIN_LED, HIGH);
    delay(500);
    digitalWrite(PIN_LED, LOW);
    delay(500);
    
    passthrough = true;
    return;
  }
  delay(1000);
  if (!passthrough)
  {
    
    //Serial.begin(115200);
    fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &uartout ;
    delay(5000);
    Serial.println("ACIO passthrough mode is off, init communication");
    acio_open();
  }
  
}

void loop() {
  if (passthrough){
    while (true){
      passthrough_loop();
    }
  }
  while (true){
      acio_loop();
  }
}

void acio_loop(){
    Serial.println("ACIO poll");
    delay(2);
}

void passthrough_loop() {

  while (Serial.available()) {      // If anything comes in Serial (USB),
    Serial1.write(Serial.read());   // read it and send it out Serial1 (pins 0 & 1)
  }
  while (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    Serial.write(Serial1.read());   // read it and send it out Serial (USB)
  }
}
