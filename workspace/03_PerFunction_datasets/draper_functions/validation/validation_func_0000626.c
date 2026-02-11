P_get_BandWidth(int interpolator, int nsplines)
{


    if (interpolator == P_BILINEAR) {
	return (2 * nsplines + 1);
    }
    else {
	return (4 * nsplines + 3);
    }
}
