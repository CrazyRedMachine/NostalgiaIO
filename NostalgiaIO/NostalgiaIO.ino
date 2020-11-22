#include "NOSTHID.h"

#define REPORT_DELAY 1000
NOSTHID_ NOSTHID;
  
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

  if (!passthrough)
  {
    
    //Serial.begin(115200);
    fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &uartout ;
    Serial.println("ACIO passthrough mode is off, init communication");
 /*   while (digitalRead(PIN_PASSTHROUGH) == HIGH){
      Serial.println("press the button to continue process");
      delay(1000);
    }*/
    NOSTHID.setLightMode(LIGHTMODE_COMBINED);
    NOSTHID.init_acio();
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


color_t color = {0x23,0x00,0x7F};
color_t colors[6] = {{0x7F,0x23,0x00},{0x00,0x7F,0x23},{0x23,0x00,0x7F},{0xFF,0x00,0x00},{0x00,0xFF,0x00},{0x00,0x00,0xFF}};

unsigned long lastReport = 0;
void acio_loop(){
   static uint8_t send_lamp_cooldown = 5;
   NOSTHID.poll();
   send_lamp_cooldown--;
    if (send_lamp_cooldown == 0)
    {
      NOSTHID.updateLeds();
      send_lamp_cooldown = 5;
    }
  /* USB DATA */
  if ( ( (micros() - lastReport) >= REPORT_DELAY) )
  {
    NOSTHID.sendState();
    lastReport = micros();
  }  

}

void passthrough_loop() {

  while (Serial.available()) {      // If anything comes in Serial (USB),
    Serial1.write(Serial.read());   // read it and send it out Serial1 (pins 0 & 1)
  }
  while (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    Serial.write(Serial1.read());   // read it and send it out Serial (USB)
  }
}
