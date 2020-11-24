#include "Touch.h"

#if defined(_USING_HID)

#define CONTACT_COUNT_MAXIMUM 10
#define REPORTID_TOUCH        0x01

#define LOWER_PART 9000
#define CENTER_PART 5000
#define UPPER_PART 1000
#define UPPER_PIN 7
#define CENTER_PIN 6
#define TOUCH_HEIGHT (digitalRead(CENTER_PIN) == LOW) ? CENTER_PART : ( (digitalRead(UPPER_PIN) == LOW) ? UPPER_PART : LOWER_PART )

static const uint8_t _hidReportDescriptor[] PROGMEM = {
  0x05, 0x0D,                    // USAGE_PAGE(Digitizers)
  0x09, 0x04,                    // USAGE     (Touch Screen)
  0xA1, 0x01,                    // COLLECTION(Application)
  0x85, REPORTID_TOUCH,          //   REPORT_ID (Touch)

  // define the maximum amount of fingers that the device supports
  0x09, 0x55,                    //   USAGE (Contact Count Maximum)
  0x25, CONTACT_COUNT_MAXIMUM,   //   LOGICAL_MAXIMUM (CONTACT_COUNT_MAXIMUM)
  0xB1, 0x02,                    //   FEATURE (Data,Var,Abs)

  // define the actual amount of fingers that are concurrently touching the screen
  0x09, 0x54,                    //   USAGE (Contact count)
  0x95, 0x01,                    //   REPORT_COUNT(1)
  0x75, 0x08,                    //   REPORT_SIZE (8)
  0x81, 0x02,                    //   INPUT (Data,Var,Abs)

  // declare a finger collection
  0x09, 0x22,                    //   USAGE (Finger)
  0xA1, 0x02,                    //   COLLECTION (Logical)

  // declare an identifier for the finger
  0x09, 0x51,                    //     USAGE (Contact Identifier)
  0x75, 0x08,                    //     REPORT_SIZE (8)
  0x95, 0x01,                    //     REPORT_COUNT (1)
  0x81, 0x02,                    //     INPUT (Data,Var,Abs)

  // declare Tip Switch and In Range
  0x09, 0x42,                    //     USAGE (Tip Switch)
  0x09, 0x32,                    //     USAGE (In Range)
  0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
  0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
  0x75, 0x01,                    //     REPORT_SIZE (1)
  0x95, 0x02,                    //     REPORT_COUNT(2)
  0x81, 0x02,                    //     INPUT (Data,Var,Abs)

  // declare the remaining 6 bits of the first data byte as constant -> the driver will ignore them
  0x95, 0x06,                    //     REPORT_COUNT (6)
  0x81, 0x03,                    //     INPUT (Cnst,Ary,Abs)

  // define absolute X and Y coordinates of 16 bit each (percent values multiplied with 100)
  0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
  0x09, 0x30,                    //     Usage (X)
  0x09, 0x31,                    //     Usage (Y)
  0x16, 0x00, 0x00,              //     Logical Minimum (0)
  0x26, 0x10, 0x27,              //     Logical Maximum (10000)
  0x36, 0x00, 0x00,              //     Physical Minimum (0)
  0x46, 0x10, 0x27,              //     Physical Maximum (10000)
  0x66, 0x00, 0x00,              //     UNIT (None)
  0x75, 0x10,                    //     Report Size (16),
  0x95, 0x02,                    //     Report Count (2),
  0x81, 0x02,                    //     Input (Data,Var,Abs)
  0xC0,                          //   END_COLLECTION
  0xC0                           // END_COLLECTION

  // with this declaration a data packet must be sent as:
  // byte 1   -> "contact count"        (always == 1)
  // byte 2   -> "contact identifier"   (any value)
  // byte 3   -> "Tip Switch" state     (bit 0 = Tip Switch up/down, bit 1 = In Range)
  // byte 4,5 -> absolute X coordinate  (0...10000)
  // byte 6,7 -> absolute Y coordinate  (0...10000)
};


typedef struct Finger {
  int contact;
  uint16_t x;
  uint16_t y;
  bool already_off; 
  bool already_on; //send reports only on state change
} Finger;

static Finger fingers[CONTACT_COUNT_MAXIMUM];

