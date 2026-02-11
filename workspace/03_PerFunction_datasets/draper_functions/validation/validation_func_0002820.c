fdisk_get_freespaces(struct fdisk_context *cxt, struct fdisk_table **tb)
{
	int rc = 0;
	size_t nparts = 0;
	fdisk_sector_t last, grain;
	struct fdisk_table *parts = NULL;
	struct fdisk_partition *pa;
	struct fdisk_iter itr;

	DBG(CXT, ul_debugobj(cxt, "-- get freespace --"));

	if (!cxt || !cxt->label || !tb)
		return -EINVAL;
	if (!*tb && !(*tb = fdisk_new_table()))
		return -ENOMEM;

	rc = fdisk_get_partitions(cxt, &parts);
	if (rc)
		goto done;

	fdisk_table_sort_partitions(parts, fdisk_partition_cmp_start);
	fdisk_reset_iter(&itr, FDISK_ITER_FORWARD);
	last = cxt->first_lba;
	grain = cxt->grain > cxt->sector_size ?	cxt->grain / cxt->sector_size : 1;

	DBG(CXT, ul_debugobj(cxt, "initialized:  last=%ju, grain=%ju", last, grain));


	while (rc == 0 && fdisk_table_next_partition(parts, &itr, &pa) == 0) {

		DBG(CXT, ul_debugobj(cxt, "partno=%zu, start=%ju", pa->partno, pa->start));

		if (!pa->used || pa->wholedisk || fdisk_partition_is_nested(pa)
			      || !fdisk_partition_has_start(pa))
			continue;
		DBG(CXT, ul_debugobj(cxt, "freespace analyze: partno=%zu, start=%ju, end=%ju",
					pa->partno,
					(uintmax_t) fdisk_partition_get_start(pa),
					(uintmax_t) fdisk_partition_get_end(pa)));
		if (last + grain <= pa->start) {
			rc = table_add_freespace(cxt, *tb,
				last + (last > cxt->first_lba ? 1 : 0),
				pa->start - 1, NULL);
		}

		if (fdisk_partition_is_container(pa))
			rc = check_container_freespace(cxt, parts, *tb, pa);
		last = fdisk_partition_get_end(pa);
		nparts++;
	}


	if (rc == 0 && last + grain < cxt->total_sectors - 1) {
		DBG(CXT, ul_debugobj(cxt, "freespace behind last partition detected"));
		rc = new_freespace(cxt,
			last + (last > cxt->first_lba || nparts ? 1 : 0),
			cxt->last_lba, NULL, &pa);
		if (pa) {
			fdisk_table_add_partition(*tb, pa);
			fdisk_unref_partition(pa);
		}
	}

done:
	fdisk_unref_table(parts);

	DBG(CXT, ul_debugobj(cxt, "get freespace DONE [rc=%d]", rc));
	return rc;
}
