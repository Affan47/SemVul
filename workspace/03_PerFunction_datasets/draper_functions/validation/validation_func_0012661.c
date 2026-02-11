lpddr_probe(struct map_info *map)
{
	struct mtd_info *mtd = NULL;
	struct lpddr_private *lpddr;


	lpddr = lpddr_probe_chip(map);
	if (!lpddr)
		return NULL;

	map->fldrv_priv = lpddr;
	mtd = lpddr_cmdset(map);
	if (mtd) {
		if (mtd->size > map->size) {
			printk(KERN_WARNING "Reducing visibility of %ldKiB chip"
				"to %ldKiB\n", (unsigned long)mtd->size >> 10,
				(unsigned long)map->size >> 10);
			mtd->size = map->size;
		}
		return mtd;
	}

	kfree(lpddr->qinfo);
	kfree(lpddr);
	map->fldrv_priv = NULL;
	return NULL;
}
