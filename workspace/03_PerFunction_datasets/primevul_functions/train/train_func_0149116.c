static void pn533_usb_abort_cmd(struct pn533 *dev, gfp_t flags)
{
	struct pn533_usb_phy *phy = dev->phy;


	if (dev->device_type == PN533_DEVICE_ACR122U)
		return;


	pn533_usb_send_ack(dev, flags);


	usb_kill_urb(phy->in_urb);
}
