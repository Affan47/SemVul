static int scale_linear(int it, int width, int max_change)
{


	if (max_change < 2)
		return it;
	return ((it - 1) * (width - 1) + max_change - 1) / (max_change - 1);
}
