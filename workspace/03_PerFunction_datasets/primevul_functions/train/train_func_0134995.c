static void cmd_get_configuration(IDEState *s, uint8_t *buf)
{
    uint32_t len;
    uint8_t index = 0;
    int max_len;


    if (buf[2] != 0 || buf[3] != 0) {
        ide_atapi_cmd_error(s, ILLEGAL_REQUEST,
                            ASC_INV_FIELD_IN_CMD_PACKET);
        return;
    }


    max_len = lduw_be_p(buf + 7);


    if (max_len > BDRV_SECTOR_SIZE) {

        max_len = BDRV_SECTOR_SIZE;
    }

    memset(buf, 0, max_len);


    if (media_is_dvd(s)) {
        stw_be_p(buf + 6, MMC_PROFILE_DVD_ROM);
    } else if (media_is_cd(s)) {
        stw_be_p(buf + 6, MMC_PROFILE_CD_ROM);
    }

    buf[10] = 0x02 | 0x01;
    len = 12;
    len += ide_atapi_set_profile(buf, &index, MMC_PROFILE_DVD_ROM);
    len += ide_atapi_set_profile(buf, &index, MMC_PROFILE_CD_ROM);
    stl_be_p(buf, len - 4);

    ide_atapi_cmd_reply(s, len, max_len);
}
