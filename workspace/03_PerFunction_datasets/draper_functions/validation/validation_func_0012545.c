ts3a227e_i2c_probe(struct i2c_client *i2c,
			      const struct i2c_device_id *id)
{
	struct ts3a227e *ts3a227e;
	struct device *dev = &i2c->dev;
	int ret;
	unsigned int acc_reg;

	ts3a227e = devm_kzalloc(&i2c->dev, sizeof(*ts3a227e), GFP_KERNEL);
	if (ts3a227e == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, ts3a227e);
	ts3a227e->dev = dev;
	ts3a227e->irq = i2c->irq;

	ts3a227e->regmap = devm_regmap_init_i2c(i2c, &ts3a227e_regmap_config);
	if (IS_ERR(ts3a227e->regmap))
		return PTR_ERR(ts3a227e->regmap);

	ret = ts3a227e_parse_device_property(ts3a227e, dev);
	if (ret) {
		dev_err(dev, "Failed to parse device property: %d\n", ret);
		return ret;
	}

	ret = devm_request_threaded_irq(dev, i2c->irq, NULL, ts3a227e_interrupt,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					"TS3A227E", ts3a227e);
	if (ret) {
		dev_err(dev, "Cannot request irq %d (%d)\n", i2c->irq, ret);
		return ret;
	}

	ret = devm_snd_soc_register_component(&i2c->dev, &ts3a227e_soc_driver,
					      NULL, 0);
	if (ret)
		return ret;


	regmap_update_bits(ts3a227e->regmap, TS3A227E_REG_INTERRUPT_DISABLE,
			   INTB_DISABLE | ADC_COMPLETE_INT_DISABLE,
			   ADC_COMPLETE_INT_DISABLE);


	regmap_read(ts3a227e->regmap, TS3A227E_REG_ACCESSORY_STATUS, &acc_reg);
	ts3a227e_new_jack_state(ts3a227e, acc_reg);
	ts3a227e_jack_report(ts3a227e);

	return 0;
}
