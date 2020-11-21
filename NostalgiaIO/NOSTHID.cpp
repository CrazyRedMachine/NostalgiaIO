#include "NOSTHID.h"

/* HID DESCRIPTOR */
static const byte PROGMEM _hidReportNOST[] = {
0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
0x09, 0x05,        // Usage (Game Pad)

0xA1, 0x01,        // Collection (Application)
  0x85, 0x04,        //   Report ID (4)
    /* 30 buttons (28 keys, service, test */
  0x05, 0x09,        //   Usage Page (Button)
  0x19, 0x01,        //   Usage Minimum (0x01)
  0x29, 0x1E,        //   Usage Maximum (30)
  0x15, 0x00,        //   Logical Minimum (0)
  0x25, 0x01,        //   Logical Maximum (1)
  0x95, 0x1E,        //   Report Count (30)
  0x75, 0x01,        //   Report Size (1)
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    /* 2 bits padding */
  0x95, 0x01,        //   Report Count (1)
  0x75, 0x02,        //   Report Size (2)
  0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  
  0x85, 0x02,        //   Report ID (5)   
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
  /*
  0x85, 0x03,        //   Report ID (3)
      // 14 RGB leds (42 leds)
    0x05, 0x0a,        //     Usage Page (Buttons)
    0x19, 0x2B,        //     Usage Minimum (0x01)
    0x29, 0x54,        //     Usage Maximum (0x54)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x00,        //     Logical Maximum (255)
    0x95, 0x2A,        //     Report Count (84)
    0x75, 0x08,        //     Report Size (8)
    0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  */
    /* HID modeswitch request (no usage page etc so it's not picked up by the tools) */
  0x85, 0x06,        //   Report ID (6)
    0x95, 0x01,        //     Report Count (1)
    0x75, 0x08,        //     Report Size (9)
    0xb1, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    
0xC0  // End Collection (Gamepad)

};

/* PluggableUSBModule IMPLEMENTATION */
    NOSTHID_::NOSTHID_(void) : PluggableUSBModule(1, 1, epType) {
      epType[0] = EP_TYPE_INTERRUPT_IN;
      PluggableUSB().plug(this);
    }

    int NOSTHID_::getInterface(byte* interfaceCount) {
      *interfaceCount += 1; // uses 1
      HIDDescriptor hidInterface = {
        D_INTERFACE(pluggedInterface, 1, USB_DEVICE_CLASS_HUMAN_INTERFACE, HID_SUBCLASS_NONE, HID_PROTOCOL_NONE),
        D_HIDREPORT(sizeof(_hidReportNOST)),
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

      return USB_SendControl(TRANSFER_PGM, _hidReportNOST, sizeof(_hidReportNOST));
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
          else if (setup.wValueH == HID_REPORT_TYPE_OUTPUT && setup.wLength == 2){
            USB_RecvControl(mode_data, 2);
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

/* CUSTOM NOST FUNCTIONS */
    void NOSTHID_::init_acio(void){
      acio_open();
      delay(500);
      panb_set_auto_poll();
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
    
    void NOSTHID_::updateLightMode(){
      uint8_t* mode = (uint8_t*)&(mode_data[1]);
      if (*mode < NUM_LIGHT_MODES) {
        setLightMode(*mode);
        mode_data[1] = 0xFF;
      }
     }

    color_t NOSTHID_::color_reactive(uint8_t button)
    {
      if (buttonsState[button]) return {0,0x7F,0x23};

      return {0,0,0};
    }
    void NOSTHID_::updateLeds(bool hid, color_t (*func)(uint8_t)){
      if (hid)
        panb_set_lamp_state_batch((uint8_t*)&(led_data[1]));

      if (func != NULL)
      {
        for (int i=0; i<30; i++)
        {
          panb_set_lamp_state(i, func(i));
        }
      }
      
      panb_send_lamp();
    }
    
    int NOSTHID_::sendState(){
      uint32_t bitfield = 0;
      for(int i=0; i < 30; i++)
      {
        if (buttonsState[i]) bitfield |= (uint32_t)((uint32_t)1<<i);
      }
      /* finally, send HID report */
      uint8_t data[5];
      data[0] = (uint8_t) 4; //report id
      data[1] = (uint8_t) (bitfield & 0xFF);
      data[2] = (uint8_t) (bitfield >> 8) & 0xFF;
      data[3] = (uint8_t) (bitfield >> 16) & 0xFF;
      data[4] = (uint8_t) (bitfield >> 24) & 0xFF;
      return USB_Send(pluggedEndpoint | TRANSFER_RELEASE, data, 5);
    }
