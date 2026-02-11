parse_bars_file (const char *fname,
				  int *err)
{
    FILE *fp;
    plotbars *bars = NULL;
    char line[128];
    int ncolon = 0;
    int ndash = 0;
    int d1, d2, d3, d4;
    int n = 0;

    fp = gretl_fopen(fname, "r");
    if (fp == NULL) {
	*err = E_FOPEN;
	return NULL;
    }

#if BDEBUG > 1
    fprintf(stderr, "parse_bars_file: '%s'\n", fname);
#endif


    while (fgets(line, sizeof line, fp)) {
	if (*line == '#') {
	    continue;
	} else if (sscanf(line, "%d:%d %d:%d", &d1, &d2, &d3, &d4) == 4) {
	    ncolon++;
	} else if (sscanf(line, "%d-%d %d-%d", &d1, &d2, &d3, &d4) == 4) {
	    ndash++;
	} else {
	    break;
	}
	n++;
    }


    if (n == 0 || (ncolon == 0 && ndash == 0)) {
	*err = E_DATA;
    } else if (ncolon > 0 && ndash > 0) {
	*err = E_DATA;
    } else {
	bars = plotbars_new(n);
	if (bars == NULL) {
	    *err = E_ALLOC;
	}
    }

    if (*err == 0) {
	double x0, x1;
	int i = 0;

	rewind(fp);


	while (fgets(line, sizeof line, fp) && !*err) {
	    if (*line == '#') {
		continue;
	    }
	    if (ncolon) {
		sscanf(line, "%d:%d %d:%d", &d1, &d2, &d3, &d4);
	    } else {
		sscanf(line, "%d-%d %d-%d", &d1, &d2, &d3, &d4);
	    }
	    x0 = d1 + (d2 - 1.0) / 12;
	    x1 = d3 + (d4 - 1.0) / 12;
#if BDEBUG > 1
	    fprintf(stderr, "%.4f %.4f\n", x0, x1);
#endif
	    if (x1 < x0) {
		*err = E_DATA;
	    } else {
		bars->dx[i][0] = x0;
		bars->dx[i][1] = x1;
		i++;
	    }
	}
    }

    fclose(fp);

    if (*err == E_DATA) {
	gretl_errmsg_set(_("Dates file does not conform to the specification"));
    }

    if (*err && bars != NULL) {
	plotbars_free(bars);
	bars = NULL;
    }

    return bars;
}
