void round_corners(GVJ_t * job, pointf * AF, int sides, int style, int filled)
{
    pointf *B, C[5], *D, p0, p1;
    double rbconst, d, dx, dy, t;
    int i, seg, mode, shape;
    pointf* pts;

    shape = style & SHAPE_MASK;
    if (style & DIAGONALS)
	mode = DIAGONALS;
    else if (style & SHAPE_MASK)
	mode = shape;
    else
	mode = ROUNDED;
    if (mode == CYLINDER) {
	cylinder_draw (job, AF, sides, style, filled);
	return;
    }
    B = N_NEW(4 * sides + 4, pointf);
    i = 0;


    rbconst = RBCONST;
    for (seg = 0; seg < sides; seg++) {
	p0 = AF[seg];
	if (seg < sides - 1)
	    p1 = AF[seg + 1];
	else
	    p1 = AF[0];
	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	d = sqrt(dx * dx + dy * dy);
	rbconst = MIN(rbconst, d / 3.0);
    }
    for (seg = 0; seg < sides; seg++) {
	p0 = AF[seg];
	if (seg < sides - 1)
	    p1 = AF[seg + 1];
	else
	    p1 = AF[0];
	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	d = sqrt(dx * dx + dy * dy);
	t = rbconst / d;
	if (shape == BOX3D || shape == COMPONENT)
	    t /= 3;
	else if (shape == DOGEAR)
	    t /= 2;
	if (mode != ROUNDED)
	    B[i++] = p0;
	else
	    B[i++] = interpolate_pointf(RBCURVE * t, p0, p1);
	B[i++] = interpolate_pointf(t, p0, p1);
	B[i++] = interpolate_pointf(1.0 - t, p0, p1);
	if (mode == ROUNDED)
	    B[i++] = interpolate_pointf(1.0 - RBCURVE * t, p0, p1);
    }
    B[i++] = B[0];
    B[i++] = B[1];
    B[i++] = B[2];

    switch (mode) {
    case ROUNDED:
	pts = N_GNEW(6 * sides + 2, pointf);
	i = 0;
	for (seg = 0; seg < sides; seg++) {
	    pts[i++] = B[4 * seg];
	    pts[i++] = B[4 * seg+1];
	    pts[i++] = B[4 * seg+1];
	    pts[i++] = B[4 * seg+2];
	    pts[i++] = B[4 * seg+2];
	    pts[i++] = B[4 * seg+3];
	}
	pts[i++] = pts[0];
	pts[i++] = pts[1];
	gvrender_beziercurve(job, pts+1, i-1, FALSE, FALSE, filled);
	free (pts);

#if 0
	if (filled) {
	    pointf *pts = N_GNEW(2 * sides, pointf);
		pts[j++] = B[4 * seg + 1];
		pts[j++] = B[4 * seg + 2];
	    }
	    gvrender_polygon(job, pts, 2 * sides, filled);
	    free(pts);
	    for (seg = 0; seg < sides; seg++) {
	    }
	}
	if (penc) {
	    for (seg = 0; seg < sides; seg++) {
		gvrender_polyline(job, B + 4 * seg + 1, 2);
		gvrender_beziercurve(job, B + 4 * seg + 2, 4, FALSE, FALSE, FALSE);
	    }
	}
#endif
	break;
    case DIAGONALS:

	gvrender_polygon(job, AF, sides, filled);

	for (seg = 0; seg < sides; seg++) {
#ifdef NOTDEF
	    C[0] = B[3 * seg];
	    C[1] = B[3 * seg + 3];
	    gvrender_polyline(job, C, 2);
#endif
	    C[0] = B[3 * seg + 2];
	    C[1] = B[3 * seg + 4];
	    gvrender_polyline(job, C, 2);
	}
	break;
    case DOGEAR:

	D = N_NEW(sides + 1, pointf);
	for (seg = 1; seg < sides; seg++)
	    D[seg] = AF[seg];
	D[0] = B[3 * (sides - 1) + 4];
	D[sides] = B[3 * (sides - 1) + 2];
	gvrender_polygon(job, D, sides + 1, filled);
	free(D);


	seg = sides - 1;
	C[0] = B[3 * seg + 2];
	C[1] = B[3 * seg + 4];
	C[2].x = C[1].x + (C[0].x - B[3 * seg + 3].x);
	C[2].y = C[1].y + (C[0].y - B[3 * seg + 3].y);
	gvrender_polyline(job, C + 1, 2);
	C[1] = C[2];
	gvrender_polyline(job, C, 2);
	break;
    case TAB:


	D = N_NEW(sides + 2, pointf);
	D[0] = AF[0];
	D[1] = B[2];
	D[2].x = B[2].x + (B[3].x - B[4].x) / 3;
	D[2].y = B[2].y + (B[3].y - B[4].y) / 3;
	D[3].x = B[3].x + (B[3].x - B[4].x) / 3;
	D[3].y = B[3].y + (B[3].y - B[4].y) / 3;
	for (seg = 4; seg < sides + 2; seg++)
	    D[seg] = AF[seg - 2];
	gvrender_polygon(job, D, sides + 2, filled);
	free(D);


	C[0] = B[3];
	C[1] = B[2];
	gvrender_polyline(job, C, 2);
	break;
    case FOLDER:


	D = N_NEW(sides + 3, pointf);
	D[0] = AF[0];
	D[1].x = AF[0].x - (AF[0].x - B[1].x) / 4;
	D[1].y = AF[0].y + (B[3].y - B[4].y) / 3;
	D[2].x = AF[0].x - 2 * (AF[0].x - B[1].x);
	D[2].y = D[1].y;
	D[3].x = AF[0].x - 2.25 * (AF[0].x - B[1].x);
	D[3].y = B[3].y;
	D[4].x = B[3].x;
	D[4].y = B[3].y;
	for (seg = 4; seg < sides + 3; seg++)
	    D[seg] = AF[seg - 3];
	gvrender_polygon(job, D, sides + 3, filled);
	free(D);
	break;
    case BOX3D:
	assert(sides == 4);

	D = N_NEW(sides + 2, pointf);
	D[0] = AF[0];
	D[1] = B[2];
	D[2] = B[4];
	D[3] = AF[2];
	D[4] = B[8];
	D[5] = B[10];
	gvrender_polygon(job, D, sides + 2, filled);
	free(D);


	C[0].x = B[1].x + (B[11].x - B[0].x);
	C[0].y = B[1].y + (B[11].y - B[0].y);
	C[1] = B[4];
	gvrender_polyline(job, C, 2);
	C[1] = B[8];
	gvrender_polyline(job, C, 2);
	C[1] = B[0];
	gvrender_polyline(job, C, 2);
	break;
    case COMPONENT:
	assert(sides == 4);


	D = N_NEW(sides + 8, pointf);
	D[0] = AF[0];
	D[1] = AF[1];
	D[2].x = B[3].x + (B[4].x - B[3].x);
	D[2].y = B[3].y + (B[4].y - B[3].y);
	D[3].x = D[2].x + (B[3].x - B[2].x);
	D[3].y = D[2].y + (B[3].y - B[2].y);
	D[4].x = D[3].x + (B[4].x - B[3].x);
	D[4].y = D[3].y + (B[4].y - B[3].y);
	D[5].x = D[4].x + (D[2].x - D[3].x);
	D[5].y = D[4].y + (D[2].y - D[3].y);

	D[9].x = B[6].x + (B[5].x - B[6].x);
	D[9].y = B[6].y + (B[5].y - B[6].y);
	D[8].x = D[9].x + (B[6].x - B[7].x);
	D[8].y = D[9].y + (B[6].y - B[7].y);
	D[7].x = D[8].x + (B[5].x - B[6].x);
	D[7].y = D[8].y + (B[5].y - B[6].y);
	D[6].x = D[7].x + (D[9].x - D[8].x);
	D[6].y = D[7].y + (D[9].y - D[8].y);

	D[10] = AF[2];
	D[11] = AF[3];
	gvrender_polygon(job, D, sides + 8, filled);


	C[0] = D[2];
	C[1].x = D[2].x - (D[3].x - D[2].x);
	C[1].y = D[2].y - (D[3].y - D[2].y);
	C[2].x = C[1].x + (D[4].x - D[3].x);
	C[2].y = C[1].y + (D[4].y - D[3].y);
	C[3] = D[5];
	gvrender_polyline(job, C, 4);
	C[0] = D[6];
	C[1].x = D[6].x - (D[7].x - D[6].x);
	C[1].y = D[6].y - (D[7].y - D[6].y);
	C[2].x = C[1].x + (D[8].x - D[7].x);
	C[2].y = C[1].y + (D[8].y - D[7].y);
	C[3] = D[9];
	gvrender_polyline(job, C, 4);

	free(D);
	break;

    case PROMOTER:


	D = N_NEW(sides + 5, pointf);
	D[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 + (AF[0].x - AF[1].x)/8;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)*3/2;
	D[1].x = AF[1].x + (AF[0].x - AF[1].x)/2 - (AF[0].x - AF[1].x)/4;
	D[1].y = D[0].y;
	D[2].x = D[1].x;
	D[2].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	D[3].x = D[2].x + (B[2].x - B[3].x)/2;
	D[3].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	D[4].x = D[3].x;
	D[4].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y);
	D[5].x = D[0].x;
	D[5].y = D[4].y;
	D[6].x = D[0].x;
	D[6].y = D[4].y - (B[3].y-B[4].y)/4;
	D[7].x = D[6].x + (B[2].x - B[3].x);
	D[7].y = D[6].y + (B[3].y - B[4].y)/2;
	D[8].x = D[0].x;
	D[8].y = D[0].y + (B[3].y - B[4].y)/4;
	gvrender_polygon(job, D, sides + 5, filled);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;

    case CDS:


	D = N_NEW(sides + 1, pointf);
	D[0].x = B[1].x;
	D[0].y = B[1].y - (B[3].y - B[4].y)/2;
	D[1].x = B[3].x;
	D[1].y = B[3].y - (B[3].y - B[4].y)/2;
	D[2].x = AF[2].x;
	D[2].y = AF[2].y + (B[3].y - B[4].y)/2;
	D[3].x = B[1].x;
	D[3].y = AF[2].y + (B[3].y - B[4].y)/2;
	D[4].y = AF[0].y - (AF[0].y - AF[3].y)/2;
	D[4].x = AF[0].x;

	gvrender_polygon(job, D, sides + 1, filled);
	free(D);

	break;

    case TERMINATOR:


	D = N_NEW(sides + 4, pointf);
	D[0].x = AF[1].x + (AF[0].x-AF[1].x)/2 + (B[2].x-B[3].x)/4;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	D[1].x = D[0].x;
	D[1].y = D[0].y + (B[3].y-B[4].y)/2;
	D[2].x = D[1].x + (B[2].x-B[3].x)/2;
	D[2].y = D[1].y;
	D[3].x = D[2].x;
	D[3].y = D[2].y + (B[3].y-B[4].y)/2;
	D[4].x = AF[1].x + (AF[0].x-AF[1].x)/2 - (B[2].x-B[3].x)*3/4;
	D[4].y = D[3].y;
	D[5].x = D[4].x;
	D[5].y = D[2].y;
	D[6].x = AF[1].x + (AF[0].x-AF[1].x)/2 - (B[2].x-B[3].x)/4;
	D[6].y = D[1].y;
	D[7].x = D[6].x;
	D[7].y = D[0].y;
	gvrender_polygon(job, D, sides + 4, filled);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;

    case UTR:


	D = N_NEW(sides + 2, pointf);
	D[0].x = AF[1].x + (AF[0].x-AF[1].x)/2 + (B[2].x-B[3].x)*3/4;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	D[1].x = D[0].x;
	D[1].y = D[0].y + (B[3].y-B[4].y)/4;
	D[2].x = AF[1].x + (AF[0].x-AF[1].x)/2 + (B[2].x-B[3].x)/4;
	D[2].y = D[1].y + (B[3].y-B[4].y)/2;
	D[3].x = AF[1].x + (AF[0].x-AF[1].x)/2 - (B[2].x-B[3].x)/4;
	D[3].y = D[2].y;
	D[4].x = AF[1].x + (AF[0].x-AF[1].x)/2 - (B[2].x-B[3].x)*3/4;
	D[4].y = D[1].y;
	D[5].x = D[4].x;
	D[5].y = D[0].y;
	gvrender_polygon(job, D, sides + 2, filled);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;
    case PRIMERSITE:


	D = N_NEW(sides + 1, pointf);
	D[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 + (B[2].x-B[3].x);
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/4;
	D[1].x = D[0].x - (B[2].x-B[3].x);
	D[1].y = D[0].y + (B[3].y-B[4].y);
	D[2].x = D[1].x;
	D[2].y = D[0].y + (B[3].y-B[4].y)/2;
	D[3].x = AF[1].x + (AF[0].x - AF[1].x)/2 - (AF[0].x - AF[1].x)/4;
	D[3].y = D[2].y;
	D[4].x = D[3].x;
	D[4].y = D[0].y;
	gvrender_polygon(job, D, sides + 1, filled);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;
    case RESTRICTIONSITE:


	D = N_NEW(sides + 4, pointf);
	D[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 + (AF[0].x - AF[1].x)/8 + (B[2].x-B[3].x)/2;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/4;
	D[1].x = AF[1].x + (AF[0].x - AF[1].x)/2 - (AF[0].x - AF[1].x)/8;
	D[1].y = D[0].y;
	D[2].x = D[1].x;
	D[2].y = D[1].y + (B[3].y-B[4].y)/2;
	D[3].x = D[2].x - (B[2].x-B[3].x)/2;
	D[3].y = D[2].y;
	D[4].x = D[3].x;
	D[4].y = AF[2].y + (AF[1].y - AF[2].y)/2 - (B[3].y-B[4].y)/4;
	D[5].x = D[0].x - (B[2].x-B[3].x)/2;
	D[5].y = D[4].y;
	D[6].x = D[5].x;
	D[6].y = D[5].y - (B[3].y-B[4].y)/2;
	D[7].x = D[0].x;
	D[7].y = D[6].y;
	gvrender_polygon(job, D, sides + 4, filled);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = D[4].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);


	C[0].x = D[7].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;
    case FIVEPOVERHANG:


	D = N_NEW(sides, pointf);
	D[0].x = AF[1].x;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/8;
	D[1].x = D[0].x + 2*(B[2].x-B[3].x);
	D[1].y = D[0].y;
	D[2].x = D[1].x;
	D[2].y = D[1].y + (B[3].y-B[4].y)/2;
	D[3].x = D[0].x;
	D[3].y = D[2].y;
	gvrender_polygon(job, D, sides, filled);


	free(D);
	D = N_NEW(sides, pointf);
	D[0].x = AF[1].x + (B[2].x-B[3].x);
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 - (B[3].y-B[4].y)*5/8;
	D[1].x = D[0].x + (B[2].x-B[3].x);
	D[1].y = D[0].y;
	D[2].x = D[1].x;
	D[2].y = D[1].y + (B[3].y-B[4].y)/2;
	D[3].x = D[0].x;
	D[3].y = D[2].y;
	gvrender_polygon(job, D, sides, filled);


	C[0].x = D[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;
    case THREEPOVERHANG:


	D = N_NEW(sides, pointf);
	D[0].x = AF[0].x;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/8;
	D[1].x = D[0].x;
	D[1].y = D[0].y + (B[3].y-B[4].y)/2;
	D[2].x = D[1].x - 2*(B[3].y-B[4].y);
	D[2].y = D[1].y;
	D[3].x = D[2].x;
	D[3].y = D[0].y;
	gvrender_polygon(job, D, sides, filled);


	free(D);
	D = N_NEW(sides, pointf);
	D[0].x = AF[0].x - (B[2].x-B[3].x);
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 - (B[3].y-B[4].y)*5/8;
	D[1].x = D[0].x;
	D[1].y = D[0].y + (B[3].y-B[4].y)/2;
	D[2].x = D[1].x - (B[3].y-B[4].y);
	D[2].y = D[1].y;
	D[3].x = D[2].x;
	D[3].y = D[0].y;
	gvrender_polygon(job, D, sides, filled);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = D[3].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;
    case NOVERHANG:


	D = N_NEW(sides, pointf);
	D[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 - (B[2].x-B[3].x)*9/8;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/8;
	D[1].x = D[0].x + (B[2].x-B[3].x);
	D[1].y = D[0].y;
	D[2].x = D[1].x;
	D[2].y = D[1].y + (B[3].y-B[4].y)/2;
	D[3].x = D[0].x;
	D[3].y = D[2].y;
	gvrender_polygon(job, D, sides, filled);


	free(D);
	D = N_NEW(sides, pointf);
	D[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 - (B[2].x-B[3].x)*9/8;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 - (B[3].y-B[4].y)*5/8;
	D[1].x = D[0].x + (B[2].x-B[3].x);
	D[1].y = D[0].y;
	D[2].x = D[1].x;
	D[2].y = D[1].y + (B[3].y-B[4].y)/2;
	D[3].x = D[0].x;
	D[3].y = D[2].y;
	gvrender_polygon(job, D, sides, filled);


	free(D);
	D = N_NEW(sides, pointf);
	D[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 + (B[2].x-B[3].x)/8;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 - (B[3].y-B[4].y)*5/8;
	D[1].x = D[0].x + (B[2].x-B[3].x);
	D[1].y = D[0].y;
	D[2].x = D[1].x;
	D[2].y = D[1].y + (B[3].y-B[4].y)/2;
	D[3].x = D[0].x;
	D[3].y = D[2].y;
	gvrender_polygon(job, D, sides, filled);


	free(D);
	D = N_NEW(sides, pointf);
	D[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 + (B[2].x-B[3].x)/8;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/8;
	D[1].x = D[0].x + (B[2].x-B[3].x);
	D[1].y = D[0].y;
	D[2].x = D[1].x;
	D[2].y = D[1].y + (B[3].y-B[4].y)/2;
	D[3].x = D[0].x;
	D[3].y = D[2].y;
	gvrender_polygon(job, D, sides, filled);


	C[0].x = D[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);


	C[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 - (B[2].x-B[3].x)*9/8;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[1].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;
    case ASSEMBLY:


	D = N_NEW(sides, pointf);
	D[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 - (B[2].x-B[3].x);
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/8;
	D[1].x = D[0].x + 2*(B[2].x-B[3].x);
	D[1].y = D[0].y;
	D[2].x = D[1].x;
	D[2].y = D[1].y + (B[3].y-B[4].y)/2;
	D[3].x = D[0].x;
	D[3].y = D[2].y;
	gvrender_polygon(job, D, sides, filled);


	free(D);
	D = N_NEW(sides, pointf);
	D[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 - (B[2].x-B[3].x);
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 - (B[3].y-B[4].y)*5/8;
	D[1].x = D[0].x + 2*(B[2].x-B[3].x);
	D[1].y = D[0].y;
	D[2].x = D[1].x;
	D[2].y = D[1].y + (B[3].y-B[4].y)/2;
	D[3].x = D[0].x;
	D[3].y = D[2].y;
	gvrender_polygon(job, D, sides, filled);


	C[0].x = D[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = D[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;
    case SIGNATURE:


	D = N_NEW(sides, pointf);
	D[0].x = AF[0].x;
	D[0].y = B[1].y - (B[3].y - B[4].y)/2;
	D[1].x = B[3].x;
	D[1].y = B[3].y - (B[3].y - B[4].y)/2;
	D[2].x = AF[2].x;
	D[2].y = AF[2].y + (B[3].y - B[4].y)/2;
	D[3].x = AF[0].x;
	D[3].y = AF[2].y + (B[3].y - B[4].y)/2;
	gvrender_polygon(job, D, sides, filled);


	C[0].x = AF[1].x + (B[2].x-B[3].x)/4;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/8;
	C[1].x = C[0].x + (B[2].x-B[3].x)/4;
	C[1].y = C[0].y - (B[3].y-B[4].y)/4;
	gvrender_polyline(job, C, 2);


	C[0].x = AF[1].x + (B[2].x-B[3].x)/4;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 - (B[3].y-B[4].y)/8;
	C[1].x = C[0].x + (B[2].x-B[3].x)/4;
	C[1].y = C[0].y + (B[3].y-B[4].y)/4;
	gvrender_polyline(job, C, 2);


	C[0].x = AF[1].x + (B[2].x-B[3].x)/4;
	C[0].y = AF[2].y + (B[3].y-B[4].y)*3/4;
	C[1].x = AF[0].x - (B[2].x-B[3].x)/4;
	C[1].y = C[0].y;
	gvrender_polyline(job, C, 2);
	free(D);

	break;
    case INSULATOR:


	D = N_NEW(sides, pointf);
	D[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 + (B[2].x-B[3].x)/2;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[2].x-B[3].x)/2;
	D[1].x = D[0].x;
	D[1].y = AF[2].y + (AF[1].y - AF[2].y)/2 - (B[2].x-B[3].x)/2;
	D[2].x = AF[1].x + (AF[0].x - AF[1].x)/2 - (B[2].x-B[3].x)/2;
	D[2].y = D[1].y;
	D[3].x = D[2].x;
	D[3].y = D[0].y;
	gvrender_polygon(job, D, sides, filled);
	free(D);


	C[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 + (B[2].x-B[3].x)*3/4;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[2].x-B[3].x)*3/4;
	C[1].x = C[0].x;
	C[1].y = AF[2].y + (AF[1].y - AF[2].y)/2 - (B[2].x-B[3].x)*3/4;
	C[2].x = AF[1].x + (AF[0].x - AF[1].x)/2 - (B[2].x-B[3].x)*3/4;
	C[2].y = C[1].y;
	C[3].x = C[2].x;
	C[3].y = C[0].y;
	C[4] = C[0];
	gvrender_polyline(job, C, 5);


	C[0].x = AF[1].x + (AF[0].x - AF[1].x)/2 + (B[2].x-B[3].x)*3/4;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[1].x + (AF[0].x - AF[1].x)/2 - (B[2].x-B[3].x)*3/4;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);

	break;
    case RIBOSITE:


	D = N_NEW(sides + 12, pointf);
	D[0].x = AF[1].x + (AF[0].x-AF[1].x)/2 + (B[2].x-B[3].x)/4;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/2;
	D[1].x = D[0].x;
	D[1].y = D[0].y + (B[3].y-B[4].y)/8;
	D[2].x = D[0].x - (B[2].x-B[3].x)/8;
	D[2].y = D[1].y + (B[3].y-B[4].y)/8;
	D[3].x = D[0].x;
	D[3].y = D[2].y + (B[3].y-B[4].y)/8;
	D[4].x = D[0].x;
	D[4].y = D[3].y + (B[3].y-B[4].y)/8;
	D[5].x = D[2].x;
	D[5].y = D[4].y;
	D[6].x = AF[1].x + (AF[0].x - AF[1].x)/2;
	D[6].y = D[3].y;
	D[7].x = D[6].x - (B[2].x-B[3].x)/8;
	D[7].y = D[5].y;
	D[8].x = D[7].x - (B[2].x-B[3].x)/8;
	D[8].y = D[7].y;
	D[9].x = D[8].x;
	D[9].y = D[3].y;
	D[10].x = D[8].x + (B[2].x-B[3].x)/8;
	D[10].y = D[2].y;
	D[11].x = D[8].x;
	D[11].y = D[1].y;
	D[12].x = D[8].x;
	D[12].y = D[0].y;
	D[13].x = D[10].x;
	D[13].y = D[12].y;
	D[14].x = D[6].x;
	D[14].y = D[1].y;
	D[15].x = D[2].x;
	D[15].y = D[0].y;
	gvrender_polygon(job, D, sides + 12, filled);


	C[0].x = D[14].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = C[0].x;
	C[1].y = C[0].y + (B[3].y-B[4].y)/8;
	gvrender_polyline(job, C, 2);


	C[0].x = D[14].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/4;
	C[1].x = C[0].x;
	C[1].y = C[0].y + (B[3].y-B[4].y)/8;
	gvrender_polyline(job, C, 2);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;
    case RNASTAB:


	D = N_NEW(sides + 4, pointf);
	D[0].x = AF[1].x + (AF[0].x-AF[1].x)/2 + (B[2].x-B[3].x)/8;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/2;
	D[1].x = D[0].x + (B[2].x-B[3].x)/8;
	D[1].y = D[0].y + (B[3].y-B[4].y)/8;
	D[2].x = D[1].x;
	D[2].y = D[1].y + (B[3].y-B[4].y)/4;
	D[3].x = D[0].x;
	D[3].y = D[2].y + (B[3].y-B[4].y)/8;
	D[4].x = D[3].x - (B[2].x-B[3].x)/4;
	D[4].y = D[3].y;
	D[5].x = D[4].x - (B[2].x-B[3].x)/8;
	D[5].y = D[2].y;
	D[6].x = D[5].x;
	D[6].y = D[1].y;
	D[7].x = D[4].x;
	D[7].y = D[0].y;
	gvrender_polygon(job, D, sides + 4, filled);


	C[0].x = AF[1].x + (AF[0].x - AF[1].x)/2;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = C[0].x;
	C[1].y = C[0].y + (B[3].y-B[4].y)/8;
	gvrender_polyline(job, C, 2);


	C[0].x = AF[1].x + (AF[0].x - AF[1].x)/2;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/4;
	C[1].x = C[0].x;
	C[1].y = C[0].y + (B[3].y-B[4].y)/8;
	gvrender_polyline(job, C, 2);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;
    case PROTEASESITE:


	D = N_NEW(sides + 12, pointf);
	D[0].x = AF[1].x + (AF[0].x-AF[1].x)/2 + (B[2].x-B[3].x)/4;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/2;
	D[1].x = D[0].x;
	D[1].y = D[0].y + (B[3].y-B[4].y)/8;
	D[2].x = D[0].x - (B[2].x-B[3].x)/8;
	D[2].y = D[1].y + (B[3].y-B[4].y)/8;
	D[3].x = D[0].x;
	D[3].y = D[2].y + (B[3].y-B[4].y)/8;
	D[4].x = D[0].x;
	D[4].y = D[3].y + (B[3].y-B[4].y)/8;
	D[5].x = D[2].x;
	D[5].y = D[4].y;
	D[6].x = AF[1].x + (AF[0].x - AF[1].x)/2;
	D[6].y = D[3].y;
	D[7].x = D[6].x - (B[2].x-B[3].x)/8;
	D[7].y = D[5].y;
	D[8].x = D[7].x - (B[2].x-B[3].x)/8;
	D[8].y = D[7].y;
	D[9].x = D[8].x;
	D[9].y = D[3].y;
	D[10].x = D[8].x + (B[2].x-B[3].x)/8;
	D[10].y = D[2].y;
	D[11].x = D[8].x;
	D[11].y = D[1].y;
	D[12].x = D[8].x;
	D[12].y = D[0].y;
	D[13].x = D[10].x;
	D[13].y = D[12].y;
	D[14].x = D[6].x;
	D[14].y = D[1].y;
	D[15].x = D[2].x;
	D[15].y = D[0].y;
	gvrender_polygon(job, D, sides + 12, filled);


	C[0] = D[14];
	C[1].x = C[0].x;
	C[1].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	gvrender_polyline(job, C, 2);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;
    case PROTEINSTAB:


	D = N_NEW(sides + 4, pointf);
	D[0].x = AF[1].x + (AF[0].x-AF[1].x)/2 + (B[2].x-B[3].x)/8;
	D[0].y = AF[2].y + (AF[1].y - AF[2].y)/2 + (B[3].y-B[4].y)/2;
	D[1].x = D[0].x + (B[2].x-B[3].x)/8;
	D[1].y = D[0].y + (B[3].y-B[4].y)/8;
	D[2].x = D[1].x;
	D[2].y = D[1].y + (B[3].y-B[4].y)/4;
	D[3].x = D[0].x;
	D[3].y = D[2].y + (B[3].y-B[4].y)/8;
	D[4].x = D[3].x - (B[2].x-B[3].x)/4;
	D[4].y = D[3].y;
	D[5].x = D[4].x - (B[2].x-B[3].x)/8;
	D[5].y = D[2].y;
	D[6].x = D[5].x;
	D[6].y = D[1].y;
	D[7].x = D[4].x;
	D[7].y = D[0].y;
	gvrender_polygon(job, D, sides + 4, filled);


	C[0].x = AF[1].x + (AF[0].x - AF[1].x)/2;
	C[0].y = D[0].y;
	C[1].x = C[0].x;
	C[1].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	gvrender_polyline(job, C, 2);


	C[0].x = AF[1].x;
	C[0].y = AF[2].y + (AF[1].y - AF[2].y)/2;
	C[1].x = AF[0].x;
	C[1].y = AF[2].y + (AF[0].y - AF[3].y)/2;
	gvrender_polyline(job, C, 2);
	free(D);

	break;

    case RPROMOTER:


	D = N_NEW(sides + 5, pointf);
	D[0].x = B[1].x - (B[2].x - B[3].x)/2;
	D[0].y = B[1].y - (B[3].y - B[4].y)/2;
	D[1].x = B[3].x;
	D[1].y = B[3].y - (B[3].y - B[4].y)/2;
	D[2].x = AF[2].x;
	D[2].y = AF[2].y;
	D[3].x = B[2].x + (B[2].x - B[3].x)/2;
	D[3].y = AF[2].y;
	D[4].x = B[2].x + (B[2].x - B[3].x)/2;
	D[4].y = AF[2].y + (B[3].y - B[4].y)/2;
	D[5].x = B[1].x - (B[2].x - B[3].x)/2;
	D[5].y = AF[2].y + (B[3].y - B[4].y)/2;
	D[6].x = B[1].x - (B[2].x - B[3].x)/2;
	D[6].y = AF[3].y;
	D[7].y = AF[0].y - (AF[0].y - AF[3].y)/2;
	D[7].x = AF[0].x;
	D[8].y = AF[0].y;
	D[8].x = B[1].x - (B[2].x - B[3].x)/2;

	gvrender_polygon(job, D, sides + 5, filled);
	free(D);
	break;

    case RARROW:


	D = N_NEW(sides + 3, pointf);
	D[0].x = B[1].x - (B[2].x - B[3].x)/2;
	D[0].y = B[1].y - (B[3].y - B[4].y)/2;
	D[1].x = B[3].x;
	D[1].y = B[3].y - (B[3].y - B[4].y)/2;
	D[2].x = AF[2].x;
	D[2].y = AF[2].y + (B[3].y - B[4].y)/2;
	D[3].x = B[1].x - (B[2].x - B[3].x)/2;
	D[3].y = AF[2].y + (B[3].y - B[4].y)/2;
	D[4].x = B[1].x - (B[2].x - B[3].x)/2;
	D[4].y = AF[3].y;
	D[5].y = AF[0].y - (AF[0].y - AF[3].y)/2;
	D[5].x = AF[0].x;
	D[6].y = AF[0].y;
	D[6].x = B[1].x - (B[2].x - B[3].x)/2;

	gvrender_polygon(job, D, sides + 3, filled);
	free(D);
	break;

    case LARROW:


	D = N_NEW(sides + 3, pointf);
	D[0].x = AF[0].x;
	D[0].y = AF[0].y - (B[3].y-B[4].y)/2;
	D[1].x = B[2].x + (B[2].x - B[3].x)/2;
	D[1].y = AF[0].y - (B[3].y-B[4].y)/2;
	D[2].x = B[2].x + (B[2].x - B[3].x)/2;
	D[2].y = B[2].y;
	D[3].x = AF[1].x;
	D[3].y = AF[1].y - (AF[1].y - AF[2].y)/2;
	D[4].x = B[2].x + (B[2].x - B[3].x)/2;
	D[4].y = AF[2].y;
	D[5].y = AF[2].y + (B[3].y-B[4].y)/2;
	D[5].x = B[2].x + (B[2].x - B[3].x)/2;
	D[6].y = AF[3].y + (B[3].y - B[4].y)/2;
	D[6].x = AF[0].x;

	gvrender_polygon(job, D, sides + 3, filled);
	free(D);
	break;

    case LPROMOTER:


	D = N_NEW(sides + 5, pointf);
	D[0].x = AF[0].x;
	D[0].y = AF[0].y - (B[3].y-B[4].y)/2;
	D[1].x = B[2].x + (B[2].x - B[3].x)/2;
	D[1].y = AF[0].y - (B[3].y-B[4].y)/2;
	D[2].x = B[2].x + (B[2].x - B[3].x)/2;
	D[2].y = B[2].y;
	D[3].x = AF[1].x;
	D[3].y = AF[1].y - (AF[1].y - AF[2].y)/2;
	D[4].x = B[2].x + (B[2].x - B[3].x)/2;
	D[4].y = AF[2].y;
	D[5].y = AF[2].y + (B[3].y-B[4].y)/2;
	D[5].x = B[2].x + (B[2].x - B[3].x)/2;
	D[6].y = AF[3].y + (B[3].y - B[4].y)/2;
	D[6].x = B[1].x - (B[2].x - B[3].x)/2;
	D[7].x = B[1].x - (B[2].x - B[3].x)/2;
	D[7].y = AF[3].y;
	D[8].x = AF[3].x;
	D[8].y = AF[3].y;

	gvrender_polygon(job, D, sides + 5, filled);
	free(D);
	break;
    }
