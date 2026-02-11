CONF_load_bio(LHASH_OF(CONF_VALUE) *conf, BIO *bp,
				    long *eline)
	{
	CONF ctmp;
	int ret;

	CONF_set_nconf(&ctmp, conf);

	ret = NCONF_load_bio(&ctmp, bp, eline);
	if (ret)
		return ctmp.data;
	return NULL;
	}
