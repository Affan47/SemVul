stk1160_i2c_register(struct stk1160 *dev)
{
	int rc;

	dev->i2c_adap = adap_template;
	dev->i2c_adap.dev.parent = dev->dev;
	strcpy(dev->i2c_adap.name, "stk1160");
	dev->i2c_adap.algo_data = dev;

	i2c_set_adapdata(&dev->i2c_adap, &dev->v4l2_dev);

	rc = i2c_add_adapter(&dev->i2c_adap);
	if (rc < 0) {
		stk1160_err("cannot add i2c adapter (%d)\n", rc);
		return rc;
	}

	dev->i2c_client = client_template;
	dev->i2c_client.adapter = &dev->i2c_adap;


	stk1160_write_reg(dev, STK1160_SICTL_CD,  0x0f);


	stk1160_write_reg(dev, STK1160_ASIC + 3,  0x00);

	return 0;
}
