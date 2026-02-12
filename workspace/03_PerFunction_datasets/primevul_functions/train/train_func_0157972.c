hufCanonicalCodeTable (Int64 hcode[HUF_ENCSIZE])
#endif
{
    Int64 n[59];


    for (int i = 0; i <= 58; ++i)
	n[i] = 0;

    for (int i = 0; i < HUF_ENCSIZE; ++i)
	n[hcode[i]] += 1;


    Int64 c = 0;

    for (int i = 58; i > 0; --i)
    {
	Int64 nc = ((c + n[i]) >> 1);
	n[i] = c;
	c = nc;
    }


    for (int i = 0; i < HUF_ENCSIZE; ++i)
    {
	int l = hcode[i];

	if (l > 0)
	    hcode[i] = l | (n[l]++ << 6);
    }
}
