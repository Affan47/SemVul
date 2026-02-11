ti_iter_destroy(ti_iter_t iter)
{
	if (iter) {
		free(iter->str.s); free(iter->off);
		free(iter);
	}
}
