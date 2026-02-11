i2c_do_del_adapter(struct i2c_driver *driver,
			      struct i2c_adapter *adapter)
{
	struct i2c_client *client, *_n;


	list_for_each_entry_safe(client, _n, &driver->clients, detected) {
		if (client->adapter == adapter) {
			dev_dbg(&adapter->dev, "Removing %s at 0x%x\n",
				client->name, client->addr);
			list_del(&client->detected);
			i2c_unregister_device(client);
		}
	}
}
