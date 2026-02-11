load_pen_width_table(FILE * td)
{
	PEN_N tp;
	PEN_W tw;
	int i;

	if (fread((void *) &tp, sizeof(tp), 1, td) != 1) {
		return (0);
	}

	if (fread((void *) &tw, sizeof(tw), 1, td) != 1) {
		return (0);
	}

	if (tp >= NUMPENS) {
		return (1);
	}

	if (tp == 0) {
		for (i = 1; i < NUMPENS; ++i)
			pt.width[i] = tw;
	} else {
		pt.width[tp] = tw;
	}

	return (1);
}
