w83792d_detect_subclients(struct i2c_client *new_client)
{
	int i, id, err;
	int address = new_client->addr;
	u8 val;
	struct i2c_adapter *adapter = new_client->adapter;
	struct w83792d_data *data = i2c_get_clientdata(new_client);

	id = i2c_adapter_id(adapter);
	if (force_subclients[0] == id && force_subclients[1] == address) {
		for (i = 2; i <= 3; i++) {
			if (force_subclients[i] < 0x48 ||
			    force_subclients[i] > 0x4f) {
				dev_err(&new_client->dev,
					"invalid subclient address %d; must be 0x48-0x4f\n",
					force_subclients[i]);
				err = -ENODEV;
				goto ERROR_SC_0;
			}
		}
		w83792d_write_value(new_client, W83792D_REG_I2C_SUBADDR,
					(force_subclients[2] & 0x07) |
					((force_subclients[3] & 0x07) << 4));
	}

	val = w83792d_read_value(new_client, W83792D_REG_I2C_SUBADDR);
	if (!(val & 0x08))
		data->lm75[0] = i2c_new_dummy(adapter, 0x48 + (val & 0x7));
	if (!(val & 0x80)) {
		if ((data->lm75[0] != NULL) &&
			((val & 0x7) == ((val >> 4) & 0x7))) {
			dev_err(&new_client->dev,
				"duplicate addresses 0x%x, use force_subclient\n",
				data->lm75[0]->addr);
			err = -ENODEV;
			goto ERROR_SC_1;
		}
		data->lm75[1] = i2c_new_dummy(adapter,
					      0x48 + ((val >> 4) & 0x7));
	}

	return 0;


ERROR_SC_1:
	if (data->lm75[0] != NULL)
		i2c_unregister_device(data->lm75[0]);
ERROR_SC_0:
	return err;
}
