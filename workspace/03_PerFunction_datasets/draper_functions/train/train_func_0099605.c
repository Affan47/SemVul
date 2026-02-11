atp_resume(struct usb_interface *iface)
{
	struct atp *dev = usb_get_intfdata(iface);

	if (dev->open && usb_submit_urb(dev->urb, GFP_ATOMIC))
		return -EIO;

	return 0;
}
