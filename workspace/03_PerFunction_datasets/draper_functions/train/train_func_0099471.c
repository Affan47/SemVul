G_get_ellipsoid_parameters(double *a, double *e2)
{
    int in_stat, stat;
    char ipath[GPATH_MAX];
    struct Key_Value *proj_keys;

    proj_keys = NULL;

    G__file_name(ipath, "", PROJECTION_FILE, PERMANENT);

    if (access(ipath, 0) != 0) {
	*a = 6378137.0;
	*e2 = .006694385;
	return 0;
    }

    proj_keys = G_read_key_value_file(ipath, &in_stat);

    if (in_stat != 0) {
	G_fatal_error(_("Unable to open file %s in <%s>"),
		      PROJECTION_FILE, PERMANENT);
    }

    stat = get_ellipsoid_parameters(proj_keys, a, e2);

    G_free_key_value(proj_keys);

    return stat;
}
