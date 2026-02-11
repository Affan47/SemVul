console_set_echo(VALUE io, VALUE f)
{
    conmode t;
    rb_io_t *fptr;
    int fd;

    GetOpenFile(io, fptr);
    fd = GetReadFD(fptr);
    if (!getattr(fd, &t)) rb_sys_fail(0);
    if (RTEST(f))
	set_echo(&t, NULL);
    else
	set_noecho(&t, NULL);
    if (!setattr(fd, &t)) rb_sys_fail(0);
    return io;
}
