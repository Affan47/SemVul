usb_dvobj_deinit(struct usb_interface *usb_intf)
{
	struct dvobj_priv *dvobj = usb_get_intfdata(usb_intf);

	usb_set_intfdata(usb_intf, NULL);
	if (dvobj) {

		if ((dvobj->NumInterfaces != 2 &&
		    dvobj->NumInterfaces != 3) ||
		    (dvobj->InterfaceNumber == 1)) {
			if (interface_to_usbdev(usb_intf)->state !=
			    USB_STATE_NOTATTACHED) {


				pr_debug("usb attached..., try to reset usb device\n");
				usb_reset_device(interface_to_usbdev(usb_intf));
			}
		}

		kfree(dvobj->usb_vendor_req_buf);
		mutex_destroy(&dvobj->usb_vendor_req_mutex);
		kfree(dvobj);
	}

	usb_put_dev(interface_to_usbdev(usb_intf));

}
