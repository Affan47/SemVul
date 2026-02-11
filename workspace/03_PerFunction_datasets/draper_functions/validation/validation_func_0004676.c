inspect_ary(VALUE ary, VALUE dummy, int recur)
{
    int tainted = OBJ_TAINTED(ary);
    int untrust = OBJ_UNTRUSTED(ary);
    long i;
    VALUE s, str;

    if (recur) return rb_usascii_str_new_cstr("[...]");
    str = rb_str_buf_new2("[");
    for (i=0; i<RARRAY_LEN(ary); i++) {
	s = rb_inspect(RARRAY_PTR(ary)[i]);
	if (OBJ_TAINTED(s)) tainted = TRUE;
	if (OBJ_UNTRUSTED(s)) untrust = TRUE;
	if (i > 0) rb_str_buf_cat2(str, ", ");
	else rb_enc_copy(str, s);
	rb_str_buf_append(str, s);
    }
    rb_str_buf_cat2(str, "]");
    if (tainted) OBJ_TAINT(str);
    if (untrust) OBJ_UNTRUST(str);
    return str;
}
