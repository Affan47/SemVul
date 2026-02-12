static NTSTATUS smb_set_file_basic_info(connection_struct *conn,
					const char *pdata,
					int total_data,
					files_struct *fsp,
					struct smb_filename *smb_fname)
{

	struct smb_file_time ft;
	uint32_t dosmode = 0;
	NTSTATUS status = NT_STATUS_OK;

	init_smb_file_time(&ft);

	if (total_data < 36) {
		return NT_STATUS_INVALID_PARAMETER;
	}

	if (fsp == NULL) {
		return NT_STATUS_INVALID_HANDLE;
	}

	status = check_access_fsp(fsp, FILE_WRITE_ATTRIBUTES);
	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}


	dosmode = IVAL(pdata,32);
	status = smb_set_file_dosmode(conn, fsp, dosmode);
	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}


	ft.create_time = pull_long_date_full_timespec(pdata);


	ft.atime = pull_long_date_full_timespec(pdata+8);


	ft.mtime = pull_long_date_full_timespec(pdata+16);


	ft.ctime = pull_long_date_full_timespec(pdata+24);

	DEBUG(10, ("smb_set_file_basic_info: file %s\n",
		   smb_fname_str_dbg(smb_fname)));

	status = smb_set_file_time(conn, fsp, smb_fname, &ft, true);
	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (fsp->fsp_flags.modified) {
		trigger_write_time_update_immediate(fsp);
	}
	return NT_STATUS_OK;
}
