void remap_struct(unsigned int gtypes_nr[], unsigned int ftypes_nr[],
		  void *ps, unsigned int f_size, unsigned int g_size)
{
	int d;


	if (MAP_SIZE(ftypes_nr) > f_size)
		return;


	d = gtypes_nr[0] - ftypes_nr[0];
	if (d) {
		memmove(((char *) ps) + gtypes_nr[0] * ULL_ALIGNMENT_WIDTH,
			((char *) ps) + ftypes_nr[0] * ULL_ALIGNMENT_WIDTH,
			MINIMUM(f_size - ftypes_nr[0] * ULL_ALIGNMENT_WIDTH,
				g_size - gtypes_nr[0] * ULL_ALIGNMENT_WIDTH));
		if (d > 0) {
			memset(((char *) ps) + ftypes_nr[0] * ULL_ALIGNMENT_WIDTH,
			       0, d * ULL_ALIGNMENT_WIDTH);
		}
	}

	d = gtypes_nr[1] - ftypes_nr[1];
	if (d) {
		memmove(((char *) ps) + gtypes_nr[0] * ULL_ALIGNMENT_WIDTH
				      + gtypes_nr[1] * UL_ALIGNMENT_WIDTH,
			((char *) ps) + gtypes_nr[0] * ULL_ALIGNMENT_WIDTH
				      + ftypes_nr[1] * UL_ALIGNMENT_WIDTH,
			MINIMUM(f_size - ftypes_nr[0] * ULL_ALIGNMENT_WIDTH
				       - ftypes_nr[1] * UL_ALIGNMENT_WIDTH,
				g_size - gtypes_nr[0] * ULL_ALIGNMENT_WIDTH
				       - gtypes_nr[1] * UL_ALIGNMENT_WIDTH));
		if (d > 0) {
			memset(((char *) ps) + gtypes_nr[0] * ULL_ALIGNMENT_WIDTH
					     + ftypes_nr[1] * UL_ALIGNMENT_WIDTH,
			       0, d * UL_ALIGNMENT_WIDTH);
		}
	}

	d = gtypes_nr[2] - ftypes_nr[2];
	if (d) {
		memmove(((char *) ps) + gtypes_nr[0] * ULL_ALIGNMENT_WIDTH
				      + gtypes_nr[1] * UL_ALIGNMENT_WIDTH
				      + gtypes_nr[2] * U_ALIGNMENT_WIDTH,
			((char *) ps) + gtypes_nr[0] * ULL_ALIGNMENT_WIDTH
				      + gtypes_nr[1] * UL_ALIGNMENT_WIDTH
				      + ftypes_nr[2] * U_ALIGNMENT_WIDTH,
			MINIMUM(f_size - ftypes_nr[0] * ULL_ALIGNMENT_WIDTH
				       - ftypes_nr[1] * UL_ALIGNMENT_WIDTH
				       - ftypes_nr[2] * U_ALIGNMENT_WIDTH,
				g_size - gtypes_nr[0] * ULL_ALIGNMENT_WIDTH
				       - gtypes_nr[1] * UL_ALIGNMENT_WIDTH
				       - gtypes_nr[2] * U_ALIGNMENT_WIDTH));
		if (d > 0) {
			memset(((char *) ps) + gtypes_nr[0] * ULL_ALIGNMENT_WIDTH
					     + gtypes_nr[1] * UL_ALIGNMENT_WIDTH
					     + ftypes_nr[2] * U_ALIGNMENT_WIDTH,
			       0, d * U_ALIGNMENT_WIDTH);
		}
	}
}
