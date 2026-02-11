PGTYPESnumeric_to_decimal(numeric *src, decimal *dst)
{
	int			i;

	if (src->ndigits > DECSIZE)
	{
		errno = PGTYPES_NUM_OVERFLOW;
		return -1;
	}

	dst->weight = src->weight;
	dst->rscale = src->rscale;
	dst->dscale = src->dscale;
	dst->sign = src->sign;
	dst->ndigits = src->ndigits;

	for (i = 0; i < src->ndigits; i++)
		dst->digits[i] = src->digits[i];

	return 0;
}
