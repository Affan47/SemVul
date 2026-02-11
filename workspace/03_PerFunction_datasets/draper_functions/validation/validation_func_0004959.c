nd_blk_namespace_label_update(struct nd_region *nd_region,
		struct nd_namespace_blk *nsblk, resource_size_t size)
{
	struct nd_mapping *nd_mapping = &nd_region->mapping[0];
	struct resource *res;
	int count = 0;

	if (size == 0)
		return del_labels(nd_mapping, nsblk->uuid);

	for_each_dpa_resource(to_ndd(nd_mapping), res)
		count++;

	count = init_labels(nd_mapping, count);
	if (count < 0)
		return count;

	return __blk_label_update(nd_region, nd_mapping, nsblk, count);
}
