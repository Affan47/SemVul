usb_put_function(struct usb_function *f)
{
	if (!f)
		return;

	f->free_func(f);
}
