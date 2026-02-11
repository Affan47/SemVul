sp2_remove(struct i2c_client *client)
{
	struct sp2 *s = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");
	sp2_exit(client);
	kfree(s);
	return 0;
}
