blkid_probe_get_wholedisk_probe(blkid_probe pr)
{
	dev_t disk;

	if (blkid_probe_is_wholedisk(pr))
		return NULL;

	if (pr->parent)

		return blkid_probe_get_wholedisk_probe(pr->parent);

	disk = blkid_probe_get_wholedisk_devno(pr);

	if (pr->disk_probe && pr->disk_probe->devno != disk) {

		blkid_free_probe(pr->disk_probe);
		pr->disk_probe = NULL;
	}

	if (!pr->disk_probe) {

		char *disk_path = blkid_devno_to_devname(disk);

		if (!disk_path)
			return NULL;

		DBG(LOWPROBE, ul_debug("allocate a wholedisk probe"));

		pr->disk_probe = blkid_new_probe_from_filename(disk_path);

		free(disk_path);

		if (!pr->disk_probe)
			return NULL;
	}

	return pr->disk_probe;
}
