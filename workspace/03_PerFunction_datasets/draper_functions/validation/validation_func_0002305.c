iconv_free(VALUE cd)
{
    if (cd && iconv_close(VALUE2ICONV(cd)) == -1)
	rb_sys_fail("iconv_close");
    return Qnil;
}
