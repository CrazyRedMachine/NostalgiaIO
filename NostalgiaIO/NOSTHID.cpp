#include "NOSTHID.h"

#if defined(_USING_HID)

#define CONTACT_COUNT_MAXIMUM 8
#define REPORTID_TOUCH        0x01

#define LOWER_PART 90
#define CENTER_PART 50
#define UPPER_PART 10
#define UPPER_PIN 7
#define CENTER_PIN 6
#define TOUCH_HEIGHT (digitalRead(CENTER_PIN) == LOW) ? CENTER_PART : ( (digitalRead(UPPER_PIN) == LOW) ? UPPER_PART : LOWER_PART )

/* number of physical keys which make up one virtual key (useless, please leave on 1) */
#define BLOCK_SIZE 1

static const uint8_t _hidReportDescriptorTouch[] PROGMEM = {
  0x05, 0x0D,                    // USAGE_PAGE(Digitizers)
  0x09, 0x04,                    // USAGE     (NOSTHID Screen)
  0xA1, 0x01,                    // COLLECTION(Application)
  0x85, REPORTID_TOUCH,          //   REPORT_ID (NOSTHID)

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
  0x15, 0x00,              //     Logical Minimum (0)
  0x25, 0x64,              //     Logical Maximum (100)
  0x35, 0x00,              //     Physical Minimum (0)
  0x45, 0x64,             //     Physical Maximum (100)
  0x66, 0x00, 0x00,              //     UNIT (None)
  0x75, 0x08,                    //     Report Size (8),
  0x95, 0x02,                    //     Report Count (2),
  0x81, 0x02,                    //     Input (Data,Var,Abs)
  0xC0,                          //   END_COLLECTION

  0x85, 0x02,        //   Report ID (2)   
      // 14 RGB leds (42 leds)
    0x95, 0x2A,        //   REPORT_COUNT
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x05, 0x0a,                    //   USAGE_PAGE (Ordinals)
    // Locals
    0x19, 0x01,                    //   USAGE_MINIMUM (Instance 1)
    0x29, 0x2A,        //   USAGE_MAXIMUM (Instance n)
    0xA1, 0x02,        //   Collection (Logical)
      0x09, 0x01,        //       Usage (Indicator Red)
      0x09, 0x02,        //       Usage (Indicator Red)
      0x09, 0x03,        //       Usage (Indicator Red)
      0x09, 0x04,        //       Usage (Indicator Red)
      0x09, 0x05,        //       Usage (Indicator Red)
      0x09, 0x06,        //       Usage (Indicator Red)
      0x09, 0x07,        //       Usage (Indicator Red)
      0x09, 0x08,        //       Usage (Indicator Red)
      0x09, 0x09,        //       Usage (Indicator Red)
      0x09, 0x0A,        //       Usage (Indicator Red)
      0x09, 0x0B,        //       Usage (Indicator Red)
      0x09, 0x0C,        //       Usage (Indicator Red)
      0x09, 0x0D,        //       Usage (Indicator Red)
      0x09, 0x0E,        //       Usage (Indicator Red)
      0x09, 0x0F,        //       Usage (Indicator Red)
      0x09, 0x10,        //       Usage (Indicator Red)
      0x09, 0x11,        //       Usage (Indicator Red)
      0x09, 0x12,        //       Usage (Indicator Red)
      0x09, 0x13,        //       Usage (Indicator Red)
      0x09, 0x14,        //       Usage (Indicator Red)
      0x09, 0x15,        //       Usage (Indicator Red)
      0x09, 0x16,        //       Usage (Indicator Red)
      0x09, 0x17,        //       Usage (Indicator Red)
      0x09, 0x18,        //       Usage (Indicator Red)
      0x09, 0x19,        //       Usage (Indicator Red)
      0x09, 0x1A,        //       Usage (Indicator Red)
      0x09, 0x1B,        //       Usage (Indicator Red)
      0x09, 0x1C,        //       Usage (Indicator Red)
      0x09, 0x1D,        //       Usage (Indicator Red)
      0x09, 0x1E,        //       Usage (Indicator Red)
      0x09, 0x1F,        //       Usage (Indicator Red)
      0x09, 0x20,        //       Usage (Indicator Red)
      0x09, 0x21,        //       Usage (Indicator Red)
      0x09, 0x22,        //       Usage (Indicator Red)
      0x09, 0x23,        //       Usage (Indicator Red)
      0x09, 0x24,        //       Usage (Indicator Red)
      0x09, 0x25,        //       Usage (Indicator Red)
      0x09, 0x26,        //       Usage (Indicator Red)
      0x09, 0x27,        //       Usage (Indicator Red)
      0x09, 0x28,        //       Usage (Indicator Red)
      0x09, 0x29,        //       Usage (Indicator Red)
      0x09, 0x2A,        //       Usage (Indicator Red)
      0x91, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection (RGB led)

  0x85, 0x03,        //   Report ID (3)   
      // 14 RGB leds (42 leds)
    0x95, 0x2A,        //   REPORT_COUNT
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x05, 0x0a,                    //   USAGE_PAGE (Ordinals)
    0x19, 0x2B,                    //   USAGE_MINIMUM (Instance 1)
    0x29, 0x54,        //   USAGE_MAXIMUM (Instance n)
    0xA1, 0x02,        //   Collection (Logical)
      0x09, 0x2B,        //       Usage (Indicator Red)
      0x09, 0x2C,        //       Usage (Indicator Red)
      0x09, 0x2D,        //       Usage (Indicator Red)
      0x09, 0x2E,        //       Usage (Indicator Red)
      0x09, 0x2F,        //       Usage (Indicator Red)
      0x09, 0x30,        //       Usage (Indicator Red)
      0x09, 0x31,        //       Usage (Indicator Red)
      0x09, 0x32,        //       Usage (Indicator Red)
      0x09, 0x33,        //       Usage (Indicator Red)
      0x09, 0x34,        //       Usage (Indicator Red)
      0x09, 0x35,        //       Usage (Indicator Red)
      0x09, 0x36,        //       Usage (Indicator Red)
      0x09, 0x37,        //       Usage (Indicator Red)
      0x09, 0x38,        //       Usage (Indicator Red)
      0x09, 0x39,        //       Usage (Indicator Red)
      0x09, 0x3A,        //       Usage (Indicator Red)
      0x09, 0x3B,        //       Usage (Indicator Red)
      0x09, 0x3C,        //       Usage (Indicator Red)
      0x09, 0x3D,        //       Usage (Indicator Red)
      0x09, 0x3E,        //       Usage (Indicator Red)
      0x09, 0x3F,        //       Usage (Indicator Red)
      0x09, 0x40,        //       Usage (Indicator Red)
      0x09, 0x41,        //       Usage (Indicator Red)
      0x09, 0x42,        //       Usage (Indicator Red)
      0x09, 0x43,        //       Usage (Indicator Red)
      0x09, 0x44,        //       Usage (Indicator Red)
      0x09, 0x45,        //       Usage (Indicator Red)
      0x09, 0x46,        //       Usage (Indicator Red)
      0x09, 0x47,        //       Usage (Indicator Red)
      0x09, 0x48,        //       Usage (Indicator Red)
      0x09, 0x49,        //       Usage (Indicator Red)
      0x09, 0x4A,        //       Usage (Indicator Red)
      0x09, 0x4B,        //       Usage (Indicator Red)
      0x09, 0x4C,        //       Usage (Indicator Red)
      0x09, 0x4D,        //       Usage (Indicator Red)
      0x09, 0x4E,        //       Usage (Indicator Red)
      0x09, 0x4F,        //       Usage (Indicator Red)
      0x09, 0x50,        //       Usage (Indicator Red)
      0x09, 0x51,        //       Usage (Indicator Red)
      0x09, 0x52,        //       Usage (Indicator Red)
      0x09, 0x53,        //       Usage (Indicator Red)
      0x09, 0x54,        //       Usage (Indicator Red)
      0x91, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection (RGB led)

    /* HID modeswitch paletteswitch request (no usage page etc so it's not picked up by the tools) */
  0x85, 0x06,        //   Report ID (6)
    0x95, 0x02,        //     Report Count (1)
    0x75, 0x08,        //     Report Size (9)
    0x91, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  
  0xC0                           // END_COLLECTION

  // with this declaration a data packet must be sent as:
  // byte 1   -> "contact count"        (always == 1)
  // byte 2   -> "contact identifier"   (any value)
  // byte 3   -> "Tip Switch" state     (bit 0 = Tip Switch up/down, bit 1 = In Range)
  // byte 4,5 -> absolute X coordinate  (0...10000)
  // byte 6,7 -> absolute Y coordinate  (0...10000)
};

