name_xprod_term (char *vname, int vi, int vj,
			     int di, const DATASET *dset)
{
    const char *si = dset->varname[vi];
    const char *sj = dset->varname[vj];
    int ilen = strlen(si);
    int jlen = strlen(sj);
    int totlen = ilen + jlen + 2;
    char numstr[32];

    sprintf(numstr, "%d", di);
    totlen += strlen(numstr);

    if (totlen > VNAMELEN - 1) {
	int decr = totlen - (VNAMELEN - 1);

	while (decr > 0) {
	    if (ilen > jlen) {
		ilen--;
	    } else {
		jlen--;
	    }
	    decr--;
	}
    }

    sprintf(vname, "%.*s_%.*s_%s", ilen, si, jlen, sj, numstr);
}
