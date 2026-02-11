rb_io_check_closed(fptr)
    OpenFile *fptr;
{
    rb_io_check_initialized(fptr);
    if (!fptr->f && !fptr->f2) {
	rb_raise(rb_eIOError, "closed stream");
    }
}
