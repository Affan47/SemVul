ddb_ci_attach(struct ddb_port *port)
{
	int ret;

	ret = dvb_register_adapter(&port->output->adap,
				   "DDBridge",
				   THIS_MODULE,
				   &port->dev->pdev->dev,
				   adapter_nr);
	if (ret < 0)
		return ret;
	port->en = cxd2099_attach(&cxd_cfg, port, &port->i2c->adap);
	if (!port->en) {
		dvb_unregister_adapter(&port->output->adap);
		return -ENODEV;
	}
	ddb_input_start(port->input[0]);
	ddb_output_start(port->output);
	dvb_ca_en50221_init(&port->output->adap,
			    port->en, 0, 1);
	ret = dvb_register_device(&port->output->adap, &port->output->dev,
				  &dvbdev_ci, (void *) port->output,
				  DVB_DEVICE_SEC);
	return ret;
}
