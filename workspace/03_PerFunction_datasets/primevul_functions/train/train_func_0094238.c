static NTSTATUS smb_set_file_size(connection_struct *conn,
				  struct smb_request *req,
				  files_struct *fsp,
				  struct smb_filename *smb_fname,
				  const SMB_STRUCT_STAT *psbuf,
				  off_t size,
				  bool fail_after_createfile)
{
	NTSTATUS status = NT_STATUS_OK;
	files_struct *new_fsp = NULL;

	if (!VALID_STAT(*psbuf)) {
		return NT_STATUS_OBJECT_NAME_NOT_FOUND;
	}

	DBG_INFO("size: %"PRIu64", file_size_stat=%"PRIu64"\n",
		 (uint64_t)size,
		 get_file_size_stat(psbuf));

	if (size == get_file_size_stat(psbuf)) {
		if (fsp == NULL) {
			return NT_STATUS_OK;
		}
		if (!fsp->fsp_flags.modified) {
			return NT_STATUS_OK;
		}
		trigger_write_time_update_immediate(fsp);
		return NT_STATUS_OK;
	}

	DEBUG(10,("smb_set_file_size: file %s : setting new size to %.0f\n",
		  smb_fname_str_dbg(smb_fname), (double)size));

	if (fsp &&
	    !fsp->fsp_flags.is_pathref &&
	    fsp_get_io_fd(fsp) != -1)
	{

		if (!(fsp->access_mask & FILE_WRITE_DATA)) {
			return NT_STATUS_ACCESS_DENIED;
		}

		if (vfs_set_filelen(fsp, size) == -1) {
			return map_nt_error_from_unix(errno);
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


	if (fail_after_createfile) {
		close_file(req, new_fsp,NORMAL_CLOSE);
		return NT_STATUS_INVALID_LEVEL;
	}

	if (vfs_set_filelen(new_fsp, size) == -1) {
		status = map_nt_error_from_unix(errno);
		close_file(req, new_fsp,NORMAL_CLOSE);
		return status;
	}

	trigger_write_time_update_immediate(new_fsp);
	close_file(req, new_fsp,NORMAL_CLOSE);
	return NT_STATUS_OK;
}
