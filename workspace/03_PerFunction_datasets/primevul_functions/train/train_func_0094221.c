static NTSTATUS smb_posix_open(connection_struct *conn,
			       struct smb_request *req,
				char **ppdata,
				int total_data,
				struct smb_filename *smb_fname,
				int *pdata_return_size)
{
	bool extended_oplock_granted = False;
	char *pdata = *ppdata;
	uint32_t flags = 0;
	uint32_t wire_open_mode = 0;
	uint32_t raw_unixmode = 0;
	uint32_t attributes = 0;
	uint32_t create_disp = 0;
	uint32_t access_mask = 0;
	uint32_t create_options = FILE_NON_DIRECTORY_FILE;
	NTSTATUS status = NT_STATUS_OK;
	mode_t unixmode = (mode_t)0;
	files_struct *fsp = NULL;
	int oplock_request = 0;
	int info = 0;
	uint16_t info_level_return = 0;
	struct smb2_create_blobs *posx = NULL;

	if (total_data < 18) {
		return NT_STATUS_INVALID_PARAMETER;
	}

	flags = IVAL(pdata,0);
	oplock_request = (flags & REQUEST_OPLOCK) ? EXCLUSIVE_OPLOCK : 0;
	if (oplock_request) {
		oplock_request |= (flags & REQUEST_BATCH_OPLOCK) ? BATCH_OPLOCK : 0;
	}

	wire_open_mode = IVAL(pdata,4);

	if (wire_open_mode == (SMB_O_CREAT|SMB_O_DIRECTORY)) {
		return smb_posix_mkdir(conn, req,
					ppdata,
					total_data,
					smb_fname,
					pdata_return_size);
	}

	switch (wire_open_mode & SMB_ACCMODE) {
		case SMB_O_RDONLY:
			access_mask = SMB_O_RDONLY_MAPPING;
			break;
		case SMB_O_WRONLY:
			access_mask = SMB_O_WRONLY_MAPPING;
			break;
		case SMB_O_RDWR:
			access_mask = (SMB_O_RDONLY_MAPPING|
					SMB_O_WRONLY_MAPPING);
			break;
		default:
			DEBUG(5,("smb_posix_open: invalid open mode 0x%x\n",
				(unsigned int)wire_open_mode ));
			return NT_STATUS_INVALID_PARAMETER;
	}

	wire_open_mode &= ~SMB_ACCMODE;


	switch (wire_open_mode & (SMB_O_CREAT | SMB_O_EXCL)) {
		case (SMB_O_CREAT | SMB_O_EXCL):

			create_disp = FILE_CREATE;
			break;
		case SMB_O_CREAT:

			create_disp = FILE_OPEN_IF;
			break;
		case SMB_O_EXCL:


		case 0:

			create_disp = FILE_OPEN;
			break;
		default:
			DEBUG(5,("smb_posix_open: invalid create mode 0x%x\n",
				(unsigned int)wire_open_mode ));
			return NT_STATUS_INVALID_PARAMETER;
	}


	wire_open_mode &= ~(SMB_O_CREAT | SMB_O_EXCL);

	if (wire_open_mode & SMB_O_TRUNC) {
		switch (create_disp) {
			case FILE_CREATE:


				break;
			case FILE_OPEN_IF:


				create_disp = FILE_OVERWRITE_IF;
				break;
			case FILE_OPEN:


				create_disp = FILE_OVERWRITE;
				break;
			default:

				smb_panic("smb_posix_open: logic error");
				return NT_STATUS_INVALID_PARAMETER;
		}
	}

	raw_unixmode = IVAL(pdata,8);


	status = unix_perms_from_wire(conn, &smb_fname->st, raw_unixmode,
				      (VALID_STAT(smb_fname->st) ?
					  PERM_EXISTING_FILE : PERM_NEW_FILE),
				      &unixmode);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	status = make_smb2_posix_create_ctx(talloc_tos(), &posx, unixmode);
	if (!NT_STATUS_IS_OK(status)) {
		DBG_WARNING("make_smb2_posix_create_ctx failed: %s\n",
			    nt_errstr(status));
		return status;
	}

	if (wire_open_mode & SMB_O_SYNC) {
		create_options |= FILE_WRITE_THROUGH;
	}
	if (wire_open_mode & SMB_O_APPEND) {
		access_mask |= FILE_APPEND_DATA;
	}
	if (wire_open_mode & SMB_O_DIRECT) {
		attributes |= FILE_FLAG_NO_BUFFERING;
	}

	if ((wire_open_mode & SMB_O_DIRECTORY) ||
			VALID_STAT_OF_DIR(smb_fname->st)) {
		if (access_mask != SMB_O_RDONLY_MAPPING) {
			return NT_STATUS_FILE_IS_A_DIRECTORY;
		}
		create_options &= ~FILE_NON_DIRECTORY_FILE;
		create_options |= FILE_DIRECTORY_FILE;
	}

	DEBUG(10,("smb_posix_open: file %s, smb_posix_flags = %u, mode 0%o\n",
		smb_fname_str_dbg(smb_fname),
		(unsigned int)wire_open_mode,
		(unsigned int)unixmode ));

        status = SMB_VFS_CREATE_FILE(
		conn,
		req,
		smb_fname,
		access_mask,
		(FILE_SHARE_READ | FILE_SHARE_WRITE |
		    FILE_SHARE_DELETE),
		create_disp,
		create_options,
		attributes,
		oplock_request,
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

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (oplock_request && lp_fake_oplocks(SNUM(conn))) {
		extended_oplock_granted = True;
	}

	if(oplock_request && EXCLUSIVE_OPLOCK_TYPE(fsp->oplock_type)) {
		extended_oplock_granted = True;
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
		close_file(req, fsp, ERROR_CLOSE);
		*pdata_return_size = 0;
		return NT_STATUS_NO_MEMORY;
	}
	pdata = *ppdata;

	if (extended_oplock_granted) {
		if (flags & REQUEST_BATCH_OPLOCK) {
			SSVAL(pdata,0, BATCH_OPLOCK_RETURN);
		} else {
			SSVAL(pdata,0, EXCLUSIVE_OPLOCK_RETURN);
		}
	} else if (fsp->oplock_type == LEVEL_II_OPLOCK) {
		SSVAL(pdata,0, LEVEL_II_OPLOCK_RETURN);
	} else {
		SSVAL(pdata,0,NO_OPLOCK_RETURN);
	}

	SSVAL(pdata,2,fsp->fnum);
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
	return NT_STATUS_OK;
}
