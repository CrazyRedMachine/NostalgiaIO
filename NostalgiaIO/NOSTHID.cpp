#include "NOSTHID.h"

#if defined(_USING_HID)

static const uint8_t _hidReportDescriptorLights[] PROGMEM = {
  0x05, 0x01,                    // USAGE_PAGE(General Desktop)
  0x09, 0x00,                    // USAGE     (Undefined)
  0xA1, 0x01,                    // COLLECTION(Application)
  
  0x85, 0x01,        //   Report ID (1)
    /* 1 button just so it has an input */
    0x05, 0x09,        //   Usage Page (Button)
    0x19, 0x01,        //   Usage Minimum (0x01)
    0x29, 0x01,        //   Usage Maximum (0x09)
    0x15, 0x00,        //   Logical Minimum (0)
    0x25, 0x01,        //   Logical Maximum (1)
    0x95, 0x01,        //   Report Count (9)
    0x75, 0x01,        //   Report Size (1)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    /* 7 bits padding */
    0x95, 0x01,        //   Report Count (1)
    0x75, 0x07,        //   Report Size (7)
    0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position) 
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
};

uint8_t *_hidReportDescriptor;
uint16_t _hidReportDescriptorSize;

NOSTHID_::NOSTHID_(void) : PluggableUSBModule(1, 1, epType) {
   epType[0] = EP_TYPE_INTERRUPT_IN;

    _hidReportDescriptor = _hidReportDescriptorLights;
    _hidReportDescriptorSize = sizeof(_hidReportDescriptorLights);

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
}

void NOSTHID_::end(void) {
}

int NOSTHID_::send(uint8_t identifier) {

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
        case LIGHTMODE_FADE:
          updateLeds(true, &color_fade);
          break;
        case LIGHTMODE_VELOCITY_FADE:
          updateLeds(true, &color_velocity_fade);
          break;
      }
    }
    uint8_t* NOSTHID_::getButtonsState(){
      return buttonsState;
    }
#endif
