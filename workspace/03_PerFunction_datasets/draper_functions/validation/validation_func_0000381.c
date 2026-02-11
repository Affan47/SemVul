bigsub(VALUE x, VALUE y)
{
    VALUE z = 0;
    long i = RBIGNUM_LEN(x);
    BDIGIT *xds, *yds;


    if (RBIGNUM_LEN(x) < RBIGNUM_LEN(y)) {
	z = x; x = y; y = z;
    }
    else if (RBIGNUM_LEN(x) == RBIGNUM_LEN(y)) {
	xds = BDIGITS(x);
	yds = BDIGITS(y);
	while (i > 0) {
	    i--;
	    if (xds[i] > yds[i]) {
		break;
	    }
	    if (xds[i] < yds[i]) {
		z = x; x = y; y = z;
		break;
	    }
	}
    }

    z = bignew(RBIGNUM_LEN(x), z==0);
    bigsub_core(BDIGITS(x), RBIGNUM_LEN(x),
		BDIGITS(y), RBIGNUM_LEN(y),
		BDIGITS(z), RBIGNUM_LEN(z));

    return z;
}
