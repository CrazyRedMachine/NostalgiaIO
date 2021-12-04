#include <EEPROM.h>
#include "NOSTHID.h"
#include "MIDIUSB.h"

#define REPORT_DELAY 1000
NOSTHID_ NOSTHID;
MIDI_ MidiUSB;

bool passthrough = false;
#define PIN_MODE A3
#define PIN_COIN 7
#define PIN_SERVICE 5 
#define PIN_TEST 6
#define PIN_LED 13
#define PIN_PASSTHROUGH PIN_SERVICE

uint8_t buttonsState[31] = {0};

static FILE uartout = {0} ;

static int uart_putchar (char c, FILE *stream)
{
  Serial.write(c) ;
  return 0 ;
}

void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);

  pinMode(PIN_MODE, INPUT_PULLUP);
  pinMode(PIN_COIN, INPUT_PULLUP);
  pinMode(PIN_SERVICE, INPUT_PULLUP);
  pinMode(PIN_TEST, INPUT_PULLUP);
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
    fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &uartout ;
    uint8_t lightMode;
    EEPROM.get(0, lightMode);
    if (lightMode < 0 || lightMode >= NUM_LIGHT_MODES)
      lightMode = 0;
    NOSTHID.setLightMode(lightMode);
    uint8_t palette;
    EEPROM.get(1, palette);
    if (palette < 0 || palette >= NUM_PALETTE)
      palette = 0;
    NOSTHID.setPalette(palette);
  
    NOSTHID.begin();
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

void acio_loop(){
   static bool modeChanged = false;
   static bool palChanged = false;
   static unsigned long lastReport = 0;
   static uint8_t send_multitouch_cooldown = 2;
   static uint8_t send_lamp_cooldown = 5;
    NOSTHID.poll();
    buttonsState[28] = ( digitalRead(PIN_SERVICE) == LOW ) ? 0xF:0;
    buttonsState[29] = ( digitalRead(PIN_TEST) == LOW ) ? 0xF:0;
    buttonsState[30] = ( digitalRead(PIN_COIN) == LOW ) ? 0xF:0;
   send_lamp_cooldown--;
    if (send_lamp_cooldown == 0)
    {
      NOSTHID.updateLeds();
      send_lamp_cooldown = 5;
    }
  
  static uint8_t initial_mode = digitalRead(PIN_MODE);
  /* USB DATA */
  if ( ( (micros() - lastReport) >= REPORT_DELAY) )
  { 
      /* midi keyboard (28 keys + test service coin) */
for (int i = 0; i<31; i++)
{
   MidiUSB.noteNOST(i);
}
      MidiUSB.flush();
    
    lastReport = micros();
  }

/* MANUAL LIGHTMODE UPDATE */
  if ( digitalRead(PIN_SERVICE) == LOW ) {
    if ( (buttonsState[0]) && (modeChanged == false)) {
      modeChanged = true;
      uint8_t mode = NOSTHID.getLightMode()+1;
      if (mode == NUM_LIGHT_MODES) mode = 0;
      NOSTHID.setLightMode(mode);
      EEPROM.put(0, mode);
    }
    else if (!(buttonsState[0])) {
      modeChanged = false;
    }

if ( (buttonsState[1]) && (palChanged == false)) {
      palChanged = true;
      uint8_t pal = NOSTHID.getPalette()+1;
      if (pal == NUM_PALETTE) pal = 0;
      NOSTHID.setPalette(pal);
      EEPROM.put(1, pal);
    }
    else if (!(buttonsState[1])) {
      palChanged = false;
    }

    
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
