usb_show_dynids(struct usb_dynids *dynids, char *buf)
{
	struct usb_dynid *dynid;
	size_t count = 0;

	list_for_each_entry(dynid, &dynids->list, node)
		if (dynid->id.bInterfaceClass != 0)
			count += scnprintf(&buf[count], PAGE_SIZE - count, "%04x %04x %02x\n",
					   dynid->id.idVendor, dynid->id.idProduct,
					   dynid->id.bInterfaceClass);
		else
			count += scnprintf(&buf[count], PAGE_SIZE - count, "%04x %04x\n",
					   dynid->id.idVendor, dynid->id.idProduct);
	return count;
}
