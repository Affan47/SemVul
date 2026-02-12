void swap_struct(unsigned int types_nr[], void *ps, int is64bit)
{
	int i;
	uint64_t *x;
	uint32_t *y;

	x = (uint64_t *) ps;

	for (i = 0; i < types_nr[0]; i++) {
		*x = __builtin_bswap64(*x);
		x = (uint64_t *) ((char *) x + ULL_ALIGNMENT_WIDTH);
	}

	y = (uint32_t *) x;

	for (i = 0; i < types_nr[1]; i++) {
		if (is64bit) {
			*x = __builtin_bswap64(*x);
			x = (uint64_t *) ((char *) x + UL_ALIGNMENT_WIDTH);
		}
		else {
			*y = __builtin_bswap32(*y);
			y = (uint32_t *) ((char *) y + UL_ALIGNMENT_WIDTH);
		}
	}

	if (is64bit) {
		y = (uint32_t *) x;
	}

	for (i = 0; i < types_nr[2]; i++) {
		*y = __builtin_bswap32(*y);
		y = (uint32_t *) ((char *) y + U_ALIGNMENT_WIDTH);
	}
}
