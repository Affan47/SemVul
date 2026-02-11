eeti_ts_probe(struct i2c_client *client,
				   const struct i2c_device_id *idp)
{
	struct eeti_ts_platform_data *pdata = dev_get_platdata(&client->dev);
	struct eeti_ts_priv *priv;
	struct input_dev *input;
	unsigned int irq_flags;
	int err = -ENOMEM;


	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		dev_err(&client->dev, "failed to allocate driver data\n");
		goto err0;
	}

	mutex_init(&priv->mutex);
	input = input_allocate_device();

	if (!input) {
		dev_err(&client->dev, "Failed to allocate input device.\n");
		goto err1;
	}

	input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_set_abs_params(input, ABS_X, 0, EETI_MAXVAL, 0, 0);
	input_set_abs_params(input, ABS_Y, 0, EETI_MAXVAL, 0, 0);
	input_set_abs_params(input, ABS_PRESSURE, 0, 0xff, 0, 0);

	input->name = client->name;
	input->id.bustype = BUS_I2C;
	input->dev.parent = &client->dev;
	input->open = eeti_ts_open;
	input->close = eeti_ts_close;

	priv->client = client;
	priv->input = input;
	priv->irq_gpio = pdata->irq_gpio;
	priv->irq = gpio_to_irq(pdata->irq_gpio);

	err = gpio_request_one(pdata->irq_gpio, GPIOF_IN, client->name);
	if (err < 0)
		goto err1;

	priv->irq_active_high = pdata->irq_active_high;

	irq_flags = priv->irq_active_high ?
		IRQF_TRIGGER_RISING : IRQF_TRIGGER_FALLING;

	INIT_WORK(&priv->work, eeti_ts_read);
	i2c_set_clientdata(client, priv);
	input_set_drvdata(input, priv);

	err = input_register_device(input);
	if (err)
		goto err2;

	err = request_irq(priv->irq, eeti_ts_isr, irq_flags,
			  client->name, priv);
	if (err) {
		dev_err(&client->dev, "Unable to request touchscreen IRQ.\n");
		goto err3;
	}


	eeti_ts_stop(priv);

	device_init_wakeup(&client->dev, 0);
	return 0;

err3:
	input_unregister_device(input);
	input = NULL;
err2:
	gpio_free(pdata->irq_gpio);
err1:
	input_free_device(input);
	kfree(priv);
err0:
	return err;
}
