read_points(struct Map_info *In, double ***coordinate, double dsize)
{
    int line, nlines, npoints, ltype, i = 0;
    double **xySites;
    static struct line_pnts *Points = NULL;

    if (!Points)
	Points = Vect_new_line_struct();


    npoints = Vect_get_num_primitives(In, GV_POINT);
    xySites = (double **)G_calloc(npoints, sizeof(double *));

    nlines = Vect_get_num_lines(In);

    for (line = 1; line <= nlines; line++) {
	ltype = Vect_read_line(In, Points, NULL, line);
	if (!(ltype & GV_POINT))
	    continue;

	xySites[i] = (double *)G_calloc((size_t) 2, sizeof(double));

	xySites[i][0] = Points->x[0];
	xySites[i][1] = Points->y[0];
	i++;
    }

    *coordinate = xySites;

    return (npoints);
}
