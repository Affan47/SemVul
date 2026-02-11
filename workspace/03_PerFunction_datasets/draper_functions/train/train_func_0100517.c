init(FT_IO_NS fm_io & io)
{
    int err = 0;
    if (this_io->is_open())
        this_io = & io;
    else
        err = ENOTCONN;
    return err;
}
