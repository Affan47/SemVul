unfilter2(unsigned char *prev, unsigned char *curr)
{
	unsigned int pos;

	for (pos = 1; pos < step; pos++)
		curr[pos] += prev[pos];
}
