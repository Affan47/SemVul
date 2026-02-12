static int grow_islands(void) {
	int x, y, n, run;
	int diffs = 0, ct;


	for (y=0; y < ntiles_y; y++) {
		run = 0;
		for (x=0; x <= ntiles_x - 2; x++) {
			ct = island_try(x, y, x+1, y, &run);
			if (ct < 0) return ct;
		}
	}

	for (y=0; y < ntiles_y; y++) {
		run = 0;
		for (x = ntiles_x - 1; x >= 1; x--) {
			ct = island_try(x, y, x-1, y, &run);
			if (ct < 0) return ct;
		}
	}
	for (n=0; n < ntiles; n++) {
		if (tile_has_diff[n]) {
			diffs++;
		}
	}
	return diffs;
}
