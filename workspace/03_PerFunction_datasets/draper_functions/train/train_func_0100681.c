__create_snap(struct dm_pool_metadata *pmd,
			 dm_thin_id dev, dm_thin_id origin)
{
	int r;
	dm_block_t origin_root;
	uint64_t key = origin, dev_key = dev;
	struct dm_thin_device *td;
	struct disk_device_details details_le;
	__le64 value;


	r = dm_btree_lookup(&pmd->details_info, pmd->details_root,
			    &dev_key, &details_le);
	if (!r)
		return -EEXIST;


	r = dm_btree_lookup(&pmd->tl_info, pmd->root, &key, &value);
	if (r)
		return r;
	origin_root = le64_to_cpu(value);


	dm_tm_inc(pmd->tm, origin_root);


	value = cpu_to_le64(origin_root);
	__dm_bless_for_disk(&value);
	key = dev;
	r = dm_btree_insert(&pmd->tl_info, pmd->root, &key, &value, &pmd->root);
	if (r) {
		dm_tm_dec(pmd->tm, origin_root);
		return r;
	}

	pmd->time++;

	r = __open_device(pmd, dev, 1, &td);
	if (r)
		goto bad;

	r = __set_snapshot_details(pmd, td, origin, pmd->time);
	__close_device(td);

	if (r)
		goto bad;

	return 0;

bad:
	dm_btree_remove(&pmd->tl_info, pmd->root, &key, &pmd->root);
	dm_btree_remove(&pmd->details_info, pmd->details_root,
			&key, &pmd->details_root);
	return r;
}
