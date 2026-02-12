static boolean poly_inside(inside_t * inside_context, pointf p)
{
    static node_t *lastn;
    static polygon_t *poly;
    static int last, outp, sides;
    static pointf O;
    static pointf *vertex;
    static double xsize, ysize, scalex, scaley, box_URx, box_URy;

    int i, i1, j, s;
    pointf P, Q, R;
    boxf *bp;
    node_t *n;

    if (!inside_context) {
	lastn = NULL;
	return FALSE;
    }

    bp = inside_context->s.bp;
    n = inside_context->s.n;
    P = ccwrotatepf(p, 90 * GD_rankdir(agraphof(n)));


    if (bp) {
	boxf bbox = *bp;
	return INSIDE(P, bbox);
    }

    if (n != lastn) {
	double n_width, n_height;
	poly = (polygon_t *) ND_shape_info(n);
	vertex = poly->vertices;
	sides = poly->sides;

	if (poly->option & FIXEDSHAPE) {
	   boxf bb = polyBB(poly);
	    n_width = bb.UR.x - bb.LL.x;
	    n_height = bb.UR.y - bb.LL.y;

	    if (GD_flip(agraphof(n))) {
		ysize = n_width;
		xsize = n_height;
	    } else {
		xsize = n_width;
		ysize = n_height;
	    }
	} else {

	    if (GD_flip(agraphof(n))) {
		ysize = ND_lw(n) + ND_rw(n);
		xsize = ND_ht(n);
	    } else {
		xsize = ND_lw(n) + ND_rw(n);
		ysize = ND_ht(n);
	    }
	    n_width = POINTS(ND_width(n));
	    n_height = POINTS(ND_height(n));
	}


	if (xsize == 0.0)
	    xsize = 1.0;
	if (ysize == 0.0)
	    ysize = 1.0;
	scalex = n_width / xsize;
	scaley = n_height / ysize;
	box_URx = n_width / 2.0;
	box_URy = n_height / 2.0;


	outp = (poly->peripheries - 1) * sides;
	if (outp < 0)
	    outp = 0;
	lastn = n;
    }


    P.x *= scalex;
    P.y *= scaley;


    if ((fabs(P.x) > box_URx) || (fabs(P.y) > box_URy))
	return FALSE;


    if (sides <= 2)
	return (hypot(P.x / box_URx, P.y / box_URy) < 1.);


    i = last % sides;
    i1 = (i + 1) % sides;
    Q = vertex[i + outp];
    R = vertex[i1 + outp];
    if (!(same_side(P, O, Q, R)))
	return FALSE;

    if ((s = same_side(P, Q, R, O)) && (same_side(P, R, O, Q)))
	return TRUE;

    for (j = 1; j < sides; j++) {
	if (s) {
	    i = i1;
	    i1 = (i + 1) % sides;
	} else {
	    i1 = i;
	    i = (i + sides - 1) % sides;
	}
	if (!(same_side(P, O, vertex[i + outp], vertex[i1 + outp]))) {
	    last = i;
	    return FALSE;
	}
    }

    last = i;
    return TRUE;
}
