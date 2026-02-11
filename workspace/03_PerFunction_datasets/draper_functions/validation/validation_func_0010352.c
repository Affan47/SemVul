Vedit_snap_line(struct Map_info *Map, struct Map_info **BgMap,
		    int nbgmaps, int line, struct line_pnts *Points,
		    double thresh, int to_vertex)
{
    int i, npoints, node, rewrite;
    double *x, *y, *z;

    struct line_cats *Cats;

    Cats = Vect_new_cats_struct();

    G_debug(3, "Vedit_snap_line(): thresh=%g, to_vertex=%d", thresh,
	    to_vertex);

    if (line > 0 && !Vect_line_alive(Map, line))
	return -1;

    npoints = Points->n_points;
    x = Points->x;
    y = Points->y;
    z = Points->z;

    rewrite = 0;
    for (node = 0; node < npoints; node++) {
	if ((node > 0 && node < npoints - 1) && !to_vertex)
	    continue;

	if (Vedit_snap_point(Map, line, &x[node], &y[node], &z[node], thresh,
			     to_vertex)) {
	    rewrite = 1;
	}
	else {

	    for (i = 0; i < nbgmaps; i++) {
		if (Vedit_snap_point
		    (BgMap[i], -1, &x[node], &y[node], &z[node], thresh,
		     to_vertex)) {
		    rewrite = 1;
		    break;
		}
	    }
	}
    }


    if (!rewrite &&
	Vect_points_distance(x[0], y[0], z[0],
			     x[npoints - 1], y[npoints - 1], z[npoints - 1],
			     WITHOUT_Z) <= thresh) {
	x[npoints - 1] = x[0];
	y[npoints - 1] = y[0];
	z[npoints - 1] = z[0];

	rewrite = 1;
    }

    G_debug(3, "Vedit_snap_line(): line=%d, snapped=%d", line, rewrite);

    Vect_destroy_cats_struct(Cats);

    return rewrite;
}
