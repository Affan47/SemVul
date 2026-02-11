xusbatm_capture_intf(struct usbatm_data *usbatm, struct usb_device *usb_dev,
		struct usb_interface *intf, int altsetting, int claim)
{
	int ifnum = intf->altsetting->desc.bInterfaceNumber;
	int ret;

	if (claim && (ret = usb_driver_claim_interface(&xusbatm_usb_driver, intf, usbatm))) {
		usb_err(usbatm, "%s: failed to claim interface %2d (%d)!\n", __func__, ifnum, ret);
		return ret;
	}
	ret = usb_set_interface(usb_dev, ifnum, altsetting);
	if (ret) {
		usb_err(usbatm, "%s: altsetting %2d for interface %2d failed (%d)!\n", __func__, altsetting, ifnum, ret);
		return ret;
	}
	return 0;
}
