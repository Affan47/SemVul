ck_rhs_init(struct ck_rhs *hs,
    unsigned int mode,
    ck_rhs_hash_cb_t *hf,
    ck_rhs_compare_cb_t *compare,
    struct ck_malloc *m,
    unsigned long n_entries,
    unsigned long seed)
{

	if (m == NULL || m->malloc == NULL || m->free == NULL || hf == NULL)
		return false;

	hs->m = m;
	hs->mode = mode;
	hs->seed = seed;
	hs->hf = hf;
	hs->compare = compare;
	hs->load_factor = CK_RHS_DEFAULT_LOAD_FACTOR;

	hs->map = ck_rhs_map_create(hs, n_entries);
	return hs->map != NULL;
}
