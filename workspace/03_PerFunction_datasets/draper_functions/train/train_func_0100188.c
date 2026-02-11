of_iio_channel_get(struct device_node *np, int index)
{
	struct iio_channel *channel;
	int err;

	if (index < 0)
		return ERR_PTR(-EINVAL);

	channel = kzalloc(sizeof(*channel), GFP_KERNEL);
	if (channel == NULL)
		return ERR_PTR(-ENOMEM);

	err = __of_iio_channel_get(channel, np, index);
	if (err)
		goto err_free_channel;

	return channel;

err_free_channel:
	kfree(channel);
	return ERR_PTR(err);
}
