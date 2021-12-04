#ifndef NOSTHID_h
#define NOSTHID_h
#define EPTYPE_DESCRIPTOR_SIZE    uint8_t
#include "HID.h"
#include "PANB.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

enum lightmode_e {
  LIGHTMODE_HID,
  LIGHTMODE_COMBINED,
  LIGHTMODE_INVERT,
  LIGHTMODE_FADE,
  LIGHTMODE_VELOCITY_FADE,
  NUM_LIGHT_MODES,
};
//#define DEBUG

#ifdef DEBUG
  #define DEBUG_INIT() Serial.begin(115200)
  #define DEBUG_VAR(x) Serial.print(#x " = "); Serial.println(x)
#else
  #define DEBUG_INIT() 
  #define DEBUG_VAR(x) 
#endif

extern uint8_t buttonsState[31];

static color_t palette_color[3][3] = {
  {{0x7F,0x23,0},{0,0x7F,0x23},{0x23,0,0x7F}},
  {{0x7F,0xFF,0},{0,0x7F,0xFF},{0xFF,0,0x7F}},
  {{0xFF,0,0},{0,0xFF,0},{0,0,0xFF}},
};
static uint8_t palette = 2;

#define COLOR_OFF {0,0,0}
#define PALETTE_COLOR_1 palette_color[palette][0]
#define PALETTE_COLOR_2 palette_color[palette][1]
#define PALETTE_COLOR_3 palette_color[palette][2]
#define NUM_PALETTE 3

class NOSTHID_ : public PluggableUSBModule {
private:
  int send(uint8_t identifier);
public:
  NOSTHID_(void);
  void begin(void);
  void end(void);
  
    void init_acio(void);

    void poll();
    /**
     * Updates the led status based on led_data (HID report received) and/or button states
     * param[in] buttonState bitfield with currently pressed buttons (used to force additional lights for mixed mode)
     * param[in] invert set to true to invert on/off status (used for invert lightmode)
     * param[in] knobs set to true to use knob activity for color shift
     * param[in] hid set to true to use hid led_data 
     */
    void updateLeds(bool hid, color_t (*func)(uint8_t));
    void updateLeds();

    /**
     * Changes the lightMode if a received HID report asks for it
     */
    void updateLightMode();
    
    /**
     * getter and setter for lightMode protected field.
     */
    uint8_t getLightMode();
    void setLightMode(uint8_t mode);
    uint8_t getPalette();
    void setPalette(uint8_t pal);
    
    /**
     * getter for lastHidUpdate protected field.
     */
    unsigned long getLastHidUpdate();
    
    static uint8_t* getButtonsState();
    
protected:
    /* current lightMode (0 = reactive, 1 = HID only, 2 = mixed (HID+reactive auto-switch), 3 = combined (HID+button presses), 4 = combined invert) */
    uint8_t lightMode = 2;
    
    /* timestamp of last received HID report for lightMode 3 */
    unsigned long lastHidUpdate = 0;
    /* byte array to receive HID reports from the PC */
    byte led_data[85];
    byte mode_data[3];
    
    /* Implementation of the PUSBListNode */
    EPTYPE_DESCRIPTOR_SIZE epType[1];
    uint8_t protocol;
    uint8_t idle;    
    int getInterface(uint8_t* interfaceCount);
    int getDescriptor(USBSetup& setup);
    bool setup(USBSetup& setup);
    uint8_t getShortName(char *name);
};
extern NOSTHID_ NOSTHID;

#endif
#endif
