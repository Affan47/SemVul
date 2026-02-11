saa7164_i2c_register(struct saa7164_i2c *bus)
{
	struct saa7164_dev *dev = bus->dev;

	dprintk(DBGLVL_I2C, "%s(bus = %d)\n", __func__, bus->nr);

	bus->i2c_adap = saa7164_i2c_adap_template;
	bus->i2c_client = saa7164_i2c_client_template;

	bus->i2c_adap.dev.parent = &dev->pci->dev;

	strlcpy(bus->i2c_adap.name, bus->dev->name,
		sizeof(bus->i2c_adap.name));

	bus->i2c_adap.algo_data = bus;
	i2c_set_adapdata(&bus->i2c_adap, bus);
	i2c_add_adapter(&bus->i2c_adap);

	bus->i2c_client.adapter = &bus->i2c_adap;

	if (0 != bus->i2c_rc)
		printk(KERN_ERR "%s: i2c bus %d register FAILED\n",
			dev->name, bus->nr);

	return bus->i2c_rc;
}
