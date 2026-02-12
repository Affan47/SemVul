static NTSTATUS get_posix_fsp(connection_struct *conn,
			struct smb_request *req,
			struct smb_filename *smb_fname,
			uint32_t access_mask,
			files_struct **ret_fsp)
{
	NTSTATUS status;
	uint32_t create_disposition = FILE_OPEN;
	uint32_t share_access = FILE_SHARE_READ|
				FILE_SHARE_WRITE|
				FILE_SHARE_DELETE;
	struct smb2_create_blobs *posx = NULL;


	uint32_t file_attributes = 0664;
	uint32_t oplock = NO_OPLOCK;
	uint32_t create_options = FILE_NON_DIRECTORY_FILE;


	if (!VALID_STAT(smb_fname->st)) {
		return NT_STATUS_OBJECT_NAME_NOT_FOUND;
	}

	if (S_ISLNK(smb_fname->st.st_ex_mode)) {
		return NT_STATUS_ACCESS_DENIED;
	}

	if (S_ISDIR(smb_fname->st.st_ex_mode)) {


		file_attributes = 0775;
		create_options = FILE_DIRECTORY_FILE;
	}

	status = make_smb2_posix_create_ctx(
		talloc_tos(), &posx, file_attributes);
	if (!NT_STATUS_IS_OK(status)) {
		DBG_WARNING("make_smb2_posix_create_ctx failed: %s\n",
			    nt_errstr(status));
		goto done;
	}

	status = SMB_VFS_CREATE_FILE(
		conn,
		req,
		smb_fname,
		access_mask,
		share_access,
		create_disposition,
		create_options,
		file_attributes,
		oplock,
		NULL,
		0,
		0,
		NULL,
		NULL,
		ret_fsp,
		NULL,
		posx,
		NULL);

done:
	TALLOC_FREE(posx);
	return status;
}
