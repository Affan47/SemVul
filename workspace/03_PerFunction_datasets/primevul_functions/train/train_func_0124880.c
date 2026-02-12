static int scsi_read_disc_information(SCSIDiskState *s, SCSIDiskReq *r,
                                      uint8_t *outbuf)
{
    uint8_t type = r->req.cmd.buf[1] & 7;

    if (s->qdev.type != TYPE_ROM) {
        return -1;
    }


    if (type != 0) {
        scsi_check_condition(r, SENSE_CODE(INVALID_FIELD));
        return -1;
    }

    memset(outbuf, 0, 34);
    outbuf[1] = 32;
    outbuf[2] = 0xe;
    outbuf[3] = 1;
    outbuf[4] = 1;
    outbuf[5] = 1;
    outbuf[6] = 1;
    outbuf[7] = 0x20;
    outbuf[8] = 0x00;


    return 34;
}
