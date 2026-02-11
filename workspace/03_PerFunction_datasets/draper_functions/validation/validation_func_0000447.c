exit_success_p(exc)
    VALUE exc;
{
    VALUE status = rb_attr_get(exc, rb_intern("status"));
    if (NIL_P(status)) return Qtrue;
    if (status == INT2FIX(EXIT_SUCCESS)) return Qtrue;
    return Qfalse;
}
