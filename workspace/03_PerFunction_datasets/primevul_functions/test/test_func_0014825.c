static void em28xx_check_usb_descriptor(struct em28xx *dev,
					struct usb_device *udev,
					struct usb_interface *intf,
					int alt, int ep,
					bool *has_vendor_audio,
					bool *has_video,
					bool *has_dvb)
{
	const struct usb_endpoint_descriptor *e;
	int sizedescr, size;


	e = &intf->altsetting[alt].endpoint[ep].desc;

	if (!usb_endpoint_dir_in(e))
		return;

	sizedescr = le16_to_cpu(e->wMaxPacketSize);
	size = sizedescr & 0x7ff;

	if (udev->speed == USB_SPEED_HIGH)
		size = size * hb_mult(sizedescr);


	switch (e->bEndpointAddress) {
	case 0x82:
		*has_video = true;
		if (usb_endpoint_xfer_isoc(e)) {
			dev->analog_ep_isoc = e->bEndpointAddress;
			dev->alt_max_pkt_size_isoc[alt] = size;
		} else if (usb_endpoint_xfer_bulk(e)) {
			dev->analog_ep_bulk = e->bEndpointAddress;
		}
		return;
	case 0x83:
		if (usb_endpoint_xfer_isoc(e))
			*has_vendor_audio = true;
		else
			dev_err(&intf->dev,
				"error: skipping audio endpoint 0x83, because it uses bulk transfers !\n");
		return;
	case 0x84:
		if (*has_video && (usb_endpoint_xfer_bulk(e))) {
			dev->analog_ep_bulk = e->bEndpointAddress;
		} else {
			if (usb_endpoint_xfer_isoc(e)) {
				if (size > dev->dvb_max_pkt_size_isoc) {


					*has_dvb = true;
					dev->dvb_ep_isoc = e->bEndpointAddress;
					dev->dvb_max_pkt_size_isoc = size;
					dev->dvb_alt_isoc = alt;
				}
			} else {
				*has_dvb = true;
				dev->dvb_ep_bulk = e->bEndpointAddress;
			}
		}
		return;
	case 0x85:
		if (usb_endpoint_xfer_isoc(e)) {
			if (size > dev->dvb_max_pkt_size_isoc_ts2) {
				dev->dvb_ep_isoc_ts2 = e->bEndpointAddress;
				dev->dvb_max_pkt_size_isoc_ts2 = size;
				dev->dvb_alt_isoc = alt;
			}
		} else {
			dev->dvb_ep_bulk_ts2 = e->bEndpointAddress;
		}
		return;
	}
}
