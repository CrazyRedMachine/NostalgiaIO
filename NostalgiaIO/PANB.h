#ifndef panb_h
#define panb_h
#include "ACIO.h"

typedef struct color_s {
  byte red;
  byte green;
  byte blue;
} color_t;

enum panb_cmd {
    AC_IO_CMD_PANB_LAMP = 0x0111,
    AC_IO_CMD_PANB_AUTO_INPUT = 0x0115,
};

typedef struct panb_button_state_s {
    uint8_t addr; /* always 0x81 */
    uint16_t code; /* always 0x0110 */
    uint8_t seq_no; /* seq_number at time of set_auto_input */
    uint8_t nbytes; /* always 0x10 */
    uint8_t sub_seq1; /* last recv command seq number */
    uint8_t sub_seq2; /* polling internal seq number */
    
    uint8_t keypair[14];
} panb_button_state_t;

void panb_set_lamp_state_batch(uint8_t source[]);
void panb_set_lamp_state(uint8_t key, color_t color, bool mix);
bool panb_send_lamp();
bool panb_set_auto_input();

#endif
