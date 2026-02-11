ua2regval(int ua, bool cgain)
{
	int ret;
	if (cgain)
		ua /= 2;
	ret = (ua * 10 + 8500 * 1000) / 16618;

	if (ret < 512)
		ret = 512;
	return ret;
}
