xfs_bmap_split_indlen(
	xfs_filblks_t			ores,
	xfs_filblks_t			*indlen1,
	xfs_filblks_t			*indlen2,
	xfs_filblks_t			avail)
{
	xfs_filblks_t			len1 = *indlen1;
	xfs_filblks_t			len2 = *indlen2;
	xfs_filblks_t			nres = len1 + len2;
	xfs_filblks_t			stolen = 0;
	xfs_filblks_t			resfactor;


	if (ores < nres && avail)
		stolen = XFS_FILBLKS_MIN(nres - ores, avail);
	ores += stolen;


	if (ores >= nres)
		return stolen;


	resfactor = (ores * 100);
	do_div(resfactor, nres);
	len1 *= resfactor;
	do_div(len1, 100);
	len2 *= resfactor;
	do_div(len2, 100);
	ASSERT(len1 + len2 <= ores);
	ASSERT(len1 < *indlen1 && len2 < *indlen2);


	ores -= (len1 + len2);
	ASSERT((*indlen1 - len1) + (*indlen2 - len2) >= ores);
	if (ores && !len2 && *indlen2) {
		len2++;
		ores--;
	}
	while (ores) {
		if (len1 < *indlen1) {
			len1++;
			ores--;
		}
		if (!ores)
			break;
		if (len2 < *indlen2) {
			len2++;
			ores--;
		}
	}

	*indlen1 = len1;
	*indlen2 = len2;

	return stolen;
}
