#include "ACIO.h"

#define ac_io_u16(x) __builtin_bswap16(x)
#define ac_io_u32(x) __builtin_bswap32(x)

static uint8_t acio_msg_counter = 1;
static uint8_t acio_node_count;
static char acio_node_products[16][4];

static bool acio_send(const uint8_t *buffer, int length)
{
    uint8_t send_buf[512];
    int send_buf_pos = 0;
    uint8_t checksum = 0;

    if (length > sizeof(send_buf)) {
        Serial.println("Send buffer overflow");
        return false;
    }

    send_buf[send_buf_pos++] = AC_IO_SOF;

    for (int i = 0; i < length; i++) {
        if (buffer[i] == AC_IO_SOF || buffer[i] == AC_IO_ESCAPE) {
            send_buf[send_buf_pos++] = AC_IO_ESCAPE;
            send_buf[send_buf_pos++] = ~buffer[i];
        } else {
            send_buf[send_buf_pos++] = buffer[i];
        }

        checksum += buffer[i];
    }

    if (checksum == AC_IO_SOF || checksum == AC_IO_ESCAPE) {
        send_buf[send_buf_pos++] = AC_IO_ESCAPE;
        send_buf[send_buf_pos++] = ~checksum;
    } else {
        send_buf[send_buf_pos++] = checksum;
    }

    if (Serial1.write(send_buf, send_buf_pos) != send_buf_pos) {
        Serial.println("Sending data failed");
        return false;
    }

    return true;
}

static int acio_receive(uint8_t *buffer, int size)
{
    uint8_t recv_buf[512];
    int recv_size = 0;
    int read = 0;
    uint8_t checksum = 0;
    int result_size = 0;

    /* reading a byte stream, we are getting a varying amount
       of 0xAAs before we get a valid message. */
    recv_buf[0] = AC_IO_SOF;
    do {
        read = Serial1.readBytes(recv_buf, 1);
    } while (recv_buf[0] == AC_IO_SOF);

    if (read > 0) {
        size += 1;

        /* recv_buf[0] is already the first byte of the message.
           now read until nothing's left */
        recv_size++;
        size--;

        /* important: we have to know how much data we expect
           and have to read until we reach the requested amount.
           Because this can be interrupted by 0 reads and we
           need to handle escaping (which relies on an up to
           date recv_buf[recv_size]) we loop until we get a
           non-zero read. */
        while (size > 0) {
            do {
                read = Serial1.readBytes(recv_buf + recv_size, 1);
            } while (read == 0);

            if (read < 0) {
                break;
            }

            /* check for escape byte. these don't count towards the
               size we expect! */
            if (recv_buf[recv_size] == AC_IO_ESCAPE) {
                /* next byte is our real data
                   overwrite escape byte */
                do {
                    read = Serial1.readBytes(recv_buf + recv_size, 1);
                } while (read == 0);

                if (read < 0) {
                    break;
                }

                recv_buf[recv_size] = ~recv_buf[recv_size];
            }

            recv_size += read;
            size -= read;
        }

        /* recv_size - 1: omit checksum for checksum calc */
        for (int i = 0; i < recv_size - 1; i++) {
            checksum += recv_buf[i];
            buffer[i] = recv_buf[i];
        }

        result_size = recv_size - 1;

        if (checksum != recv_buf[recv_size - 1]) {
            Serial.println("Invalid message checksum: ");
            Serial.print(checksum, HEX);
            Serial.print(" != ");
            Serial.print(recv_buf[recv_size - 1], HEX);
            Serial.println();
            return -1;
        }

        return result_size;
    }

    return -1;
}

bool acio_send_and_recv(struct ac_io_message *msg, int resp_size)
{
    msg->cmd.seq_no = acio_msg_counter++;
    int send_size = offsetof(struct ac_io_message, cmd.raw) + msg->cmd.nbytes;

    if (acio_send((uint8_t *) msg, send_size) <= 0) {
        return false;
    }

    uint16_t req_code = msg->cmd.code;

    if (acio_receive((uint8_t *) msg, resp_size) <= 0) {
        return false;
    }

    if (req_code != msg->cmd.code) {
        Serial.print("Received invalid response ");
        Serial.print(msg->cmd.code, HEX);
        Serial.print(" for request ");
        Serial.print(req_code, HEX);
        Serial.println();
        return false;
    }

    return true;
}

