check_crc(int fd)
{
    int i;
    unsigned int crc1;

    sendcommand(fd, CHECK_CRC);
    crc1 = crc;
    com_putc(fd, crc1);
    com_putc(fd, crc1 >> 8);

    i = com_getc(fd, TIMEOUT);
    switch (i)
    {
        case SUCCESS:
            return 0;
        case BADCOMMAND:
            return 2;
        case FAIL:
            return 1;
        case COM_DISCONNECT:

        case COM_TIMEOUT:
            printf("check_crc: ...Device does not answer!\n\n");

        default:
            return i;
    }
}
