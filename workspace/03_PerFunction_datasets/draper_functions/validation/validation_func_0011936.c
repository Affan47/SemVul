RefLim (cra, cdec, dra, ddec, sysc, sysr, eqc, eqr, epc,
	ramin, ramax, decmin, decmax, verbose)

double	cra, cdec;
double	dra, ddec;
int	sysc, sysr;
double	eqc, eqr;
double	epc;

double	*ramin,*ramax;
double	*decmin,*decmax;
int	verbose;

{
    double ra1, ra2, ra3, ra4, dec1, dec2, dec3, dec4;
    double dec;


    ra1 = cra - dra;
    ra2 = cra + dra;


    if (ra1 < 0.0)
	ra1 = ra1 + 360.0;
    if (ra2 > 360.0)
	ra2 = ra2 - 360.0;
    ra3 = ra1;
    ra4 = ra2;


    dec1 = cdec - ddec;
    dec2 = cdec + ddec;


    if (dec1 > dec2) {
	dec = dec1;
	dec1 = dec2;
	dec2 = dec;
	}
    dec3 = dec2;
    dec4 = dec1;


    vimoswcscon (sysc, sysr, eqc, eqr, &ra1, &dec1, epc);
    vimoswcscon (sysc, sysr, eqc, eqr, &ra2, &dec2, epc);
    vimoswcscon (sysc, sysr, eqc, eqr, &ra3, &dec3, epc);
    vimoswcscon (sysc, sysr, eqc, eqr, &ra4, &dec4, epc);

    *ramin = ra1;
    if (ra3 < *ramin)
	*ramin = ra3;
    *ramax = ra2;
    if (ra4 > *ramax)
	*ramax = ra4;
    *decmin = dec1;
    if (dec4 < *decmin)
	*decmin = dec4;
    *decmax = dec2;
    if (dec3 > *decmax)
	*decmax = dec3;


    if (*decmin < -90.0) {
	*decmin = -90.0;
	*ramin = 0.0;
	*ramax = 359.99999;
	}
    if (*decmax > 90.0) {
	*decmax = 90.0;
	*ramin = 0.0;
	*ramax = 359.99999;
	}
    if (verbose) {
	char rstr1[16],rstr2[16],dstr1[16],dstr2[16];
	ra2str (rstr1, 16, *ramin, 3);
        dec2str (dstr1, 16, *decmin, 2);
	ra2str (rstr2, 16, *ramax, 3);
        dec2str (dstr2, 16, *decmax, 2);
	fprintf (stderr,"RefLim: RA: %s - %s  Dec: %s - %s\n",
		 rstr1,rstr2,dstr1,dstr2);
	}
    return;
}
