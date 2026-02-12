static int gap_try(int x, int y, int *run, int *saw, int along_x) {
	int n, m, i, xt, yt, ct;

	n = x + y * ntiles_x;

	if (! tile_has_diff[n]) {
		if (*saw) {
			(*run)++;
		}
		return 0;
	}
	if (! *saw || *run == 0 || *run > gaps_fill) {
		*run = 0;
		*saw = 1;
		return 0;
	}

	for (i=1; i <= *run; i++) {
		if (along_x) {
			xt = x - i;
			yt = y;
		} else {
			xt = x;
			yt = y - i;
		}

		m = xt + yt * ntiles_x;
		if (tile_tried[m]) {
			continue;
		}

		ct = copy_tiles(xt, yt, 1);
		if (ct < 0) return ct;
	}
	*run = 0;
	*saw = 1;
	return 1;
}
