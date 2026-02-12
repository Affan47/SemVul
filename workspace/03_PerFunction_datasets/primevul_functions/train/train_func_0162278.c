int blkid_partitions_do_subprobe(blkid_probe pr, blkid_partition parent,
		const struct blkid_idinfo *id)
{
	blkid_probe prc;
	int rc;
	blkid_partlist ls;
	uint64_t sz, off;

	DBG(LOWPROBE, ul_debug(
		"parts: ----> %s subprobe requested (parent=%p)",
		id->name, parent));

	if (!pr || !parent || !parent->size)
		return -EINVAL;
	if (pr->flags & BLKID_FL_NOSCAN_DEV)
		return BLKID_PROBE_NONE;


	sz = parent->size << 9;
	off = parent->start << 9;

	if (off < pr->off || pr->off + pr->size < off + sz) {
		DBG(LOWPROBE, ul_debug(
			"ERROR: parts: <---- '%s' subprobe: overflow detected.",
			id->name));
		return -ENOSPC;
	}


	prc = blkid_clone_probe(pr);
	if (!prc)
		return -ENOMEM;

	blkid_probe_set_dimension(prc, off, sz);


	prc->cur_chain = blkid_probe_get_chain(pr);


	ls = blkid_probe_get_partlist(pr);
	blkid_partlist_set_parent(ls, parent);

	blkid_probe_set_partlist(prc, ls);

	rc = idinfo_probe(prc, id, blkid_probe_get_chain(pr));

	blkid_probe_set_partlist(prc, NULL);
	blkid_partlist_set_parent(ls, NULL);

	blkid_free_probe(prc);

	DBG(LOWPROBE, ul_debug(
		"parts: <---- %s subprobe done (parent=%p, rc=%d)",
		id->name, parent, rc));

	return rc;
}