static const uint8_t _hidReportDescriptorLights[] PROGMEM = {
  0x05, 0x01,                    // USAGE_PAGE(Digitizers)
  0x09, 0x04,                    // USAGE     (NOSTHID Screen)
  0xA1, 0x01,                    // COLLECTION(Application)
  0x85, REPORTID_TOUCH,          //   REPORT_ID (NOSTHID)

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
  0x15, 0x00,              //     Logical Minimum (0)
  0x25, 0x64,              //     Logical Maximum (100)
  0x35, 0x00,              //     Physical Minimum (0)
  0x45, 0x64,             //     Physical Maximum (100)
  0x66, 0x00, 0x00,              //     UNIT (None)
  0x75, 0x08,                    //     Report Size (8),
  0x95, 0x02,                    //     Report Count (2),
  0x81, 0x02,                    //     Input (Data,Var,Abs)
  0xC0,                          //   END_COLLECTION

  0x85, 0x02,        //   Report ID (2)   
      // 14 RGB leds (42 leds)
    0x95, 0x2A,        //   REPORT_COUNT
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x05, 0x0a,                    //   USAGE_PAGE (Ordinals)
    // Locals
    0x19, 0x01,                    //   USAGE_MINIMUM (Instance 1)
    0x29, 0x2A,        //   USAGE_MAXIMUM (Instance n)
    0xA1, 0x02,        //   Collection (Logical)
      0x09, 0x01,        //       Usage (Indicator Red)
      0x09, 0x02,        //       Usage (Indicator Red)
      0x09, 0x03,        //       Usage (Indicator Red)
      0x09, 0x04,        //       Usage (Indicator Red)
      0x09, 0x05,        //       Usage (Indicator Red)
      0x09, 0x06,        //       Usage (Indicator Red)
      0x09, 0x07,        //       Usage (Indicator Red)
      0x09, 0x08,        //       Usage (Indicator Red)
      0x09, 0x09,        //       Usage (Indicator Red)
      0x09, 0x0A,        //       Usage (Indicator Red)
      0x09, 0x0B,        //       Usage (Indicator Red)
      0x09, 0x0C,        //       Usage (Indicator Red)
      0x09, 0x0D,        //       Usage (Indicator Red)
      0x09, 0x0E,        //       Usage (Indicator Red)
      0x09, 0x0F,        //       Usage (Indicator Red)
      0x09, 0x10,        //       Usage (Indicator Red)
      0x09, 0x11,        //       Usage (Indicator Red)
      0x09, 0x12,        //       Usage (Indicator Red)
      0x09, 0x13,        //       Usage (Indicator Red)
      0x09, 0x14,        //       Usage (Indicator Red)
      0x09, 0x15,        //       Usage (Indicator Red)
      0x09, 0x16,        //       Usage (Indicator Red)
      0x09, 0x17,        //       Usage (Indicator Red)
      0x09, 0x18,        //       Usage (Indicator Red)
      0x09, 0x19,        //       Usage (Indicator Red)
      0x09, 0x1A,        //       Usage (Indicator Red)
      0x09, 0x1B,        //       Usage (Indicator Red)
      0x09, 0x1C,        //       Usage (Indicator Red)
      0x09, 0x1D,        //       Usage (Indicator Red)
      0x09, 0x1E,        //       Usage (Indicator Red)
      0x09, 0x1F,        //       Usage (Indicator Red)
      0x09, 0x20,        //       Usage (Indicator Red)
      0x09, 0x21,        //       Usage (Indicator Red)
      0x09, 0x22,        //       Usage (Indicator Red)
      0x09, 0x23,        //       Usage (Indicator Red)
      0x09, 0x24,        //       Usage (Indicator Red)
      0x09, 0x25,        //       Usage (Indicator Red)
      0x09, 0x26,        //       Usage (Indicator Red)
      0x09, 0x27,        //       Usage (Indicator Red)
      0x09, 0x28,        //       Usage (Indicator Red)
      0x09, 0x29,        //       Usage (Indicator Red)
      0x09, 0x2A,        //       Usage (Indicator Red)
      0x91, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection (RGB led)

  0x85, 0x03,        //   Report ID (3)   
      // 14 RGB leds (42 leds)
    0x95, 0x2A,        //   REPORT_COUNT
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x05, 0x0a,                    //   USAGE_PAGE (Ordinals)
    0x19, 0x2B,                    //   USAGE_MINIMUM (Instance 1)
    0x29, 0x54,        //   USAGE_MAXIMUM (Instance n)
    0xA1, 0x02,        //   Collection (Logical)
      0x09, 0x2B,        //       Usage (Indicator Red)
      0x09, 0x2C,        //       Usage (Indicator Red)
      0x09, 0x2D,        //       Usage (Indicator Red)
      0x09, 0x2E,        //       Usage (Indicator Red)
      0x09, 0x2F,        //       Usage (Indicator Red)
      0x09, 0x30,        //       Usage (Indicator Red)
      0x09, 0x31,        //       Usage (Indicator Red)
      0x09, 0x32,        //       Usage (Indicator Red)
      0x09, 0x33,        //       Usage (Indicator Red)
      0x09, 0x34,        //       Usage (Indicator Red)
      0x09, 0x35,        //       Usage (Indicator Red)
      0x09, 0x36,        //       Usage (Indicator Red)
      0x09, 0x37,        //       Usage (Indicator Red)
      0x09, 0x38,        //       Usage (Indicator Red)
      0x09, 0x39,        //       Usage (Indicator Red)
      0x09, 0x3A,        //       Usage (Indicator Red)
      0x09, 0x3B,        //       Usage (Indicator Red)
      0x09, 0x3C,        //       Usage (Indicator Red)
      0x09, 0x3D,        //       Usage (Indicator Red)
      0x09, 0x3E,        //       Usage (Indicator Red)
      0x09, 0x3F,        //       Usage (Indicator Red)
      0x09, 0x40,        //       Usage (Indicator Red)
      0x09, 0x41,        //       Usage (Indicator Red)
      0x09, 0x42,        //       Usage (Indicator Red)
      0x09, 0x43,        //       Usage (Indicator Red)
      0x09, 0x44,        //       Usage (Indicator Red)
      0x09, 0x45,        //       Usage (Indicator Red)
      0x09, 0x46,        //       Usage (Indicator Red)
      0x09, 0x47,        //       Usage (Indicator Red)
      0x09, 0x48,        //       Usage (Indicator Red)
      0x09, 0x49,        //       Usage (Indicator Red)
      0x09, 0x4A,        //       Usage (Indicator Red)
      0x09, 0x4B,        //       Usage (Indicator Red)
      0x09, 0x4C,        //       Usage (Indicator Red)
      0x09, 0x4D,        //       Usage (Indicator Red)
      0x09, 0x4E,        //       Usage (Indicator Red)
      0x09, 0x4F,        //       Usage (Indicator Red)
      0x09, 0x50,        //       Usage (Indicator Red)
      0x09, 0x51,        //       Usage (Indicator Red)
      0x09, 0x52,        //       Usage (Indicator Red)
      0x09, 0x53,        //       Usage (Indicator Red)
      0x09, 0x54,        //       Usage (Indicator Red)
      0x91, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection (RGB led)

    /* HID modeswitch paletteswitch request (no usage page etc so it's not picked up by the tools) */
  0x85, 0x06,        //   Report ID (6)
    0x95, 0x02,        //     Report Count (1)
    0x75, 0x08,        //     Report Size (9)
    0x91, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  
  0xC0                           // END_COLLECTION

  // with this declaration a data packet must be sent as:
  // byte 1   -> "contact count"        (always == 1)
  // byte 2   -> "contact identifier"   (any value)
  // byte 3   -> "Tip Switch" state     (bit 0 = Tip Switch up/down, bit 1 = In Range)
  // byte 4,5 -> absolute X coordinate  (0...10000)
  // byte 6,7 -> absolute Y coordinate  (0...10000)
};

