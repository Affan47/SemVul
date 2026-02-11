eem_disable(struct usb_function *f)
{
	struct f_eem		*eem = func_to_eem(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	DBG(cdev, "eem deactivated\n");

	if (eem->port.in_ep->enabled)
		gether_disconnect(&eem->port);
}
