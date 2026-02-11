bq24735_parse_dt_data(struct i2c_client *client)
{
	struct bq24735_platform *pdata;
	struct device_node *np = client->dev.of_node;
	u32 val;
	int ret;
	enum of_gpio_flags flags;

	pdata = devm_kzalloc(&client->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		dev_err(&client->dev,
			"Memory alloc for bq24735 pdata failed\n");
		return NULL;
	}

	pdata->status_gpio = of_get_named_gpio_flags(np, "ti,ac-detect-gpios",
						     0, &flags);

	if (flags & OF_GPIO_ACTIVE_LOW)
		pdata->status_gpio_active_low = 1;

	ret = of_property_read_u32(np, "ti,charge-current", &val);
	if (!ret)
		pdata->charge_current = val;

	ret = of_property_read_u32(np, "ti,charge-voltage", &val);
	if (!ret)
		pdata->charge_voltage = val;

	ret = of_property_read_u32(np, "ti,input-current", &val);
	if (!ret)
		pdata->input_current = val;

	return pdata;
}
