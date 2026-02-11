cobalt_flash_probe(struct cobalt *cobalt)
{
	struct map_info *map = &cobalt_flash_map;
	struct mtd_info *mtd;

	BUG_ON(!map_bankwidth_supported(map->bankwidth));
	map->virt = cobalt->bar1;
	map->read = flash_read16;
	map->write = flash_write16;
	map->copy_from = flash_copy_from;
	map->copy_to = flash_copy_to;

	mtd = do_map_probe("cfi_probe", map);
	cobalt->mtd = mtd;
	if (!mtd) {
		cobalt_err("Probe CFI flash failed!\n");
		return -1;
	}

	mtd->owner = THIS_MODULE;
	mtd->dev.parent = &cobalt->pci_dev->dev;
	mtd_device_register(mtd, NULL, 0);
	return 0;
}
