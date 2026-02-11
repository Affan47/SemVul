gp_set_non_point_info (gnuplot_info *gi,
				  const int *list,
				  const DATASET *dset,
				  gretlopt opt)
{
    const char *s = get_optval_string(GNUPLOT, opt);
    int withval = W_POINTS;
    int i, imax = gi->withlist[0];

    if (opt == OPT_O) {
	withval = W_LINES;
    } else if (opt == OPT_M) {
	withval = W_IMPULSES;
    } else if (opt == OPT_P) {
	withval = W_LP;
    }

    if (s == NULL) {

	for (i=1; i<=imax; i++) {
	    if (gi->withlist[i] == W_POINTS) {
		gi->withlist[i] = withval;
	    }
	}
    } else if (strchr(s, ',') != NULL) {

	gchar **strs = g_strsplit(s, ",", 0);
	int j;

	for (j=0; strs[j]!=NULL; j++) {
	    i = gp_list_pos(strs[j], list, dset);
	    if (i > 0 && i <= imax) {
		gi->withlist[i] = withval;
	    }
	}
	g_strfreev(strs);
    } else {

	i = gp_list_pos(s, list, dset);
	if (i > 0 && i <= imax) {
	    gi->withlist[i] = withval;
	}
    }

    return 0;
}
