get_urc_pvalue (double tau, int n, int niv, int itv,
		       gretlopt opt)
{
    char datapath[FILENAME_MAX];
    void *handle;
    double (*mackinnon_pvalue)(double, int, int, int, char *);
    double pval = NADBL;
    static int nodata;

    if (nodata) {
	return pval;
    }

    mackinnon_pvalue = get_plugin_function("mackinnon_pvalue", &handle);
    if (mackinnon_pvalue == NULL) {
	nodata = 1;
        return pval;
    }

    strcpy(datapath, gretl_lib_path());
#ifdef WIN32
    append_dir(datapath, "plugins");
#endif

    if ((opt & OPT_G) && itv == UR_CONST) {
	itv = UR_NO_CONST;
    }

    pval = (*mackinnon_pvalue)(tau, n, niv, itv, datapath);

#if ADF_DEBUG
    fprintf(stderr, "getting pval: tau=%g, n=%d, niv=%d, itv=%d: pval=%g\n",
	    tau, n, niv, itv, pval);
#endif

    close_plugin(handle);

    if (*datapath == '\0') {
	nodata = 1;
    }

    return pval;
}
