int usb_string_id(struct usb_composite_dev *cdev)
{
	if (cdev->next_string_id < 254) {


		cdev->next_string_id++;
		return cdev->next_string_id;
	}
	return -ENODEV;
}
