rb_io_s_sysopen(argc, argv)
    int argc;
    VALUE *argv;
{
    VALUE fname, vmode, perm;
    int flags, fmode, fd;
    char *path;

    rb_scan_args(argc, argv, "12", &fname, &vmode, &perm);
    SafeStringValue(fname);

    if (NIL_P(vmode)) flags = O_RDONLY;
    else if (FIXNUM_P(vmode)) flags = FIX2INT(vmode);
    else {
	SafeStringValue(vmode);
	flags = rb_io_mode_modenum(RSTRING(vmode)->ptr);
    }
    if (NIL_P(perm)) fmode = 0666;
    else             fmode = NUM2INT(perm);

    path = ALLOCA_N(char, strlen(RSTRING(fname)->ptr)+1);
    strcpy(path, RSTRING(fname)->ptr);
    fd = rb_sysopen(path, flags, fmode);
    return INT2NUM(fd);
}
