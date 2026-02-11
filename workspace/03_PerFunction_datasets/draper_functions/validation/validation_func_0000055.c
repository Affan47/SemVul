rb_dlptr_cmp(VALUE self, VALUE other)
{
    void *ptr1, *ptr2;
    SIGNED_VALUE diff;

    if(!rb_obj_is_kind_of(other, rb_cDLCPtr)) return Qnil;

    ptr1 = rb_dlptr2cptr(self);
    ptr2 = rb_dlptr2cptr(other);
    diff = (SIGNED_VALUE)ptr1 - (SIGNED_VALUE)ptr2;
    if (!diff) return INT2FIX(0);
    return diff > 0 ? INT2NUM(1) : INT2NUM(-1);
}
