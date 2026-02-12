static int keyring_instantiate(struct key *keyring,
			       const void *data, size_t datalen)
{
	int ret;

	ret = -EINVAL;
	if (datalen == 0) {

		keyring_publish_name(keyring);
		ret = 0;
	}

	return ret;

}
