hts_idx_load_core(hts_idx_t *idx, void *fp, int fmt)
{
	int32_t i, n, is_be;
	int is_bgzf = (fmt != HTS_FMT_BAI);
	is_be = ed_is_big();
	for (i = 0; i < idx->n; ++i) {
		bidx_t *h;
		lidx_t *l = &idx->lidx[i];
		uint32_t key;
		int j, absent;
		bins_t *p;
		h = idx->bidx[i] = kh_init(bin);
		idx_read(is_bgzf, fp, &n, 4);
		if (is_be) ed_swap_4p(&n);
		for (j = 0; j < n; ++j) {
			khint_t k;
			idx_read(is_bgzf, fp, &key, 4);
			if (is_be) ed_swap_4p(&key);
			k = kh_put(bin, h, key, &absent);
			p = &kh_val(h, k);
			if (fmt == HTS_FMT_CSI) {
				idx_read(is_bgzf, fp, &p->loff, 8);
				if (is_be) ed_swap_8p(&p->loff);
			} else p->loff = 0;
			idx_read(is_bgzf, fp, &p->n, 4);
			if (is_be) ed_swap_4p(&p->n);
			p->m = p->n;
			p->list = (hts_pair64_t*)malloc(p->m * 16);
			idx_read(is_bgzf, fp, p->list, p->n<<4);
			if (is_be) swap_bins(p);
		}
		if (fmt != HTS_FMT_CSI) {
			int j;
			idx_read(is_bgzf, fp, &l->n, 4);
			if (is_be) ed_swap_4p(&l->n);
			l->m = l->n;
			l->offset = (uint64_t*)malloc(l->n << 3);
			idx_read(is_bgzf, fp, l->offset, l->n << 3);
			if (is_be) for (j = 0; j < l->n; ++j) ed_swap_8p(&l->offset[j]);
			for (j = 1; j < l->n; ++j)
				if (l->offset[j] == 0) l->offset[j] = l->offset[j-1];
			update_loff(idx, i, 1);
		}
	}
	if (idx_read(is_bgzf, fp, &idx->n_no_coor, 8) != 8) idx->n_no_coor = 0;
	if (is_be) ed_swap_8p(&idx->n_no_coor);
}
