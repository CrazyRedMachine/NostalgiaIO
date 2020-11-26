//#include "NOSTHID.h"

#define MIDI
#ifdef MIDI
#include "MIDIUSB.h"
#endif

#define REPORT_DELAY 1000
//NOSTHID_ NOSTHID;
#define TOUCH
#ifdef TOUCH
  #include "Touch.h"
  Touch_ Touch;
#endif

bool passthrough = false;
#define PIN_PASSTHROUGH A3
#define PIN_LED 13

uint8_t buttonsState[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

static FILE uartout = {0} ;

static int uart_putchar (char c, FILE *stream)
{
  Serial.write(c) ;
  return 0 ;
}
#ifdef MIDI
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

static uint8_t pitch[28] = {48,50,52,53,55,57,59,60,62,64,65,67,69,71,72,74,76,77,79,81,83,84,86,88,89,91,93,95};
void nostMidi(byte i)
{
  //note on if buttonsState is on and not already on, note off if !buttonsState and alreadyon
 static bool current[28] = {false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false};

 if (buttonsState[i] && !current[i]){
  noteOn(0,pitch[i],buttonsState[i]+0x30);
  current[i] = true;
 }
 else if (!buttonsState[i] && current[i]){
  noteOff(0,pitch[i],0);
  current[i] = false;
 }

}
// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
#endif
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
  /*  Serial.println("ACIO passthrough mode is off, init communication");
    while (digitalRead(PIN_PASSTHROUGH) == HIGH){
      Serial.println("press the button to continue process");
      delay(1000);
    }*/
    Touch.begin();
    Touch.setLightMode(LIGHTMODE_COMBINED);
    Touch.init_acio();
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
   static unsigned long lastReport = 0;
   static uint8_t send_multitouch_cooldown = 5;
   static uint8_t send_lamp_cooldown = 5;
    Touch.poll();
   send_lamp_cooldown--;
    if (send_lamp_cooldown == 0)
    {
      Touch.updateLeds();
      send_lamp_cooldown = 5;
    }
  /* USB DATA */
  if ( ( (micros() - lastReport) >= REPORT_DELAY) )
  {
   
    if (digitalRead(PIN_PASSTHROUGH) == LOW) {
      /* multitouch */
      
      send_multitouch_cooldown--;
      if (send_multitouch_cooldown == 0)
      {
        Touch.updateState();
        Touch.sendState();
        send_multitouch_cooldown = 5;
      }
    }
    else 
    {
      /* gamepad */
//      NOSTHID.sendState();     
#ifdef MIDI
for (int i = 0; i<28; i++)
{
   nostMidi(i);
}
//noteOnOff(0, 48, 64);   // Channel 0, middle C, normal velocity
      MidiUSB.flush();
      // controlChange(0, 10, 65); // Set the value of controller 10 on channel 0 to 65
#endif
    }
    
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
