rb_gzreader_each(int argc, VALUE *argv, VALUE obj)
{
    VALUE str;

    RETURN_ENUMERATOR(obj, 0, 0);

    while (!NIL_P(str = gzreader_gets(argc, argv, obj))) {
	rb_yield(str);
    }
    return obj;
}