typedef struct stack {
  int size;
  int data[CONTACT_COUNT_MAXIMUM];
} stack_t;

stack_t contact_stack;

static bool stack_push(stack_t *st, int val)
{
  if (st->size < CONTACT_COUNT_MAXIMUM)
  {
    st->data[st->size++] = val;
    return true;
  }
  return false;
}
static int stack_pop(stack_t *st)
{
  if (st->size > 0)
  {
    st->size--;
    return st->data[st->size];
  }
  Serial.println("ABORT OPERATION, ILLEGAL POP"); 
  return -1;
}
static bool stack_isempty(stack *st)
{
  return (st->size == 0);
}

Touch_::Touch_() {
  pinMode(CENTER_PIN, INPUT_PULLUP);
  pinMode(UPPER_PIN, INPUT_PULLUP);
  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);

  for (int i = 0; i < CONTACT_COUNT_MAXIMUM; i++) {
    fingers[i].contact = 0;
    fingers[i].x = 0;
    fingers[i].y = 0;
    fingers[i].already_off = true;
  }
}

void Touch_::begin(void) {
  //init contact_stack
  contact_stack.size = 0;
  for (int i=CONTACT_COUNT_MAXIMUM-1; i>=0; i--)
  {
      stack_push(&contact_stack, i);
  }
}

void Touch_::end(void) {
}


void Touch_::send(uint8_t identifier) {
  // calculate current contact count
  uint8_t contact = 0;
  
  for (int i = 0; i < CONTACT_COUNT_MAXIMUM; i++) {
    if (fingers[i].contact) {
      contact += 1;
    }
  }

  // create data array
  uint8_t usbdata[7];
  usbdata[0] = contact;
  usbdata[1] = identifier;
  usbdata[2] = fingers[identifier].contact;
  int16_t * datax = (int16_t *) &(usbdata[3]);
  *datax = fingers[identifier].x;
  int16_t * datay = (int16_t *) &(usbdata[5]);
  *datay = fingers[identifier].y;
  
  // send packet
  if (fingers[identifier].contact){
    fingers[identifier].already_off = false;
      HID().SendReport(REPORTID_TOUCH, usbdata, 7);
    
  } else if (!fingers[identifier].already_off)
  {
    fingers[identifier].already_off = true;
    HID().SendReport(REPORTID_TOUCH, usbdata, 7);
  }
  
  //

}


void Touch_::moveFingerTo(uint8_t identifier, int16_t x, int16_t y) {
  // change finger record
  fingers[identifier].contact = 1;
  fingers[identifier].x = x;
  fingers[identifier].y = y;
}

void Touch_::releaseFinger(uint8_t identifier) {
  // change finger record
  fingers[identifier].contact = 0;
  fingers[identifier].x = 0;
  fingers[identifier].y = 0;
}

void Touch_::sendState(){
  for (int i=0; i<CONTACT_COUNT_MAXIMUM; i++)
    send(i);
}

void Touch_::updateState(uint8_t *buttonsState){
  /* current[28] stores the currently used "contact_id" for the corresponding button */
  static int8_t current[28] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  uint8_t butStat[28];
  memcpy(butStat,buttonsState,28);

/* pass 1: old presses */
for (int i=0; i<28; i++)
{
  if (current[i]!=-1)
  {
    if (butStat[i] > 0)
    {
       //still pressed, but must resend report
     moveFingerTo(current[i], (i+1)*(10000/29), TOUCH_HEIGHT); 
    }
    else
    {
      //must release
      stack_push(&contact_stack, current[i]);
      releaseFinger(current[i]);
      current[i] = -1;
    }
  }
}

/* check if phase 2 necessary */
    if (stack_isempty(&contact_stack)){
//      Serial.println("all contact points used, abort");
      return;
    }
    
/* phase 2: new presses */    
  for(int i=0; i < 28; i++)
  {
    int idx = (3*i)%28; //avoid bias towards the left side of panel
    if (butStat[idx]){
      if (current[idx] == -1)
      { // new touchpoint
        int contact_id = stack_pop(&contact_stack);
        current[idx] = contact_id;
        moveFingerTo(contact_id, (idx+1)*(10000/29), TOUCH_HEIGHT);
        if (stack_isempty(&contact_stack)) return;
      }      
    } 

  }
}
  
Touch_ Touch;

#endif
