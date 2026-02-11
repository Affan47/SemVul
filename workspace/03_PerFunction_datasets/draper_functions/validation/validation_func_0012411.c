learn_symbol(unsigned char *symbol, int len)
{
	int i;

	for (i = 0; i < len - 1; i++)
		token_profit[ symbol[i] + (symbol[i + 1] << 8) ]++;
}
