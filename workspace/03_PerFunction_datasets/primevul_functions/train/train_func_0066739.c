static int cdc_ncm_bind(struct usbnet *dev, struct usb_interface *intf)
 {

 	if (cdc_ncm_select_altsetting(intf) != CDC_NCM_COMM_ALTSETTING_NCM)
 		return -ENODEV;


	return cdc_ncm_bind_common(dev, intf, CDC_NCM_DATA_ALTSETTING_NCM, 0);
 }
