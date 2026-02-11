register_slot(int slot, struct grip_mp *grip)
{
	struct grip_port *port = grip->port[slot];
	struct input_dev *input_dev;
	int j, t;
	int err;

	port->dev = input_dev = input_allocate_device();
	if (!input_dev)
		return -ENOMEM;

	input_dev->name = grip_name[port->mode];
	input_dev->id.bustype = BUS_GAMEPORT;
	input_dev->id.vendor = GAMEPORT_ID_VENDOR_GRAVIS;
	input_dev->id.product = 0x0100 + port->mode;
	input_dev->id.version = 0x0100;
	input_dev->dev.parent = &grip->gameport->dev;

	input_set_drvdata(input_dev, grip);

	input_dev->open = grip_open;
	input_dev->close = grip_close;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	for (j = 0; (t = grip_abs[port->mode][j]) >= 0; j++)
		input_set_abs_params(input_dev, t, -1, 1, 0, 0);

	for (j = 0; (t = grip_btn[port->mode][j]) >= 0; j++)
		if (t > 0)
			set_bit(t, input_dev->keybit);

	err = input_register_device(port->dev);
	if (err) {
		input_free_device(port->dev);
		return err;
	}

	port->registered = 1;

	if (port->dirty)
		report_slot(grip, slot);

	return 0;
}