static void acio_init(void)
{
    Serial.println("INIT DEVICE");
    uint8_t read_buff = 0x00;

    /* init/reset the device by sending 0xAA until 0xAA is returned */
    int read = 0;
    do {
        Serial1.write(AC_IO_SOF);
//        Serial.println("Sent : 0xAA");
        
        read_buff = Serial1.read();
//        Serial.print("Recv : 0x");
//        Serial.print(read_buff, HEX);
//        Serial.println();
    } while ((read_buff != AC_IO_SOF));
    
        Serial.println("Obtained SOF, clearing out buffer now");

    while (Serial1.available()) {
        Serial1.read();
    }
    Serial.println("Buffer cleared");
}


static uint8_t acio_enum_nodes(void)
{
    struct ac_io_message msg;

    msg.addr = 0x00;
    msg.cmd.code = ac_io_u16(AC_IO_CMD_ASSIGN_ADDRS);
    msg.cmd.nbytes = 1;
    msg.cmd.count = 0;

    if (!acio_send_and_recv(
            &msg, offsetof(struct ac_io_message, cmd.raw) + 1)) {
        printf("Enumerating nodes failed\n");
        return 0;
    }
    return msg.cmd.count;
}

static bool acio_get_version(uint8_t node_id, char product[4])
{
    struct ac_io_message msg;

    msg.addr = node_id;
    msg.cmd.code = ac_io_u16(AC_IO_CMD_GET_VERSION);
    msg.cmd.nbytes = 0;

    if (!acio_send_and_recv(
            &msg,
            offsetof(struct ac_io_message, cmd.raw) +
                sizeof(struct ac_io_version))) {
        printf("Get version of node %d failed\n", node_id);
        return false;
    }

    Serial.print("Node ");
    Serial.print(node_id,DEC);
    Serial.print(": type ");
    Serial.print(msg.cmd.version.type,DEC);
    Serial.print(", flag ");
    Serial.print(msg.cmd.version.flag);
    Serial.print(", version ");
    Serial.print(msg.cmd.version.major);
    Serial.print(".");
    Serial.print(msg.cmd.version.minor);
    Serial.print(".");
    Serial.print(msg.cmd.version.revision);
    Serial.print(", product ");
    Serial.print(msg.cmd.version.product_code[0]);
    Serial.print(msg.cmd.version.product_code[1]);
    Serial.print(msg.cmd.version.product_code[2]);
    Serial.print(msg.cmd.version.product_code[3]);
    Serial.print(", build date: ");
    Serial.print(msg.cmd.version.date);
    Serial.print(" ");
    Serial.println(msg.cmd.version.time);
    
    memcpy(product, msg.cmd.version.product_code, 4);    

    return true;
}

static bool acio_start_node(uint8_t node_id)
{
    struct ac_io_message msg;

    msg.addr = node_id;
    msg.cmd.code = ac_io_u16(AC_IO_CMD_START_UP);
    msg.cmd.nbytes = 0;

    if (!acio_send_and_recv(
            &msg, offsetof(struct ac_io_message, cmd.raw) + 1)) {
        printf("Starting node %d failed\n", node_id);
        return false;
    }

    printf("Started node %d, status: %d\n", node_id, msg.cmd.status);
    return true;
}

bool acio_open()
{
    acio_init();
    acio_node_count = acio_enum_nodes();
    if (acio_node_count == 0) {
        return false;
    }

    for (uint8_t i = 0; i < acio_node_count; i++) {
        if (!acio_get_version(
                i + 1, acio_node_products[i])) {
            return false;
        }
    }

    for (uint8_t i = 0; i < acio_node_count; i++) {
        if (!acio_start_node(i + 1)) {
            return false;
        }
    }

    return true;
}
