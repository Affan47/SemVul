static int strict_allocate_ftruncate(vfs_handle_struct *handle, files_struct *fsp, off_t len)
{
	off_t space_to_write;
	uint64_t space_avail;
	uint64_t bsize,dfree,dsize;
	int ret;
	NTSTATUS status;
	SMB_STRUCT_STAT *pst;

	status = vfs_stat_fsp(fsp);
	if (!NT_STATUS_IS_OK(status)) {
		return -1;
	}
	pst = &fsp->fsp_name->st;

#ifdef S_ISFIFO
	if (S_ISFIFO(pst->st_ex_mode))
		return 0;
#endif

	if (pst->st_ex_size == len)
		return 0;


	if (pst->st_ex_size > len)
		return ftruncate(fsp->fh->fd, len);

	space_to_write = len - pst->st_ex_size;


	ret = SMB_VFS_FALLOCATE(fsp, VFS_FALLOCATE_EXTEND_SIZE,
				pst->st_ex_size, space_to_write);
	if (ret == ENOSPC) {
		errno = ENOSPC;
		return -1;
	}
	if (ret == 0) {
		return 0;
	}
	DEBUG(10,("strict_allocate_ftruncate: SMB_VFS_FALLOCATE failed with "
		"error %d. Falling back to slow manual allocation\n", ret));


	space_avail = get_dfree_info(fsp->conn,
				     fsp->fsp_name->base_name, false,
				     &bsize,&dfree,&dsize);

	if (space_avail == (uint64_t)-1 ||
			((uint64_t)space_to_write/1024 > space_avail) ) {
		errno = ENOSPC;
		return -1;
	}


	ret = vfs_slow_fallocate(fsp, pst->st_ex_size, space_to_write);
	if (ret != 0) {
		errno = ret;
		ret = -1;
	}

	return 0;
}
