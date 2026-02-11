rb_io_sysread(int argc, VALUE *argv, VALUE io)
{
    VALUE len, str;
    rb_io_t *fptr;
    long n, ilen;
    struct read_internal_arg arg;

    rb_scan_args(argc, argv, "11", &len, &str);
    ilen = NUM2LONG(len);

    io_setstrbuf(&str,ilen);
    if (ilen == 0) return str;

    GetOpenFile(io, fptr);
    rb_io_check_byte_readable(fptr);

    if (READ_DATA_BUFFERED(fptr)) {
	rb_raise(rb_eIOError, "sysread for buffered IO");
    }

    n = fptr->fd;
    rb_thread_wait_fd(fptr->fd);
    rb_io_check_closed(fptr);

    rb_str_locktmp(str);
    arg.fd = fptr->fd;
    arg.str_ptr = RSTRING_PTR(str);
    arg.len = ilen;
    rb_ensure(read_internal_call, (VALUE)&arg, rb_str_unlocktmp, str);
    n = arg.len;

    if (n == -1) {
	rb_sys_fail_path(fptr->pathv);
    }
    rb_str_set_len(str, n);
    if (n == 0 && ilen > 0) {
	rb_eof_error();
    }
    rb_str_resize(str, n);
    OBJ_TAINT(str);

    return str;
}
