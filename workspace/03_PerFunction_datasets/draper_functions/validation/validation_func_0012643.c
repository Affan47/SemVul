new_matrix_dimv(size_t dimc, const size_t dimv[])
{
	if (dimc > 1) {
		uint64_t **p = (uint64_t**)xmalloc(dimv[0] * sizeof(uint64_t*));
		for (size_t i = 0; i < dimv[0]; i++)
			p[i] = (uint64_t*)new_matrix_dimv(dimc - 1, dimv + 1);
		return p;
	} else {
		uint64_t *p = (uint64_t*)xmalloc(dimv[0] * sizeof(uint64_t));
		zero_array(p, dimv[0]);
		return p;
	}
}
