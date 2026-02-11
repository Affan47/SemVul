get_partition_start(int fd, int partno, uint64_t *start)
{
	struct stat st;
	struct sysfs_cxt disk = { 0, -1, NULL, NULL },
			 part = { 0, -1, NULL, NULL };
	dev_t devno = 0;
	int rc = -1;


	if (fstat(fd, &st) || !S_ISBLK(st.st_mode))
		goto done;
	devno = st.st_rdev;
	if (sysfs_init(&disk, devno, NULL))
		goto done;


	devno = sysfs_partno_to_devno(&disk, partno);
	if (!devno)
		goto done;
	if (sysfs_init(&part, devno, &disk))
		goto done;
	if (sysfs_read_u64(&part, "start", start))
		goto done;

	rc = 0;
done:
	sysfs_deinit(&part);
	sysfs_deinit(&disk);
	return rc;
}
