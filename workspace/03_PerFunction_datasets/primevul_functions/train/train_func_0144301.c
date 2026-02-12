static void cmd_read_disc_information(IDEState *s, uint8_t* buf)
{
    uint8_t type = buf[1] & 7;
    uint32_t max_len = ube16_to_cpu(buf + 7);


    if (type != 0) {
        ide_atapi_cmd_error(s, ILLEGAL_REQUEST,
                            ASC_INV_FIELD_IN_CMD_PACKET);
        return;
    }

    memset(buf, 0, 34);
    buf[1] = 32;
    buf[2] = 0xe;
    buf[3] = 1;
    buf[4] = 1;
    buf[5] = 1;
    buf[6] = 1;
    buf[7] = 0x20;
    buf[8] = 0x00;


    ide_atapi_cmd_reply(s, 34, max_len);
}
