get_native_db_data_masked (const char *dbbase,
				      SERIESINFO *sinfo,
				      double **dbZ,
				      const gretl_matrix *mask)
{
    char numstr[32];
    FILE *fp;
    dbnumber x;
    int s, t, masklen;
    int err = 0;

    fp = open_binfile(dbbase, GRETL_NATIVE_DB, sinfo->offset, &err);
    if (err) {
	return err;
    }

    masklen = gretl_vector_get_length(mask);

    s = 0;
    for (t=0; t<=sinfo->nobs && !err; t++) {
	if (fread(&x, sizeof x, 1, fp) != 1) {
	    err = DB_PARSE_ERROR;
	} else if (db_row_wanted(mask, masklen, t)) {
	    sprintf(numstr, "%.7g", (double) x);
	    dbZ[1][s] = atof(numstr);
	    if (dbZ[1][s] == DBNA) {
		dbZ[1][s] = NADBL;
	    }
	    s++;
	}
    }

    fclose(fp);

    return err;
}
