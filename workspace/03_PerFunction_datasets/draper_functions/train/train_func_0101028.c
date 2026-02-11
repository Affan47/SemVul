__pmem_label_update(struct nd_region *nd_region,
		struct nd_mapping *nd_mapping, struct nd_namespace_pmem *nspm,
		int pos)
{
	u64 cookie = nd_region_interleave_set_cookie(nd_region), rawsize;
	struct nvdimm_drvdata *ndd = to_ndd(nd_mapping);
	struct nd_namespace_label *victim_label;
	struct nd_namespace_label *nd_label;
	struct nd_namespace_index *nsindex;
	unsigned long *free;
	u32 nslot, slot;
	size_t offset;
	int rc;

	if (!preamble_next(ndd, &nsindex, &free, &nslot))
		return -ENXIO;


	slot = nd_label_alloc_slot(ndd);
	if (slot == UINT_MAX)
		return -ENXIO;
	dev_dbg(ndd->dev, "%s: allocated: %d\n", __func__, slot);

	nd_label = nd_label_base(ndd) + slot;
	memset(nd_label, 0, sizeof(struct nd_namespace_label));
	memcpy(nd_label->uuid, nspm->uuid, NSLABEL_UUID_LEN);
	if (nspm->alt_name)
		memcpy(nd_label->name, nspm->alt_name, NSLABEL_NAME_LEN);
	nd_label->flags = __cpu_to_le32(NSLABEL_FLAG_UPDATING);
	nd_label->nlabel = __cpu_to_le16(nd_region->ndr_mappings);
	nd_label->position = __cpu_to_le16(pos);
	nd_label->isetcookie = __cpu_to_le64(cookie);
	rawsize = div_u64(resource_size(&nspm->nsio.res),
			nd_region->ndr_mappings);
	nd_label->rawsize = __cpu_to_le64(rawsize);
	nd_label->dpa = __cpu_to_le64(nd_mapping->start);
	nd_label->slot = __cpu_to_le32(slot);


	offset = nd_label_offset(ndd, nd_label);
	rc = nvdimm_set_config_data(ndd, offset, nd_label,
			sizeof(struct nd_namespace_label));
	if (rc < 0)
		return rc;


	victim_label = nd_mapping->labels[0];
	if (victim_label) {
		slot = to_slot(ndd, victim_label);
		nd_label_free_slot(ndd, slot);
		dev_dbg(ndd->dev, "%s: free: %d\n", __func__, slot);
	}


	rc = nd_label_write_index(ndd, ndd->ns_next,
			nd_inc_seq(__le32_to_cpu(nsindex->seq)), 0);
	if (rc < 0)
		return rc;

	nd_mapping->labels[0] = nd_label;

	return 0;
}
