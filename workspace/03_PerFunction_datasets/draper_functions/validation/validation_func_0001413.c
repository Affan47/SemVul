mag_g_pop_simple(mag_t *g, float max_cov, float max_frac, int aggressive)
{
	int64_t i;
	for (i = 0; i < g->v.n; ++i) {
		mag_vh_pop_simple(g, i<<1|0, max_cov, max_frac, aggressive);
		mag_vh_pop_simple(g, i<<1|1, max_cov, max_frac, aggressive);
	}
	mag_g_merge(g, 0);
}
