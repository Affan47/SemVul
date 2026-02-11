interp_first_last(geosurf * gs, float *bgn, float *end, Point3 f,
		       Point3 l)
{
    f[X] = bgn[X];
    f[Y] = bgn[Y];

    l[X] = end[X];
    l[Y] = end[Y];

    if (Flat) {
	f[Z] = l[Z] = gs->att[ATT_TOPO].constant;
    }
    else {
	viewcell_tri_interp(gs, Ebuf, f, 0);
	viewcell_tri_interp(gs, Ebuf, l, 0);
    }

    return;
}
