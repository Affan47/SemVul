static void uvc_disconnect(struct usb_interface *intf)
{
	struct uvc_device *dev = usb_get_intfdata(intf);


	usb_set_intfdata(intf, NULL);

	if (intf->cur_altsetting->desc.bInterfaceSubClass == SC_VIDEOSTREAMING)
		return;


	mutex_lock(&uvc_driver.open_mutex);

	dev->state |= UVC_DEV_DISCONNECTED;
	kref_put(&dev->kref, uvc_delete);

	mutex_unlock(&uvc_driver.open_mutex);
}
