static uint64_t vfswrap_get_alloc_size(vfs_handle_struct *handle,
				       struct files_struct *fsp,
				       const SMB_STRUCT_STAT *sbuf)
{
	uint64_t result;

	START_PROFILE(syscall_get_alloc_size);

	if(S_ISDIR(sbuf->st_ex_mode)) {
		result = 0;
		goto out;
	}

#if defined(HAVE_STAT_ST_BLOCKS) && defined(STAT_ST_BLOCKSIZE)


#if defined(SIZEOF_BLKCNT_T_8)
	result = (uint64_t)STAT_ST_BLOCKSIZE * (uint64_t)sbuf->st_ex_blocks;
#elif defined(SIZEOF_BLKCNT_T_4)
	{
		uint64_t bs = ((uint64_t)sbuf->st_ex_blocks) & 0xFFFFFFFFLL;
		result = (uint64_t)STAT_ST_BLOCKSIZE * bs;
	}
#else
#error SIZEOF_BLKCNT_T_NOT_A_SUPPORTED_VALUE
#endif
#else
	result = get_file_size_stat(sbuf);
#endif

	if (fsp && fsp->initial_allocation_size)
		result = MAX(result,fsp->initial_allocation_size);

	result = smb_roundup(handle->conn, result);

 out:
	END_PROFILE(syscall_get_alloc_size);
	return result;
}
