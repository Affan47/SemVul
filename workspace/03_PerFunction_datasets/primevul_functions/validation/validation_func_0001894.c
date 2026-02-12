static int mp4ain(int size)
{

    u32in();
    u16in();

    u16in();

    u16in();

    u16in();

    u32in();

    mp4config.channels = u16in();

    mp4config.bits = u16in();

    u16in();

    u16in();


    u16in();

    u16in();

    return size;
}
