needwarning(int wt)
{
	int ret;

	if (wt < 10)
		ret = 1;
	else if (wt < 60)
		ret = (wt % 15 == 0);
	else if (wt < 180)
		ret = (wt % 30 == 0);
	else
		ret = (wt % 60 == 0);

	return ret;
}