uint8_t *_hidReportDescriptor;
uint16_t _hidReportDescriptorSize;

typedef struct Finger {
  int contact;
  uint16_t x;
  uint16_t y;
  bool already_off; //send reports only on state change
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

#define PIN_MODE A3
NOSTHID_::NOSTHID_(void) : PluggableUSBModule(1, 1, epType) {
   epType[0] = EP_TYPE_INTERRUPT_IN;
   
  if (digitalRead(PIN_MODE) == LOW)
   {
    _hidReportDescriptor = _hidReportDescriptorTouch;
    _hidReportDescriptorSize = sizeof(_hidReportDescriptorTouch);
   }
   else
   {
    _hidReportDescriptor = _hidReportDescriptorLights;
    _hidReportDescriptorSize = sizeof(_hidReportDescriptorLights);
   }
      PluggableUSB().plug(this);
    }

    int NOSTHID_::getInterface(byte* interfaceCount) {
      *interfaceCount += 1; // uses 1
      HIDDescriptor hidInterface = {
        D_INTERFACE(pluggedInterface, 1, USB_DEVICE_CLASS_HUMAN_INTERFACE, HID_SUBCLASS_NONE, HID_PROTOCOL_NONE),
        D_HIDREPORT(_hidReportDescriptorSize),
        D_ENDPOINT(USB_ENDPOINT_IN(pluggedEndpoint), USB_ENDPOINT_TYPE_INTERRUPT, USB_EP_SIZE, 0x01) // this last parameter is the bInterval (requested polling rate)
      };
      return USB_SendControl(0, &hidInterface, sizeof(hidInterface));
    } 
 
    int NOSTHID_::getDescriptor(USBSetup& setup)
    {
      // Check if this is a HID Class Descriptor request
      if (setup.bmRequestType != REQUEST_DEVICETOHOST_STANDARD_INTERFACE) { return 0; }
      if (setup.wValueH != HID_REPORT_DESCRIPTOR_TYPE) { return 0; }

      // In a HID Class Descriptor wIndex contains the interface number
      if (setup.wIndex != pluggedInterface) { return 0; }

      return USB_SendControl(TRANSFER_PGM, _hidReportDescriptor, _hidReportDescriptorSize);
    }
    
    bool NOSTHID_::setup(USBSetup& setup)
    {
      if (pluggedInterface != setup.wIndex) {
        return false;
      }

      byte request = setup.bRequest;
      byte requestType = setup.bmRequestType;

      if (requestType == REQUEST_DEVICETOHOST_CLASS_INTERFACE)
      {
        return true;
      }
      
      if (requestType == REQUEST_HOSTTODEVICE_CLASS_INTERFACE) {
        if (request == HID_SET_REPORT) {
          if(setup.wValueH == HID_REPORT_TYPE_OUTPUT && setup.wLength == 43){
            byte tmp[43];
            USB_RecvControl(tmp, 43);
            if (tmp[0] == 2) memcpy(led_data, tmp, 43);
            else memcpy(led_data+43, tmp+1, 42);
            lastHidUpdate = millis();
            
            return true;
          }
          else if (setup.wValueH == HID_REPORT_TYPE_OUTPUT && setup.wLength == 3){
            USB_RecvControl(mode_data, 3);
            updateLightMode();
            return true;
          }
        }
      }

      return false;
    }
     
    uint8_t NOSTHID_::getShortName(char *name)
    {
      name[0] = 'N';
      name[1] = 'O';
      name[2] = 'S';
      name[3] = 'T';
      return 4;
    }
    
void NOSTHID_::begin(void) {
  pinMode(CENTER_PIN, INPUT_PULLUP);
  pinMode(UPPER_PIN, INPUT_PULLUP);
  for (int i = 0; i < CONTACT_COUNT_MAXIMUM; i++) {
    fingers[i].contact = 0;
    fingers[i].x = 0;
    fingers[i].y = 0;
    fingers[i].already_off = true;
  }
  //init contact_stack
  contact_stack.size = 0;
  for (int i=CONTACT_COUNT_MAXIMUM-1; i>=0; i--)
  {
      stack_push(&contact_stack, i);
  }
}

void NOSTHID_::end(void) {
}


int NOSTHID_::send(uint8_t identifier) {
  // calculate current contact count
  uint8_t contact = 0;
  
  for (int i = 0; i < CONTACT_COUNT_MAXIMUM; i++) {
    if (fingers[i].contact) {
      contact += 1;
    }
  }

  // create data array
  uint8_t usbdata[6];
  usbdata[0] = REPORTID_TOUCH;
  usbdata[1] = contact;
  usbdata[2] = identifier;
  usbdata[3] = fingers[identifier].contact;
  int8_t * datax = (int8_t *) &(usbdata[4]);
  *datax = fingers[identifier].x;
  int8_t * datay = (int8_t *) &(usbdata[5]);
  *datay = fingers[identifier].y;
  
  // send packet
  if (fingers[identifier].contact){
    fingers[identifier].already_off = false;
    return USB_Send(pluggedEndpoint | TRANSFER_RELEASE, usbdata, 6);   
  } else if (!fingers[identifier].already_off)
  {
    fingers[identifier].already_off = true;
    return USB_Send(pluggedEndpoint | TRANSFER_RELEASE, usbdata, 6); 
  }
  
  //

}


void NOSTHID_::moveFingerTo(uint8_t identifier, int16_t x, int16_t y) {
  // change finger record
  fingers[identifier].contact = 1;
  fingers[identifier].x = x;
  fingers[identifier].y = y;
}

void NOSTHID_::releaseFinger(uint8_t identifier) {
  // change finger record
  fingers[identifier].contact = 0;
  fingers[identifier].x = 0;
  fingers[identifier].y = 0;
}

int NOSTHID_::sendState(){
  for (int i=0; i<CONTACT_COUNT_MAXIMUM; i++)
    send(i);

 return 0;
}

static void spliceTab(uint8_t *tab){
 memset(tab, 0, 28);
 int i=0;
 while (i < 28)
 {
   for (int j=0; j<BLOCK_SIZE; j++)
   {
     if (i+j > 27) break;
     tab[i] = (buttonsState[i+j]>tab[i])?buttonsState[i+j]:tab[i];
   }
   i+=BLOCK_SIZE;
 }
}

void NOSTHID_::updateState(){
  /* current[28] stores the currently used "contact_id" for the corresponding button */
  static int8_t current[28] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  uint8_t butStat[28] = {0};
  spliceTab(butStat);
   
//  memcpy(butStat,buttonsState,28);
//  uint8_t *butStat = buttonsState;
/* pass 1: old presses */
for (int i=0; i<28; i++)
{
  if (current[i]!=-1)
  {
    if (butStat[i] > 0)
    {
       //still pressed, but must resend report
     moveFingerTo(current[i], (2*i+1+BLOCK_SIZE)*(10000/29)*0.005, TOUCH_HEIGHT); 
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
        moveFingerTo(contact_id, (2*idx+1+BLOCK_SIZE)*(10000/29)*0.005, TOUCH_HEIGHT);
        if (stack_isempty(&contact_stack)) return;
      }      
    } 

  }
}

/* CUSTOM NOST FUNCTIONS */
    void NOSTHID_::init_acio(void){
      acio_open();
      delay(500);
      panb_set_auto_input();
    }

    void NOSTHID_::poll(){
      struct ac_io_message msg;
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

          buttonsState[2*i] = (but1)? but1 : 0;
          buttonsState[2*i+1] = (but2)? but2 : 0;
       }
       else 
       {
          buttonsState[2*i] = 0;
          buttonsState[2*i+1] = 0;
       }
     }
    
    }
      
    }
    
    uint8_t NOSTHID_::getLightMode(){
      return lightMode;
    }
    
    uint8_t NOSTHID_::getPalette(){
      return palette;
    }
    
    unsigned long NOSTHID_::getLastHidUpdate(){
      return lastHidUpdate;
    }
    
    void NOSTHID_::setLightMode(uint8_t mode){
      if ((mode >= NUM_LIGHT_MODES) || (mode < 0)) {
        lightMode = 2;
        return;
      }
      lightMode = mode;
    }
    void NOSTHID_::setPalette(uint8_t pal){
      if ((pal >= NUM_PALETTE) || (pal < 0)) {
        palette = 1;
        return;
      }
      palette = pal;
    }
    
    void NOSTHID_::updateLightMode(){
      uint8_t* mode = (uint8_t*)&(mode_data[1]);
      uint8_t* pal = (uint8_t*)&(mode_data[2]);
      if (*mode < NUM_LIGHT_MODES) {
        setLightMode(*mode);
        mode_data[1] = 0xFF;
      }
      if (*pal < NUM_PALETTE) {
        setPalette(*pal);
        mode_data[2] = 0xFF;
      }
     }

    static color_t color_reactive(uint8_t button)
    {
      if (buttonsState[button]) return PALETTE_COLOR_2;

      return {0,0,0};
    }

    static color_t color_invert(uint8_t button)
    {
      if (!buttonsState[button]) return PALETTE_COLOR_2;

      return {0,0,0};
    }
    
    static color_t color_interlace(uint8_t button)
    {
      
      if (buttonsState[button]){
        switch (button%3)
        {
          case 0:          
            return PALETTE_COLOR_1;
          case 1:
            return PALETTE_COLOR_2;
          case 2:
            return PALETTE_COLOR_3;
        }
      }

      return {0,0,0};
    }

