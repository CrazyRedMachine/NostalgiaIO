#include "ACIO.h"
#include "PANB.h"

/* passthrough mode (disables acio module, just acts as a serial to usb converter) */
bool passthrough = false;

static FILE uartout = {0} ;

static int uart_putchar (char c, FILE *stream)
{
  Serial.write(c) ;
  return 0 ;
}

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(57600);
  Serial1.begin(57600);
  passthrough = false;
  
  fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &uartout ;
  
  delay(5000);
  printf("BEGINNING (with printf)\n");
  delay(5000);
  if (!passthrough)
  {
    acio_open();
  }

}


void loop() {
  if (passthrough){
    passthrough_loop();
    return;
  }


}


void passthrough_loop() {

if (Serial.available()) {      // If anything comes in Serial (USB),
    Serial1.write(Serial.read());   // read it and send it out Serial1 (pins 0 & 1)
  }
  if (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    Serial.write(Serial1.read());   // read it and send it out Serial (USB)
  }
}
