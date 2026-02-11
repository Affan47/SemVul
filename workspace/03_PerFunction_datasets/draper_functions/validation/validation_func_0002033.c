log1pmx (gnm_float x)
{
    static const gnm_float minLog1Value = GNM_const(-0.79149064);
    static const gnm_float two = 2;

    if (x > 1 || x < minLog1Value)
	return gnm_log1p(x) - x;
    else {
	gnm_float term = x / (2 + x);
	gnm_float y = term * term;
	if (gnm_abs(x) < 1e-2)
	    return term * ((((two / 9 * y + two / 7) * y + two / 5) * y +
			    two / 3) * y - x);
	else
	    return term * (2 * y * gnm_logcf (y, 3, 2) - x);
    }
}
