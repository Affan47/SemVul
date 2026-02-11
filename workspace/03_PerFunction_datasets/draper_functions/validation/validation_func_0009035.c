htable_foreach_remove(htable_t *hx, ckeyval_rm_fn_t fn, void *data)
{
	unsigned *hp, *end;
	size_t i, n, nr;

	htable_check(hx);

	end = &hx->kset.hashes[hx->kset.size];
	hash_refcnt_inc(HASH(hx));

	for (i = n = nr = 0, hp = hx->kset.hashes; hp != end; i++, hp++) {
		if (HASH_IS_REAL(*hp)) {
			bool r = (*fn)(hx->kset.keys[i],
				deconstify_pointer(hx->values[i]), data);
			n++;
			if (r) {
				nr++;
				hash_keyset_erect_tombstone(&hx->kset, i);
				hx->stamp++;
			}
		}
	}

	g_assert(n == hx->kset.items);
	g_assert(nr <= hx->kset.items);

	hash_refcnt_dec(HASH(hx));

	hx->kset.items -= nr;

	if (nr != 0)
		hash_resize_as_needed(HASH(hx));

	return nr;
}
