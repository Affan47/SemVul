regcache_sync_block_raw_flush(struct regmap *map, const void **data,
					 unsigned int base, unsigned int cur)
{
	size_t val_bytes = map->format.val_bytes;
	int ret, count;

	if (*data == NULL)
		return 0;

	count = (cur - base) / map->reg_stride;

	dev_dbg(map->dev, "Writing %zu bytes for %d registers from 0x%x-0x%x\n",
		count * val_bytes, count, base, cur - map->reg_stride);

	map->cache_bypass = true;

	ret = _regmap_raw_write(map, base, *data, count * val_bytes);
	if (ret)
		dev_err(map->dev, "Unable to sync registers %#x-%#x. %d\n",
			base, cur - map->reg_stride, ret);

	map->cache_bypass = false;

	*data = NULL;

	return ret;
}
