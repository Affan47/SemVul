tdb_next_hash_chain(struct tdb_context *tdb, uint32_t *chain)
{
	uint32_t h = *chain;
	if (tdb->map_ptr) {
		for (;h < tdb->header.hash_size;h++) {
			if (0 != *(uint32_t *)(TDB_HASH_TOP(h) + (unsigned char *)tdb->map_ptr)) {
				break;
			}
		}
	} else {
		uint32_t off=0;
		for (;h < tdb->header.hash_size;h++) {
			if (tdb_ofs_read(tdb, TDB_HASH_TOP(h), &off) != 0 || off != 0) {
				break;
			}
		}
	}
	(*chain) = h;
}
