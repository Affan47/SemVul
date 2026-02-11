ext4_groupinfo_destroy_slabs(void)
{
	int i;

	for (i = 0; i < NR_GRPINFO_CACHES; i++) {
		if (ext4_groupinfo_caches[i])
			kmem_cache_destroy(ext4_groupinfo_caches[i]);
		ext4_groupinfo_caches[i] = NULL;
	}
}
