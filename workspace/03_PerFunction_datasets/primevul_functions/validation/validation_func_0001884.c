static int mdhdin(int size)
{

    u32in();

    mp4config.ctime = u32in();

    mp4config.mtime = u32in();

    mp4config.samplerate = u32in();

    mp4config.samples = u32in();

    u16in();

    u16in();

    return size;
};
