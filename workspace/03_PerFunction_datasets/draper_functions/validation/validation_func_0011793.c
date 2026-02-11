show_cavan_usb_descriptor(const struct cavan_usb_descriptor *desc)
{
	int i, j, count;

	print_sep(60);
	pr_bold_info("usb deivce descriptor:");
	show_usb_device_descriptor(&desc->dev_desc);
	print_sep(60);

	for (i = 0, count = desc->dev_desc.bNumConfigurations; i < count; i++)
	{
		pr_bold_info("usb config descriptor[%d]:", i);
		show_usb_config_descriptor(desc->cfg_descs + i);
	}

	print_sep(60);

	pr_bold_info("interface descriptor count = %d", desc->if_count);

	for (i = 0, count = desc->if_count; i < count; i++)
	{
		pr_bold_info("usb interface descriptor[%d]:", i);
		show_usb_interface_descriptor(&desc->if_descs[i].if_desc);

		for (j = 0; j < desc->if_descs[i].if_desc.bNumEndpoints; j++)
		{
			pr_bold_info("usb endpoint[%d]:", j);
			show_usb_endpoint_descriptor(desc->if_descs[i].ep_descs + j);
		}
	}

	print_sep(60);
}
