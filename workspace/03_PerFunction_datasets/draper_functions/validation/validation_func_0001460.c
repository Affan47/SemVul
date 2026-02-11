strio_close_read(VALUE self)
{
    struct StringIO *ptr = StringIO(self);
    if (!READABLE(ptr)) {
	rb_raise(rb_eIOError, "closing non-duplex IO for reading");
    }
    ptr->flags &= ~FMODE_READABLE;
    return Qnil;
}
