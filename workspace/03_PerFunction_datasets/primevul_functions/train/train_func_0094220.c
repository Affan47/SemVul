static NTSTATUS smb_set_file_allocation_info(connection_struct *conn,
					     struct smb_request *req,
					const char *pdata,
					int total_data,
					files_struct *fsp,
					struct smb_filename *smb_fname)
{
	uint64_t allocation_size = 0;
	NTSTATUS status = NT_STATUS_OK;
	files_struct *new_fsp = NULL;

	if (!VALID_STAT(smb_fname->st)) {
		return NT_STATUS_OBJECT_NAME_NOT_FOUND;
	}

	if (total_data < 8) {
		return NT_STATUS_INVALID_PARAMETER;
	}

	allocation_size = (uint64_t)IVAL(pdata,0);
	allocation_size |= (((uint64_t)IVAL(pdata,4)) << 32);
	DEBUG(10,("smb_set_file_allocation_info: Set file allocation info for "
		  "file %s to %.0f\n", smb_fname_str_dbg(smb_fname),
		  (double)allocation_size));

	if (allocation_size) {
		allocation_size = smb_roundup(conn, allocation_size);
	}

	DEBUG(10,("smb_set_file_allocation_info: file %s : setting new "
		  "allocation size to %.0f\n", smb_fname_str_dbg(smb_fname),
		  (double)allocation_size));

	if (fsp &&
	    !fsp->fsp_flags.is_pathref &&
	    fsp_get_io_fd(fsp) != -1)
	{

		if (!(fsp->access_mask & FILE_WRITE_DATA)) {
			return NT_STATUS_ACCESS_DENIED;
		}


		if (allocation_size != get_file_size_stat(&smb_fname->st)) {
			if (vfs_allocate_file_space(fsp, allocation_size) == -1) {
				return map_nt_error_from_unix(errno);
			}
		}


		trigger_write_time_update_immediate(fsp);
		return NT_STATUS_OK;
	}


	status = SMB_VFS_CREATE_FILE(
		conn,
		req,
		smb_fname,
		FILE_WRITE_DATA,
		(FILE_SHARE_READ | FILE_SHARE_WRITE |
		    FILE_SHARE_DELETE),
		FILE_OPEN,
		0,
		FILE_ATTRIBUTE_NORMAL,
		0,
		NULL,
		0,
		0,
		NULL,
		NULL,
		&new_fsp,
		NULL,
		NULL, NULL);

	if (!NT_STATUS_IS_OK(status)) {

		return status;
	}


	if (allocation_size != get_file_size_stat(&smb_fname->st)) {
		if (vfs_allocate_file_space(new_fsp, allocation_size) == -1) {
			status = map_nt_error_from_unix(errno);
			close_file(req, new_fsp, NORMAL_CLOSE);
			return status;
		}
	}


	trigger_write_time_update_immediate(new_fsp);
	close_file(req, new_fsp, NORMAL_CLOSE);
	return NT_STATUS_OK;
}
