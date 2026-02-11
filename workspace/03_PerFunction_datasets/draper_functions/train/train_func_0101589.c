setRatio(graph_t * g)
{
    char *p, c;
    double ratio;

    if ((p = agget(g, "ratio")) && ((c = p[0]))) {
	switch (c) {
	case 'a':
	    if (streq(p, "auto"))
		GD_drawing(g)->ratio_kind = R_AUTO;
	    break;
	case 'c':
	    if (streq(p, "compress"))
		GD_drawing(g)->ratio_kind = R_COMPRESS;
	    break;
	case 'e':
	    if (streq(p, "expand"))
		GD_drawing(g)->ratio_kind = R_EXPAND;
	    break;
	case 'f':
	    if (streq(p, "fill"))
		GD_drawing(g)->ratio_kind = R_FILL;
	    break;
	default:
	    ratio = atof(p);
	    if (ratio > 0.0) {
		GD_drawing(g)->ratio_kind = R_VALUE;
		GD_drawing(g)->ratio = ratio;
	    }
	    break;
	}
    }
}
