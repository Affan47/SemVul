vector_sdiv_double(double* v, double r, size_t n) {
	size_t i;
	if (r == 0)
		return;
	r = 1.0 / r;
	for (i = 0; i < n; i++)
		v[i] *= r;
}
