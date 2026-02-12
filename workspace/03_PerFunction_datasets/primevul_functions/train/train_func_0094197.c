static char *store_file_unix_basic(connection_struct *conn,
				char *pdata,
				files_struct *fsp,
				const SMB_STRUCT_STAT *psbuf)
{
	dev_t devno;

	DEBUG(10,("store_file_unix_basic: SMB_QUERY_FILE_UNIX_BASIC\n"));
	DEBUG(4,("store_file_unix_basic: st_mode=%o\n",(int)psbuf->st_ex_mode));

	SOFF_T(pdata,0,get_file_size_stat(psbuf));
	pdata += 8;

	SOFF_T(pdata,0,SMB_VFS_GET_ALLOC_SIZE(conn,fsp,psbuf));
	pdata += 8;

	put_long_date_full_timespec(TIMESTAMP_SET_NT_OR_BETTER, pdata, &psbuf->st_ex_ctime);
	put_long_date_full_timespec(TIMESTAMP_SET_NT_OR_BETTER ,pdata+8, &psbuf->st_ex_atime);
	put_long_date_full_timespec(TIMESTAMP_SET_NT_OR_BETTER, pdata+16, &psbuf->st_ex_mtime);
	pdata += 24;

	SIVAL(pdata,0,psbuf->st_ex_uid);
	SIVAL(pdata,4,0);
	pdata += 8;

	SIVAL(pdata,0,psbuf->st_ex_gid);
	SIVAL(pdata,4,0);
	pdata += 8;

	SIVAL(pdata,0,unix_filetype(psbuf->st_ex_mode));
	pdata += 4;

	if (S_ISBLK(psbuf->st_ex_mode) || S_ISCHR(psbuf->st_ex_mode)) {
		devno = psbuf->st_ex_rdev;
	} else {
		devno = psbuf->st_ex_dev;
	}

	SIVAL(pdata,0,unix_dev_major(devno));
	SIVAL(pdata,4,0);
	pdata += 8;

	SIVAL(pdata,0,unix_dev_minor(devno));
	SIVAL(pdata,4,0);
	pdata += 8;

	SINO_T_VAL(pdata, 0, psbuf->st_ex_ino);
	pdata += 8;

	SIVAL(pdata,0, unix_perms_to_wire(psbuf->st_ex_mode));
	SIVAL(pdata,4,0);
	pdata += 8;

	SIVAL(pdata,0,psbuf->st_ex_nlink);
	SIVAL(pdata,4,0);
	pdata += 8;

	return pdata;
}
