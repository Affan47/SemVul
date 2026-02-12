static bool elo_broken_firmware(struct usb_device *dev)
{
	struct usb_device *hub = dev->parent;
	struct usb_device *child = NULL;
	u16 fw_lvl = le16_to_cpu(dev->descriptor.bcdDevice);
	u16 child_vid, child_pid;
	int i;

	if (!use_fw_quirk)
		return false;
	if (fw_lvl != 0x10d)
		return false;


	usb_hub_for_each_child(hub, i, child) {
		child_vid = le16_to_cpu(child->descriptor.idVendor);
		child_pid = le16_to_cpu(child->descriptor.idProduct);


		if (child_vid==0x04b3) {
			switch (child_pid) {
			case 0x4676:
			case 0x4677:
			case 0x4678:
			case 0x4679:
				return false;
			}
		}
	}
	return true;
}
