dtm_block_2_wdl_block(dtm_block_t *g, wdl_block_t *w, size_t n)
{
	int width = 2;
	int shifting;
	size_t i;
	int j;
	unsigned int x ,y;
	 dtm_t *s = g->p_arr;
	unit_t *d = w->p_arr;

	for (i = 0, y = 0; i < n; i++) {
		j =  i & 3;
		x = dtm2WDL(s[i]);
		shifting = j * width;
		y |= (x << shifting);

		if (j == 3) {
			d[i/WDL_entries_per_unit] = (unit_t) y;
			y = 0;
		}
	}

	if (0 != (n & 3)) {
		d[(n-1)/WDL_entries_per_unit] = (unit_t) y;
		y = 0;
	}

	return;
}
