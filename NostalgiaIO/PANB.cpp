#include "PANB.h"

static byte lamp_state[0x54];

void panb_set_lamp_state(uint8_t key, color_t color, bool mix)
{
  if (key < 28){
    if (!mix)
    {
      lamp_state[3*key] = 0;
      lamp_state[3*key+1] = 0;
      lamp_state[3*key+2] = 0;
    }
    lamp_state[3*key] |= color.red;
    lamp_state[3*key+1] |= color.green;
    lamp_state[3*key+2] |= color.blue;
  }
}

void panb_set_lamp_state_batch(uint8_t source[])
{
  if (source == NULL)
  {
    memset(lamp_state, 0, 0x54);
  }
  else
  memcpy(lamp_state, source, 0x54);
}

bool panb_send_lamp()
{
    struct ac_io_message msg;

    msg.addr = 01;
    msg.cmd.code = ac_io_u16(AC_IO_CMD_PANB_LAMP);
    msg.cmd.nbytes = 0x54;
    memcpy(&msg.cmd.raw, lamp_state, 0x54);

    msg.cmd.seq_no = acio_get_counter_and_increase();
    int send_size = offsetof(struct ac_io_message, cmd.raw) + msg.cmd.nbytes;

    if (acio_send((uint8_t *) &msg, send_size) <= 0) {
      #ifdef ACIO_DEBUG
        Serial.print("panb_send_lamp failed");
      #endif
        return false;
    }

    return true;
}

bool panb_set_auto_input()
{
    struct ac_io_message msg;

    msg.addr = 01;
    msg.cmd.code = ac_io_u16(AC_IO_CMD_PANB_AUTO_INPUT);
    msg.cmd.nbytes = 0x01;
    msg.cmd.count = 4;

    msg.cmd.seq_no = acio_get_counter_and_increase();
    int send_size = offsetof(struct ac_io_message, cmd.raw) + msg.cmd.nbytes;

    if (acio_send((uint8_t *) &msg, send_size) <= 0) {
      #ifdef ACIO_DEBUG
        Serial.print("panb_set_auto_poll failed");
      #endif
        return false;
    }

    return true;
}

