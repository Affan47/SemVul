set_h(int i, float v) {
	if (!(i < 0 || i >= MAXH)) {
		h[i] = v;
	}
}
