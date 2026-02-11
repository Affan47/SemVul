G_zeros_r_nulls(int zeros_r_nulls)
{
    if (zeros_r_nulls >= 0)
	_zeros_r_nulls = zeros_r_nulls > 0;

    return _zeros_r_nulls;
}
