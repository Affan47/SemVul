range_bogusproduct (gnm_float const *xs, int n, gnm_float *res)
{
	if (n == 0) {
		*res = 0;
		return 0;
	} else
		return gnm_range_product (xs, n, res);
}
