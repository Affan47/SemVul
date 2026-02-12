static void cmd_inquiry(IDEState *s, uint8_t *buf)
{
    uint8_t page_code = buf[2];
    int max_len = buf[4];

    unsigned idx = 0;
    unsigned size_idx;
    unsigned preamble_len;


    if (buf[1] & 0x01) {
        preamble_len = 4;
        size_idx = 3;

        buf[idx++] = 0x05;
        buf[idx++] = page_code;
        buf[idx++] = 0x00;
        idx++;

        switch (page_code) {
        case 0x00:

            buf[idx++] = 0x00;
            buf[idx++] = 0x83;
            break;

        case 0x83:


            if (idx + 24 > max_len) {


                ide_atapi_cmd_error(s, ILLEGAL_REQUEST,
                                    ASC_DATA_PHASE_ERROR);
                return;
            }
            buf[idx++] = 0x02;
            buf[idx++] = 0x00;
            buf[idx++] = 0x00;
            buf[idx++] = 20;
            padstr8(buf + idx, 20, s->drive_serial_str);
            idx += 20;


            if (idx + 72 > max_len) {

                goto out;
            }
            buf[idx++] = 0x02;
            buf[idx++] = 0x01;
            buf[idx++] = 0x00;
            buf[idx++] = 68;
            padstr8(buf + idx, 8, "ATA");
            idx += 8;
            padstr8(buf + idx, 40, s->drive_model_str);
            idx += 40;
            padstr8(buf + idx, 20, s->drive_serial_str);
            idx += 20;


            if (s->wwn && (idx + 12 <= max_len)) {

                buf[idx++] = 0x01;
                buf[idx++] = 0x03;
                buf[idx++] = 0x00;
                buf[idx++] = 0x08;
                stq_be_p(&buf[idx], s->wwn);
                idx += 8;
            }
            break;

        default:

            ide_atapi_cmd_error(s, ILLEGAL_REQUEST,
                                ASC_INV_FIELD_IN_CMD_PACKET);
            return;
        }
    } else {
        preamble_len = 5;
        size_idx = 4;

        buf[0] = 0x05;
        buf[1] = 0x80;
        buf[2] = 0x00;
        buf[3] = 0x21;

        buf[5] = 0;
        buf[6] = 0;
        buf[7] = 0;
        padstr8(buf + 8, 8, "QEMU");
        padstr8(buf + 16, 16, "QEMU DVD-ROM");
        padstr8(buf + 32, 4, s->version);
        idx = 36;
    }

 out:
    buf[size_idx] = idx - preamble_len;
    ide_atapi_cmd_reply(s, idx, max_len);
}
