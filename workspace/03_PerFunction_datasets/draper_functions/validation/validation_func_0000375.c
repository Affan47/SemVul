healpix_nested_to_xy(int hp, int Nside) {
	int bighp, x, y;
	int index;
	int i;
	if (!is_power_of_two(Nside)) {
		fprintf(stderr, "healpix_xy_to_nested: Nside must be a power of two.\n");
		return -1;
	}
	bighp = hp / (Nside*Nside);
	index = hp % (Nside*Nside);
	x = y = 0;
	for (i=0; i<(8*sizeof(int)/2); i++) {
		x |= (index & 0x1) << i;
		index >>= 1;
		y |= (index & 0x1) << i;
		index >>= 1;
		if (!index) break;
	}
	return healpix_compose_xy(bighp, x, y, Nside);
}
