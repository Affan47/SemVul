isd200_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct us_data *us;
	int result;

	result = usb_stor_probe1(&us, intf, id,
			(id - isd200_usb_ids) + isd200_unusual_dev_list,
			&isd200_host_template);
	if (result)
		return result;

	us->protocol_name = "ISD200 ATA/ATAPI";
	us->proto_handler = isd200_ata_command;

	result = usb_stor_probe2(us);
	return result;
}
