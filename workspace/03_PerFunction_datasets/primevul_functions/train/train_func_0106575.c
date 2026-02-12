static void put_dev (struct dev_data *data)
{
	if (likely (!refcount_dec_and_test (&data->count)))
		return;

	BUG_ON (waitqueue_active (&data->wait));
	kfree (data);
}