const uint8_t HSVpower[121] = 
{0, 2, 4, 6, 8, 11, 13, 15, 17, 19, 21, 23, 25, 28, 30, 32, 34, 36, 38, 40,
42, 45, 47, 49, 51, 53, 55, 57, 59, 62, 64, 66, 68, 70, 72, 74, 76, 79, 81, 
83, 85, 87, 89, 91, 93, 96, 98, 100, 102, 104, 106, 108, 110, 113, 115, 117, 
119, 121, 123, 125, 127, 130, 132, 134, 136, 138, 140, 142, 144, 147, 149, 
151, 153, 155, 157, 159, 161, 164, 166, 168, 170, 172, 174, 176, 178, 181, 
183, 185, 187, 189, 191, 193, 195, 198, 200, 202, 204, 206, 208, 210, 212, 
215, 217, 219, 221, 223, 225, 227, 229, 232, 234, 236, 238, 240, 242, 244, 
246, 249, 251, 253, 255};
#define NBSHADES 28
#define WAVESPEED 40
    static color_t color_rainbow(uint8_t button)
    {
      static unsigned long startTime = millis();
      uint16_t angle;
      if (!buttonsState[button]){
        angle = ((button-((millis()-startTime)/(1000/WAVESPEED)))%NBSHADES)*360/NBSHADES;
      } else {
        return {0,0,0};
        /* this one makes the reverse rainbow on held keys but that makes too much data transfers and might make
           the polling go wrong */
        angle = ((button+((millis()-startTime)/(1000/WAVESPEED)))%NBSHADES)*360/NBSHADES;
      }
      byte red, green, blue;
      if (angle<120) {red = HSVpower[120-angle]; green = HSVpower[angle]; blue = 0;} 
      else if (angle<240) {red = 0;  green = HSVpower[240-angle]; blue = HSVpower[angle-120];} 
      else {red = HSVpower[angle-240]; green = 0; blue = HSVpower[360-angle];}
                 
      return {red, green, blue};
    }
