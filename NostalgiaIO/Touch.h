#ifndef Touch_h
#define Touch_h

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

class Touch_ {
private:
  void send(uint8_t identifier, uint8_t touch, int16_t x, int16_t y);
public:
  Touch_(void);
  void begin(void);
  void end(void);
  void moveFingerTo(uint8_t finger, int16_t x, int16_t y);
  void releaseFinger(uint8_t finger);
  void sendState(uint8_t *buttonsState);
};
extern Touch_ Touch;

#endif
#endif
