static NTSTATUS smb_posix_mkdir(connection_struct *conn,
				struct smb_request *req,
				char **ppdata,
				int total_data,
				struct smb_filename *smb_fname,
				int *pdata_return_size)
{
	NTSTATUS status = NT_STATUS_OK;
	uint32_t raw_unixmode = 0;
	mode_t unixmode = (mode_t)0;
	files_struct *fsp = NULL;
	uint16_t info_level_return = 0;
	int info;
	char *pdata = *ppdata;
	struct smb2_create_blobs *posx = NULL;

	if (total_data < 18) {
		return NT_STATUS_INVALID_PARAMETER;
	}

	raw_unixmode = IVAL(pdata,8);


	status = unix_perms_from_wire(conn, &smb_fname->st, raw_unixmode,
				      PERM_NEW_DIR, &unixmode);
	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	status = make_smb2_posix_create_ctx(talloc_tos(), &posx, unixmode);
	if (!NT_STATUS_IS_OK(status)) {
		DBG_WARNING("make_smb2_posix_create_ctx failed: %s\n",
			    nt_errstr(status));
		return status;
	}

	DEBUG(10,("smb_posix_mkdir: file %s, mode 0%o\n",
		  smb_fname_str_dbg(smb_fname), (unsigned int)unixmode));

        status = SMB_VFS_CREATE_FILE(
		conn,
		req,
		smb_fname,
		FILE_READ_ATTRIBUTES,
		FILE_SHARE_NONE,
		FILE_CREATE,
		FILE_DIRECTORY_FILE,
		0,
		0,
		NULL,
		0,
		0,
		NULL,
		NULL,
		&fsp,
		&info,
		posx,
		NULL);

	TALLOC_FREE(posx);

        if (NT_STATUS_IS_OK(status)) {
                close_file(req, fsp, NORMAL_CLOSE);
        }

	info_level_return = SVAL(pdata,16);

	if (info_level_return == SMB_QUERY_FILE_UNIX_BASIC) {
		*pdata_return_size = 12 + SMB_FILE_UNIX_BASIC_SIZE;
	} else if (info_level_return ==  SMB_QUERY_FILE_UNIX_INFO2) {
		*pdata_return_size = 12 + SMB_FILE_UNIX_INFO2_SIZE;
	} else {
		*pdata_return_size = 12;
	}


	*ppdata = (char *)SMB_REALLOC(*ppdata,*pdata_return_size);
	if (*ppdata == NULL) {
		*pdata_return_size = 0;
		return NT_STATUS_NO_MEMORY;
	}
	pdata = *ppdata;

	SSVAL(pdata,0,NO_OPLOCK_RETURN);
	SSVAL(pdata,2,0);
	SIVAL(pdata,4,info);

	switch (info_level_return) {
		case SMB_QUERY_FILE_UNIX_BASIC:
			SSVAL(pdata,8,SMB_QUERY_FILE_UNIX_BASIC);
			SSVAL(pdata,10,0);
			store_file_unix_basic(conn, pdata + 12, fsp,
					      &smb_fname->st);
			break;
		case SMB_QUERY_FILE_UNIX_INFO2:
			SSVAL(pdata,8,SMB_QUERY_FILE_UNIX_INFO2);
			SSVAL(pdata,10,0);
			store_file_unix_basic_info2(conn, pdata + 12, fsp,
						    &smb_fname->st);
			break;
		default:
			SSVAL(pdata,8,SMB_NO_INFO_LEVEL_RETURNED);
			SSVAL(pdata,10,0);
			break;
	}

	return status;
}
