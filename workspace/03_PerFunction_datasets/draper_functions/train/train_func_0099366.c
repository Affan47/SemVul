pk_probe(struct hid_device *hdev, const struct hid_device_id *id)
{
	int ret;
	struct usb_interface *intf = to_usb_interface(hdev->dev.parent);
	unsigned short ifnum = intf->cur_altsetting->desc.bInterfaceNumber;
	unsigned long quirks = id->driver_data;
	struct pk_device *pk;
	struct pcmidi_snd *pm = NULL;

	pk = kzalloc(sizeof(*pk), GFP_KERNEL);
	if (pk == NULL) {
		hid_err(hdev, "can't alloc descriptor\n");
		return -ENOMEM;
	}

	pk->hdev = hdev;

	pm = kzalloc(sizeof(*pm), GFP_KERNEL);
	if (pm == NULL) {
		hid_err(hdev, "can't alloc descriptor\n");
		ret = -ENOMEM;
		goto err_free_pk;
	}

	pm->pk = pk;
	pk->pm = pm;
	pm->ifnum = ifnum;

	hid_set_drvdata(hdev, pk);

	ret = hid_parse(hdev);
	if (ret) {
		hid_err(hdev, "hid parse failed\n");
		goto err_free;
	}

	if (quirks & PK_QUIRK_NOGET) {
		hdev->quirks |= HID_QUIRK_NOGET;
	}

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	if (ret) {
		hid_err(hdev, "hw start failed\n");
		goto err_free;
	}

	ret = pcmidi_snd_initialise(pm);
	if (ret < 0)
		goto err_stop;

	return 0;
err_stop:
	hid_hw_stop(hdev);
err_free:
	kfree(pm);
err_free_pk:
	kfree(pk);

	return ret;
}
