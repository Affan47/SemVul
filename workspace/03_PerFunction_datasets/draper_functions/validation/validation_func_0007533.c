get_out_range_points(rspl *s, int *minp, int *maxp) {
	int f;

	if (s->g.fminmax_valid == 0)
		get_out_range(s, NULL, NULL);

	for (f = 0; f < s->fdi; f++) {
		if (minp != NULL)
			minp[f] = s->g.fminx[f];
		if (maxp != NULL)
			maxp[f] = s->g.fmaxx[f];
	}
}
