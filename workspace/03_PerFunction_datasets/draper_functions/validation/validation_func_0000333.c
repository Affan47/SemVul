kPalette(state_t *s, int funct_nr, int argc, reg_t *argv)
{
	switch (UKPV(0))
	{
	case 5 : {
		int r = UKPV(1);
		int g = UKPV(2);
		int b = UKPV(3);

		int i, delta, bestindex = -1, bestdelta = 200000;

		for (i = 0; i < KERNEL_COLORS_NR; i++) {
			int dr = abs (KERNEL_COLOR_PALETTE[i].r - r);
			int dg = abs (KERNEL_COLOR_PALETTE[i].g - g);
			int db = abs (KERNEL_COLOR_PALETTE[i].b - b);

			delta = dr*dr + dg * dg + db * db;

			if (delta < bestdelta)
			{
				bestdelta = delta;
				bestindex = i;
			}
		}


		return make_reg(0, bestindex);
	}

	case 4 :
	case 6 :
		break;
	default :
		SCIkdebug(SCIkWARNING, "Unimplemented subfunction: %d\n", UKPV(0));
	}
	return s->r_acc;
}
