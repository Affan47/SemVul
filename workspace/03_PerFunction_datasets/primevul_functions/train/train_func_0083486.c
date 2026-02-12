hufDecode
    (const Int64 * 	hcode,
     const HufDec * 	hdecod,
     const char* 	in,
     int		ni,
     int		rlc,
     int		no,
     unsigned short*	out)
{
    Int64 c = 0;
    int lc = 0;
    unsigned short * outb = out;
    unsigned short * oe = out + no;
    const char * ie = in + (ni + 7) / 8;


    while (in < ie)
    {
	getChar (c, lc, in);


	while (lc >= HUF_DECBITS)
	{
	    const HufDec pl = hdecod[(c >> (lc-HUF_DECBITS)) & HUF_DECMASK];

	    if (pl.len)
	    {


		lc -= pl.len;
		getCode (pl.lit, rlc, c, lc, in, out, outb, oe);
	    }
	    else
	    {
		if (!pl.p)
		    invalidCode();


		int j;

		for (j = 0; j < pl.lit; j++)
		{
		    int	l = hufLength (hcode[pl.p[j]]);

		    while (lc < l && in < ie)
			getChar (c, lc, in);

		    if (lc >= l)
		    {
			if (hufCode (hcode[pl.p[j]]) ==
				((c >> (lc - l)) & ((Int64(1) << l) - 1)))
			{


			    lc -= l;
			    getCode (pl.p[j], rlc, c, lc, in, out, outb, oe);
			    break;
			}
		    }
		}

		if (j == pl.lit)
		    invalidCode();
	    }
	}
    }


    int i = (8 - ni) & 7;
    c >>= i;
    lc -= i;

    while (lc > 0)
    {
	const HufDec pl = hdecod[(c << (HUF_DECBITS - lc)) & HUF_DECMASK];

	if (pl.len)
	{
	    lc -= pl.len;
	    getCode (pl.lit, rlc, c, lc, in, out, outb, oe);
	}
	else
	{
	    invalidCode();
	}
    }

    if (out - outb != no)
	notEnoughData ();
}
