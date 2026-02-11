gpm_round_down (gfloat value, gint smallest)
{
	gfloat division;
	if (fabs (value) < 0.01)
		return 0;
	if (smallest == 0) {
		g_warning ("divisor zero");
		return 0;
	}
	division = (gfloat) value / (gfloat) smallest;
	division = floorf (division);
	division *= smallest;
	return (gint) division;
}
