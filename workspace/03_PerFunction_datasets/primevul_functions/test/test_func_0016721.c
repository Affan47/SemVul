NTSTATUS create_directory(connection_struct *conn, struct smb_request *req,
			  struct smb_filename *smb_dname)
{
	NTSTATUS status;
	files_struct *fsp;

	status = SMB_VFS_CREATE_FILE(
		conn,
		req,
		0,
		smb_dname,
		FILE_READ_ATTRIBUTES,
		FILE_SHARE_NONE,
		FILE_CREATE,
		FILE_DIRECTORY_FILE,
		FILE_ATTRIBUTE_DIRECTORY,
		0,
		0,
		0,
		NULL,
		NULL,
		&fsp,
		NULL);

	if (NT_STATUS_IS_OK(status)) {
		close_file(req, fsp, NORMAL_CLOSE);
	}

	return status;
}
