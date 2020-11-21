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
  //Serial1.begin(115200);
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

  if (!passthrough)
  {
    
    //Serial.begin(115200);
    fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &uartout ;
    Serial.println("ACIO passthrough mode is off, init communication");
    while (digitalRead(PIN_PASSTHROUGH) == HIGH){
      Serial.println("press the button to continue process");
      delay(1000);
    }
    acio_open();
    delay(500);
    panb_set_auto_poll();
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

struct ac_io_message msg;
color_t color = {0x23,0x00,0x7F};
color_t colors[6] = {{0x7F,0x23,0x00},{0x00,0x7F,0x23},{0x23,0x00,0x7F},{0xFF,0x00,0x00},{0x00,0xFF,0x00},{0x00,0x00,0xFF}};

void acio_loop(){
    static uint8_t send_lamp_cooldown = 2;
    msg.addr = 01;
    msg.cmd.code = ac_io_u16(AC_IO_PANB_POLL_REPLY);
    msg.cmd.nbytes = 16;
    if (acio_receive((uint8_t *)&msg, offsetof(struct ac_io_message, cmd.raw) + msg.cmd.nbytes))
    {
      panb_button_state_t* button_state = (panb_button_state_t *) &msg;

    for (int i=0; i<14; i++)
    {
      if (button_state->keypair[i])
      {
        uint8_t but1 = (button_state->keypair[i])>>4;
        uint8_t but2 = (button_state->keypair[i])&0xF;

        if (but1) {
          Serial.print("Button ");
          Serial.print(2*i);
          Serial.print(" : ");
          Serial.println(but1);
          panb_set_lamp_state(2*i, color);
        }
         else panb_set_lamp_state(2*i, {0,0,0});
         
        if (but2) {
          Serial.print("Button ");
          Serial.print(2*i+1);
          Serial.print(" : ");
          Serial.println(but2);
          panb_set_lamp_state(2*i+1, color);
        }
         else panb_set_lamp_state(2*i+1, {0,0,0});
      }
      else 
      {
        panb_set_lamp_state(2*i, {0,0,0});
        panb_set_lamp_state(2*i+1, {0,0,0});
      }
    }
    
    }
    send_lamp_cooldown--;
    if (send_lamp_cooldown == 0)
    {
      panb_send_lamp();
      send_lamp_cooldown = 4;
    }
    
    
    return;
    /*
    static uint8_t colorindex = 0;
    color = colors[colorindex];
    for (int i=0; i<28; i++){
    panb_set_lamp_state(i, color);
    //delay(500);
    panb_send_lamp();
    }
    for (int i=0; i<28; i++){
    panb_set_lamp_state(i, {0,0,0});
    //delay(500);
    panb_send_lamp();
    }
    Serial.println("ACIO poll");
    delay(2);
    colorindex++;
    if (colorindex > 5) colorindex = 0;*/
}

void passthrough_loop() {

  while (Serial.available()) {      // If anything comes in Serial (USB),
    Serial1.write(Serial.read());   // read it and send it out Serial1 (pins 0 & 1)
  }
  while (Serial1.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    Serial.write(Serial1.read());   // read it and send it out Serial (USB)
  }
}
