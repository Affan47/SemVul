gnm_sinpi (gnm_float x)
{
	int k;

	if (gnm_isnan (x))
		return x;

	if (!gnm_finite (x))
		return gnm_nan;

	k = (x < 0) ? 2 : 0;
	x = gnm_fmod (gnm_abs (x), 2);
	if (x >= 1) {
		x -= 1;
		k ^= 2;
	}
	if (x >= 0.5) {
		x -= 0.5;
		k += 1;
	}
	if (x == 0) {
		static const gnm_float ys[4] = { 0, 1, -0, -1 };
		return ys[k];
	} else {
		switch (k) {
		default:
		case 0: return +gnm_sin (M_PIgnum * x);
		case 1: return +gnm_cos (M_PIgnum * x);
		case 2: return -gnm_sin (M_PIgnum * x);
		case 3: return -gnm_cos (M_PIgnum * x);
		}
	}
}
