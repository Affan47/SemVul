static void cd_data_to_raw(uint8_t *buf, int lba)
{

    buf[0] = 0x00;
    memset(buf + 1, 0xff, 10);
    buf[11] = 0x00;
    buf += 12;

    lba_to_msf(buf, lba);
    buf[3] = 0x01;
    buf += 4;

    buf += 2048;

    memset(buf, 0, 288);
}
