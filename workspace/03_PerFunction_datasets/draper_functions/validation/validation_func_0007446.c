devm_spi_register_master(struct device *dev, struct spi_master *master)
{
	struct spi_master **ptr;
	int ret;

	ptr = devres_alloc(devm_spi_unregister, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	ret = spi_register_master(master);
	if (!ret) {
		*ptr = master;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return ret;
}
