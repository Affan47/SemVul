tps6586x_i2c_remove(struct i2c_client *client)
{
	struct tps6586x *tps6586x = i2c_get_clientdata(client);

	tps6586x_remove_subdevs(tps6586x);
	mfd_remove_devices(tps6586x->dev);
	if (client->irq)
		free_irq(client->irq, tps6586x);
	return 0;
}