#undef NBSHADES
#undef WAVESPEED

#define WAVESPEED 30
    static color_t color_wave(uint8_t button)
    {
      static unsigned long startTime = millis();
      uint16_t angle;
      bool pressed = !!buttonsState[button];
      if (pressed){
        angle = ((button-((millis()-startTime)/(1000/WAVESPEED)))%10)*360/12;
      } else angle = ((button+((millis()-startTime)/(1000/WAVESPEED)))%10)*360/12;
      byte red, green, blue;
      if (angle<120) {red = HSVpower[120-angle]; green = HSVpower[angle]; blue = 0;} 
      else if (angle<240) {red = 0;  green = HSVpower[240-angle]; blue = HSVpower[angle-120];} 
      else {red = HSVpower[angle-240]; green = 0; blue = HSVpower[360-angle];}

      if (!pressed && blue) return PALETTE_COLOR_3;
      if (pressed) return PALETTE_COLOR_2;
      return COLOR_OFF;
      
      if (pressed) return {PALETTE_COLOR_3.red* ((float)red/256.),0,0};
      return {0,0,PALETTE_COLOR_3.blue* ((float)blue/256.)};
    }
#undef WAVESPEED

    
#define WAVESPEED 75
    static color_t color_breath(uint8_t button)
    {
      static unsigned long startTime = 0;
      static unsigned long currTime = 0;
      static unsigned long cooldown = 0;

      if (cooldown != 0)
      {
        cooldown--;
        color_t res = {0,0,0};
        if (buttonsState[button]) res = PALETTE_COLOR_1;
        return res;
      }
      currTime++;
      uint16_t brightness = ((currTime-startTime)/(1000/WAVESPEED))%511;
      if (brightness>255) brightness = 255-(brightness-255);
      byte brit = (byte) (brightness & 0xFF);
      if (brit==0){
        cooldown = 75;
      }
      
      if (!buttonsState[button]) return {PALETTE_COLOR_3.red* ((float)brit/256.), PALETTE_COLOR_3.green* ((float)brit/256.), PALETTE_COLOR_3.blue * ((float)brit/256.)};
      return PALETTE_COLOR_1;
    }
