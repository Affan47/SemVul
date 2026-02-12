static int hdlr2in(int size)
{
    uint8_t buf[4];


    u32in();

    u32in();

    datain(buf, 4);
    if (memcmp(buf, "mdir", 4))
        return ERR_FAIL;
    datain(buf, 4);
    if (memcmp(buf, "appl", 4))
        return ERR_FAIL;

    u32in();
    u32in();

    u8in();

    return size;
};
