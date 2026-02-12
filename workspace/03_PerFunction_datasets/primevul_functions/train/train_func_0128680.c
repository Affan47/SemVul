int set_final_arp(unsigned char *buf, unsigned char *mymac)
{
    if(buf == NULL)
        return -1;


    buf[0] = 0x08;
    buf[1] = 0x00;
    buf[2] = 0x06;
    buf[3] = 0x04;
    buf[4] = 0x00;
    buf[5] = 0x01;
    memcpy(buf+6, mymac, 6);
    buf[12] = 0xA9;
    buf[13] = 0xFE;
    buf[14] = 0x57;
    buf[15] = 0xC5;

    return 0;
}
