CRYPTO_pop_info(void)
	{
	int ret=0;

	if (is_MemCheck_on())
		{
		MemCheck_off();

		ret=(pop_info() != NULL);

		MemCheck_on();
		}
	return(ret);
	}
