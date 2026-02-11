fdreaddir( pfs_off_t offset, pfs_off_t *next_offset )
{
	static union {
		struct dirent entry;
		char padding[sizeof(struct dirent)+_POSIX_PATH_MAX];
	} d;


	errno = 0;

	if(!data) return 0;
	if(offset<0) return 0;

	if(offset>=length) {
		total_iterations++;
		return 0;
	}


	if(total_iterations>0 && (!strcmp(pfs_process_name(),"/bin/rm") || !strcmp(pfs_process_name(),"/usr/bin/rm")) ) {
		debug(D_LIBCALL,"end of directory reached, shortcutting further iterations by rm");
		return 0;
	}


	char *result = &data[offset];

	memset(&d,0,sizeof(d));
	strcpy(d.entry.d_name,result);
	d.entry.d_ino = hash_string(d.entry.d_name);
	d.entry.d_off = offset;
	d.entry.d_reclen = sizeof(d.entry) + strlen(d.entry.d_name);
	d.entry.d_type = 0;

	*next_offset = offset + strlen(result)+1;

	return &d.entry;
}
