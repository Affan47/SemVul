netup_i2c_remove(struct netup_unidvb_dev *ndev, int bus_num)
{
	struct netup_i2c *i2c;

	if (bus_num < 0 || bus_num > 1) {
		dev_err(&ndev->pci_dev->dev,
			"%s(): invalid bus number %d\n", __func__, bus_num);
		return;
	}
	i2c = &ndev->i2c[bus_num];
	netup_i2c_reset(i2c);

	i2c_del_adapter(&i2c->adap);
	dev_info(&ndev->pci_dev->dev,
		"netup_i2c_remove: unregistered I2C bus %d\n", bus_num);
}
