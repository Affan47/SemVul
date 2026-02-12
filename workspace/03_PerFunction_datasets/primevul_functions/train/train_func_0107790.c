static NTSTATUS copy_internals(TALLOC_CTX *ctx,
				connection_struct *conn,
				struct smb_request *req,
				struct smb_filename *smb_fname_src,
				struct smb_filename *smb_fname_dst,
				uint32 attrs)
{
	files_struct *fsp1,*fsp2;
	uint32 fattr;
	int info;
	SMB_OFF_T ret=-1;
	NTSTATUS status = NT_STATUS_OK;
	char *parent;

	if (!CAN_WRITE(conn)) {
		status = NT_STATUS_MEDIA_WRITE_PROTECTED;
		goto out;
	}


	if (!VALID_STAT(smb_fname_src->st)) {
		status = NT_STATUS_OBJECT_NAME_NOT_FOUND;
		goto out;
	}


	fattr = dos_mode(conn, smb_fname_src);
	if ((fattr & ~attrs) & (aHIDDEN | aSYSTEM)) {
		status = NT_STATUS_NO_SUCH_FILE;
		goto out;
	}


	if (VALID_STAT(smb_fname_dst->st)) {
		status = NT_STATUS_OBJECT_NAME_COLLISION;
		goto out;
	}


	if (S_ISDIR(smb_fname_src->st.st_ex_mode)) {
		status = NT_STATUS_FILE_IS_A_DIRECTORY;
		goto out;
	}

	DEBUG(10,("copy_internals: doing file copy %s to %s\n",
		  smb_fname_str_dbg(smb_fname_src),
		  smb_fname_str_dbg(smb_fname_dst)));

        status = SMB_VFS_CREATE_FILE(
		conn,
		req,
		0,
		smb_fname_src,
		FILE_READ_DATA,
		(FILE_SHARE_READ | FILE_SHARE_WRITE |
		    FILE_SHARE_DELETE),
		FILE_OPEN,
		0,
		FILE_ATTRIBUTE_NORMAL,
		NO_OPLOCK,
		0,
		NULL,
		NULL,
		&fsp1,
		&info);

	if (!NT_STATUS_IS_OK(status)) {
		goto out;
	}

        status = SMB_VFS_CREATE_FILE(
		conn,
		req,
		0,
		smb_fname_dst,
		FILE_WRITE_DATA,
		(FILE_SHARE_READ | FILE_SHARE_WRITE |
		    FILE_SHARE_DELETE),
		FILE_CREATE,
		0,
		fattr,
		NO_OPLOCK,
		0,
		NULL,
		NULL,
		&fsp2,
		&info);

	if (!NT_STATUS_IS_OK(status)) {
		close_file(NULL, fsp1, ERROR_CLOSE);
		goto out;
	}

	if (smb_fname_src->st.st_ex_size) {
		ret = vfs_transfer_file(fsp1, fsp2, smb_fname_src->st.st_ex_size);
	}


	close_file(NULL, fsp1, NORMAL_CLOSE);


	set_close_write_time(fsp2, smb_fname_src->st.st_ex_mtime);

	status = close_file(NULL, fsp2, NORMAL_CLOSE);


	if (!parent_dirname(talloc_tos(), smb_fname_dst->base_name, &parent,
			    NULL)) {
		status = NT_STATUS_NO_MEMORY;
		goto out;
	}
	file_set_dosmode(conn, smb_fname_dst, fattr, parent, false);
	TALLOC_FREE(parent);

	if (ret < (SMB_OFF_T)smb_fname_src->st.st_ex_size) {
		status = NT_STATUS_DISK_FULL;
		goto out;
	}
 out:
	if (!NT_STATUS_IS_OK(status)) {
		DEBUG(3,("copy_internals: Error %s copy file %s to %s\n",
			nt_errstr(status), smb_fname_str_dbg(smb_fname_src),
			smb_fname_str_dbg(smb_fname_dst)));
	}

	return status;
}
