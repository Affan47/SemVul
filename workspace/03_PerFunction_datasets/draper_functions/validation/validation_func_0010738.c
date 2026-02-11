ff_dev_create(void)
{
	struct ff_dev *ff;
	struct fmc_device *fmc;
	int i, ret;

	ff = kzalloc(sizeof(*ff), GFP_KERNEL);
	if (!ff)
		return ERR_PTR(-ENOMEM);
	dev_set_name(&ff->dev, "fake-fmc-carrier");
	ff->dev.release = ff_dev_release;

	ret = device_register(&ff->dev);
	if (ret < 0) {
		put_device(&ff->dev);
		return ERR_PTR(ret);
	}


	for (i = 0; i < ff_nr_dev; i++) {
		fmc = kmemdup(&ff_template_fmc, sizeof(ff_template_fmc),
			      GFP_KERNEL);
		fmc->hwdev = &ff->dev;
		fmc->carrier_data = ff;
		fmc->nr_slots = ff_nr_dev;

		fmc->eeprom = ff_eeimg[i];
		fmc->eeprom_addr = 0x50 + 2 * i;
		fmc->slot_id = i;
		ff->fmc[i] = fmc;

		ff_template_fmc.device_id++;
	}
	return ff;
}
