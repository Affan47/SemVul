static int scsi_get_configuration(SCSIDiskState *s, uint8_t *outbuf)
{
    int current;

    if (s->qdev.type != TYPE_ROM) {
        return -1;
    }

    if (media_is_dvd(s)) {
        current = MMC_PROFILE_DVD_ROM;
    } else if (media_is_cd(s)) {
        current = MMC_PROFILE_CD_ROM;
    } else {
        current = MMC_PROFILE_NONE;
    }

    memset(outbuf, 0, 40);
    stl_be_p(&outbuf[0], 36);
    stw_be_p(&outbuf[6], current);

    outbuf[10] = 0x03;
    outbuf[11] = 8;
    stw_be_p(&outbuf[12], MMC_PROFILE_DVD_ROM);
    outbuf[14] = (current == MMC_PROFILE_DVD_ROM);
    stw_be_p(&outbuf[16], MMC_PROFILE_CD_ROM);
    outbuf[18] = (current == MMC_PROFILE_CD_ROM);

    stw_be_p(&outbuf[20], 1);
    outbuf[22] = 0x08 | 0x03;
    outbuf[23] = 8;
    stl_be_p(&outbuf[24], 1);
    outbuf[28] = 1;

    stw_be_p(&outbuf[32], 3);
    outbuf[34] = 0x08 | 0x03;
    outbuf[35] = 4;
    outbuf[36] = 0x39;


    return 40;
}