#undef WAVESPEED

#define FADERATE 80
    static color_t color_fade(uint8_t button)
    {
      static byte fade[28] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      bool pressed = !!buttonsState[button];

      if (fade[button]>0)
      {
        fade[button]--; 
      }
      
      if (pressed)
      {
        fade[button] = FADERATE;
      }
      float brit = fade[button]*192/FADERATE;
      return {PALETTE_COLOR_1.red* ((float)brit/256.), PALETTE_COLOR_1.green* ((float)brit/256.), PALETTE_COLOR_1.blue * ((float)brit/256.)};
    }
#undef FADERATE

#define FADERATE 80
#define DELTA_HUE 3
    static color_t color_rainbow_fade(uint8_t button)
    {
      static bool new_pass = false; //trick to avoid speeding up last_angle if multiple buttons are being pressed
      static int last_angle = 0;
      static color_t curr_color[28] = {COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF};
      static byte fade[28] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      bool pressed = !!buttonsState[button];
      
      if (button == 0) new_pass = true;
      
      if (pressed)
      {
        if (new_pass){
          new_pass = false;
          last_angle+= DELTA_HUE;
          if (last_angle==360) last_angle=0;
        }
      int angle=last_angle;
      byte red, green, blue;
      if (angle<120) {red = HSVpower[120-angle]; green = HSVpower[angle]; blue = 0;} 
      else if (angle<240) {red = 0;  green = HSVpower[240-angle]; blue = HSVpower[angle-120];} 
      else {red = HSVpower[angle-240]; green = 0; blue = HSVpower[360-angle];}

      curr_color[button] = {red,green,blue};
      fade[button] = FADERATE;
      }
 
      if (fade[button]>0)
      {
        fade[button]--; 
      }
      
      float brit = fade[button]*256/FADERATE;
      return {curr_color[button].red* (0.75*(float)brit/256.), curr_color[button].green* (0.75*(float)brit/256.), curr_color[button].blue * (0.75*(float)brit/256.)};
    }
