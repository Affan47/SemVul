cddb_sum (int n)
{
	int ret = 0;

	while (n > 0)
	{
		ret = ret + (n % 10);
		n = n/10;
	}

	return (ret);
}
