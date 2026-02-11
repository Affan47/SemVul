add_to_subhash(struct tdb_context *tdb, tdb_off_t subhash,
				     unsigned hash_used, tdb_off_t val)
{
	tdb_off_t off = (val & TDB_OFF_MASK), *group;
	struct hash_info h;
	unsigned int gnum;

	h.hash_used = hash_used;

	if (hash_used + TDB_SUBLEVEL_HASH_BITS > 64)
		return add_to_chain(tdb, subhash, off);

	h.h = hash_record(tdb, off);
	gnum = use_bits(&h, TDB_SUBLEVEL_HASH_BITS-TDB_HASH_GROUP_BITS);
	h.group_start = subhash
		+ gnum * (sizeof(tdb_off_t) << TDB_HASH_GROUP_BITS);
	h.home_bucket = use_bits(&h, TDB_HASH_GROUP_BITS);

	group = tdb_access_write(tdb, h.group_start,
				 sizeof(*group) << TDB_HASH_GROUP_BITS, true);
	if (TDB_PTR_IS_ERR(group)) {
		return TDB_PTR_ERR(group);
	}
	force_into_group(group, h.home_bucket, encode_offset(off, &h));
	return tdb_access_commit(tdb, group);
}
