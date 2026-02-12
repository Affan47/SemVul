NTSTATUS open_file_fchmod(connection_struct *conn,
			  struct smb_filename *smb_fname,
			  files_struct **result)
{
	if (!VALID_STAT(smb_fname->st)) {
		return NT_STATUS_INVALID_PARAMETER;
	}

        return SMB_VFS_CREATE_FILE(
		conn,
		NULL,
		0,
		smb_fname,
		FILE_WRITE_DATA,
		(FILE_SHARE_READ | FILE_SHARE_WRITE |
		    FILE_SHARE_DELETE),
		FILE_OPEN,
		0,
		0,
		INTERNAL_OPEN_ONLY,
		0,
		0,
		NULL,
		NULL,
		result,
		NULL);
}
