static unsigned int spectrum512_FindIndex(i64 x, unsigned int c)
{
	i64 x1;

	x1 = 10 * (i64)c;

	if (c & 1)
		x1 = x1 - 5;
	else
		x1 = x1 + 1;

	if (x >= x1 && x < x1+160)
		c = c + 16;
	else if (x >= x1+160)
		c = c + 32;

	return c;
}
