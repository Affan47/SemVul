hex2triplet(hex)
    VALUE hex;
{
    VALUE rstr, gstr, bstr;
    VALUE ret_ary;

    Check_Type(hex, T_STRING);

    if (RSTRING_LEN(hex) != 7)
        rb_raise(rb_eArgError, "Invalid format: %s", RSTRING_PTR(hex));

    rstr = rb_str_new(RSTRING_PTR(hex) + 1, 2);
    gstr = rb_str_new(RSTRING_PTR(hex) + 3, 2);
    bstr = rb_str_new(RSTRING_PTR(hex) + 5, 2);

    ret_ary = rb_ary_new();

    rb_ary_push(ret_ary, rb_funcall(rstr, rb_intern("hex"), 0));
    rb_ary_push(ret_ary, rb_funcall(gstr, rb_intern("hex"), 0));
    rb_ary_push(ret_ary, rb_funcall(bstr, rb_intern("hex"), 0));

    return ret_ary;
}
