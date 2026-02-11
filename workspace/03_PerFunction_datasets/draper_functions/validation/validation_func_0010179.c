fread_u4(u4 *x, FILE *fp)
{
	u1	b[4];
	size_t	len;

	if((len = fread(b, 1, 4, fp)) != 4)
		return len;
	*x = unflip4(b);
	return 4;
}
