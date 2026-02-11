pn544_hci_i2c_probe(struct i2c_client *client,
			       const struct i2c_device_id *id)
{
	struct pn544_i2c_phy *phy;
	struct pn544_nfc_platform_data *pdata;
	int r = 0;

	dev_dbg(&client->dev, "%s\n", __func__);
	dev_dbg(&client->dev, "IRQ: %d\n", client->irq);

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		nfc_err(&client->dev, "Need I2C_FUNC_I2C\n");
		return -ENODEV;
	}

	phy = devm_kzalloc(&client->dev, sizeof(struct pn544_i2c_phy),
			   GFP_KERNEL);
	if (!phy)
		return -ENOMEM;

	INIT_WORK(&phy->fw_work, pn544_hci_i2c_fw_work);
	phy->fw_work_state = FW_WORK_STATE_IDLE;

	phy->i2c_dev = client;
	i2c_set_clientdata(client, phy);

	pdata = client->dev.platform_data;


	if (!pdata && client->dev.of_node) {
		r = pn544_hci_i2c_of_request_resources(client);
		if (r) {
			nfc_err(&client->dev, "No DT data\n");
			return r;
		}

	} else if (pdata) {

		if (pdata->request_resources == NULL) {
			nfc_err(&client->dev, "request_resources() missing\n");
			return -EINVAL;
		}

		r = pdata->request_resources(client);
		if (r) {
			nfc_err(&client->dev,
				"Cannot get platform resources\n");
			return r;
		}

		phy->gpio_en = pdata->get_gpio(NFC_GPIO_ENABLE);
		phy->gpio_fw = pdata->get_gpio(NFC_GPIO_FW_RESET);
		phy->gpio_irq = pdata->get_gpio(NFC_GPIO_IRQ);

	} else if (ACPI_HANDLE(&client->dev)) {
		r = pn544_hci_i2c_acpi_request_resources(client);
		if (r) {
			nfc_err(&client->dev,
				"Cannot get ACPI data\n");
			return r;
		}
	} else {
		nfc_err(&client->dev, "No platform data\n");
		return -EINVAL;
	}

	pn544_hci_i2c_platform_init(phy);

	r = request_threaded_irq(client->irq, NULL, pn544_hci_i2c_irq_thread_fn,
				 IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				 PN544_HCI_I2C_DRIVER_NAME, phy);
	if (r < 0) {
		nfc_err(&client->dev, "Unable to register IRQ handler\n");
		goto err_rti;
	}

	r = pn544_hci_probe(phy, &i2c_phy_ops, LLC_SHDLC_NAME,
			    PN544_I2C_FRAME_HEADROOM, PN544_I2C_FRAME_TAILROOM,
			    PN544_HCI_I2C_LLC_MAX_PAYLOAD,
			    pn544_hci_i2c_fw_download, &phy->hdev);
	if (r < 0)
		goto err_hci;

	return 0;

err_hci:
	free_irq(client->irq, phy);

err_rti:
	if (!pdata) {
		gpio_free(phy->gpio_en);
		gpio_free(phy->gpio_fw);
	} else if (pdata->free_resources) {
		pdata->free_resources();
	}

	return r;
}
