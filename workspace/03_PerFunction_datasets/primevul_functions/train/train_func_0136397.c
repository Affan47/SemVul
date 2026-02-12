static diy_fp_t normalize_boundary(diy_fp_t in)
{
	diy_fp_t res = in;


	while (! (res.f & (DP_HIDDEN_BIT << 1))) {
		res.f <<= 1;
		res.e--;
	}

	res.f <<= (DIY_SIGNIFICAND_SIZE - DP_SIGNIFICAND_SIZE - 2);
	res.e = res.e - (DIY_SIGNIFICAND_SIZE - DP_SIGNIFICAND_SIZE - 2);
	return res;
}
