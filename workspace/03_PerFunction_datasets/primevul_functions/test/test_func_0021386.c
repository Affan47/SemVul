void composite_reset(struct usb_gadget *gadget)
{


	usb_gadget_vbus_draw(gadget, 100);
	__composite_disconnect(gadget);
}
