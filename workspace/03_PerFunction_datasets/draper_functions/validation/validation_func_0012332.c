outputHull(struct Map_info *Map, struct Point *P, int *hull,
	       int numPoints)
{
    struct line_pnts *Points;
    struct line_cats *Cats;
    double *tmpx, *tmpy;
    int i, pointIdx;
    double xc, yc;

    tmpx = (double *)G_malloc((numPoints + 1) * sizeof(double));
    tmpy = (double *)G_malloc((numPoints + 1) * sizeof(double));

    xc = yc = 0;
    for (i = 0; i < numPoints; i++) {
	pointIdx = hull[i];
	tmpx[i] = P[pointIdx].x;
	tmpy[i] = P[pointIdx].y;


	xc = xc + tmpx[i] / numPoints;
	yc = yc + tmpy[i] / numPoints;
    }
    tmpx[numPoints] = P[hull[0]].x;
    tmpy[numPoints] = P[hull[0]].y;

    Points = Vect_new_line_struct();
    Cats = Vect_new_cats_struct();
    Vect_copy_xyz_to_pnts(Points, tmpx, tmpy, 0, numPoints + 1);
    G_free(tmpx);
    G_free(tmpy);


    Vect_write_line(Map, GV_BOUNDARY, Points, Cats);


    Vect_reset_line(Points);
    Vect_append_point(Points, xc, yc, 0.0);
    Vect_cat_set(Cats, 1, 1);
    Vect_write_line(Map, GV_CENTROID, Points, Cats);
    Vect_destroy_line_struct(Points);

    return 0;
}
