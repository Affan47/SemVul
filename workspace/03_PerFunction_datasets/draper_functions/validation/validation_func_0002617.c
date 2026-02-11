flodivmod(double x, double y, double *divp, double *modp)
{
    double div, mod;

    if (y == 0.0) rb_num_zerodiv();
    if((x == 0.0) || (isinf(y) && !isinf(x)))
        mod = x;
    else {
#ifdef HAVE_FMOD
	mod = fmod(x, y);
#else
	double z;

	modf(x/y, &z);
	mod = x - z * y;
#endif
    }
    if (isinf(x) && !isinf(y) && !isnan(y))
	div = x;
    else
	div = (x - mod) / y;
    if (y*mod < 0) {
	mod += y;
	div -= 1.0;
    }
    if (modp) *modp = mod;
    if (divp) *divp = div;
}