#undef FADERATE
#undef DELTA_HUE

#define FADERATE 80
    static color_t color_velocity_fade(uint8_t button)
    {
      static color_t curr_color[28] = {COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF, COLOR_OFF};
      static byte fade[28] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      bool pressed = !!buttonsState[button];
      
      if (pressed)
      {
        /* PALETTE_COLOR_3 on low velocity which goes further towards PALETTE_COLOR_1 as velocity grows */
      float max_vel = (button%2==0)?15.:14.;
      float ratio = (float)(buttonsState[button])*1./max_vel;
      color_t color = {PALETTE_COLOR_3.red * (1-ratio) + PALETTE_COLOR_1.red * ratio, PALETTE_COLOR_3.green * (1-ratio) + PALETTE_COLOR_1.green * ratio, PALETTE_COLOR_3.blue * (1-ratio) + PALETTE_COLOR_1.blue * ratio};
      curr_color[button] = color;
      fade[button] = FADERATE;
      }
 
      if (fade[button]>0)
      {
        fade[button]--; 
      }
      
      float brit = fade[button]*256/FADERATE;
      return {curr_color[button].red* (0.75*(float)brit/256.), curr_color[button].green* (0.75*(float)brit/256.), curr_color[button].blue * (0.75*(float)brit/256.)};
    }
