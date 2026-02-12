int set_final_ip(unsigned char *buf, unsigned char *mymac)
{
    if(buf == NULL)
        return -1;


    buf[0] = 0x06;
    buf[1] = 0x04;
    buf[2] = 0x00;
    buf[3] = 0x01;
    memcpy(buf+4, mymac, 6);
    buf[10] = 0xA9;
    buf[11] = 0xFE;

    return 0;
}
