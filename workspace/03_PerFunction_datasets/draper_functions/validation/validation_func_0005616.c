rb_file_s_lstat(VALUE klass, VALUE fname)
{
#ifdef HAVE_LSTAT
    struct stat st;

    rb_secure(2);
    FilePathValue(fname);
    fname = rb_str_encode_ospath(fname);
    if (lstat(StringValueCStr(fname), &st) == -1) {
	rb_sys_fail_path(fname);
    }
    return stat_new(&st);
#else
    return rb_file_s_stat(klass, fname);
#endif
}