#undef FADERATE

    void NOSTHID_::updateLeds(bool hid, color_t (*func)(uint8_t)){
      if (hid)
        panb_set_lamp_state_batch((uint8_t*)&(led_data[1]));

      if (func != NULL)
      {
        for (int i=0; i<28; i++)
        {
          color_t color = func(i);
          if (color.red|color.green|color.blue != 0) {
            panb_set_lamp_state(i, func(i), true);
          }
        }
      }
      
      panb_send_lamp();
      panb_set_lamp_state_batch(NULL);
    }

    void NOSTHID_::updateLeds(){
      switch (lightMode)
      {
        case LIGHTMODE_HID:
          if ((millis()-getLastHidUpdate()) > 3000)      
            updateLeds(false, &color_reactive);
          else
            updateLeds(true, NULL);
          break;       
        case LIGHTMODE_COMBINED:
          updateLeds(true, &color_reactive);
          break;
        case LIGHTMODE_INVERT:
          updateLeds(true, &color_invert);
          break;
        case LIGHTMODE_INTERLACE:
          updateLeds(true, &color_interlace);
          break;
        case LIGHTMODE_RAINBOW:
          //no HID as too much data transfer hinders polling
          updateLeds(false, &color_rainbow);
          break;
        case LIGHTMODE_WAVE:
          updateLeds(true, &color_wave);
          break;
        case LIGHTMODE_BREATH:
          updateLeds(true, &color_breath);
          break;
        case LIGHTMODE_FADE:
          updateLeds(true, &color_fade);
          break;
        case LIGHTMODE_VELOCITY_FADE:
          updateLeds(true, &color_velocity_fade);
          break;
        case LIGHTMODE_RAINBOW_FADE:
          updateLeds(true, &color_rainbow_fade);
          break;
      }
    }
    uint8_t* NOSTHID_::getButtonsState(){
      return buttonsState;
    }
#endif
