static int hdlr1in(int size)
{
    uint8_t buf[5];

    buf[4] = 0;

    u32in();

    u32in();

    datain(buf, 4);
    if (mp4config.verbose.header)
        fprintf(stderr, "*track media type: '%s': ", buf);
    if (memcmp("soun", buf, 4))
    {
        if (mp4config.verbose.header)
            fprintf(stderr, "unsupported, skipping\n");
        return ERR_UNSUPPORTED;
    }
    else
    {
        if (mp4config.verbose.header)
            fprintf(stderr, "OK\n");
    }

    u32in();
    u32in();
    u32in();


    u8in();

    return size;
};
