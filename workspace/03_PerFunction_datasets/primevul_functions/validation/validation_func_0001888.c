static int esdsin(int size)
{


    enum
    { TAG_ES = 3, TAG_DC = 4, TAG_DSI = 5, TAG_SLC = 6 };


    u32in();
    if (u8in() != TAG_ES)
        return ERR_FAIL;
    getsize();

    u16in();

    u8in();

    if (u8in() != TAG_DC)
        return ERR_FAIL;
    getsize();
    if (u8in() != 0x40)
        return ERR_FAIL;

    u8in();

    mp4config.buffersize = u16in() << 8;
    mp4config.buffersize |= u8in();

    mp4config.bitratemax = u32in();
    mp4config.bitrateavg = u32in();

    if (u8in() != TAG_DSI)
        return ERR_FAIL;
    mp4config.asc.size = getsize();
    if (mp4config.asc.size > sizeof(mp4config.asc.buf))
        return ERR_FAIL;

    datain(mp4config.asc.buf, mp4config.asc.size);

    if (u8in() != TAG_SLC)
        return ERR_FAIL;
    getsize();

    u8in();

    return size;
}
