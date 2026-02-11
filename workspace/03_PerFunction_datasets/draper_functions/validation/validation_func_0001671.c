hidinput_allocate(struct hid_device *hid)
{
	struct hid_input *hidinput = kzalloc(sizeof(*hidinput), GFP_KERNEL);
	struct input_dev *input_dev = input_allocate_device();
	if (!hidinput || !input_dev) {
		kfree(hidinput);
		input_free_device(input_dev);
		hid_err(hid, "Out of memory during hid input probe\n");
		return NULL;
	}

	input_set_drvdata(input_dev, hid);
	input_dev->event = hidinput_input_event;
	input_dev->open = hidinput_open;
	input_dev->close = hidinput_close;
	input_dev->setkeycode = hidinput_setkeycode;
	input_dev->getkeycode = hidinput_getkeycode;

	input_dev->name = hid->name;
	input_dev->phys = hid->phys;
	input_dev->uniq = hid->uniq;
	input_dev->id.bustype = hid->bus;
	input_dev->id.vendor  = hid->vendor;
	input_dev->id.product = hid->product;
	input_dev->id.version = hid->version;
	input_dev->dev.parent = &hid->dev;
	hidinput->input = input_dev;
	list_add_tail(&hidinput->list, &hid->inputs);

	return hidinput;
}
