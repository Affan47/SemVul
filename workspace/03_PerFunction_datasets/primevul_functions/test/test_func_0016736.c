static NTSTATUS fd_open_atomic(struct connection_struct *conn,
			files_struct *fsp,
			int flags,
			mode_t mode,
			bool *file_created)
{
	NTSTATUS status = NT_STATUS_UNSUCCESSFUL;
	bool file_existed = VALID_STAT(fsp->fsp_name->st);

	*file_created = false;

	if (!(flags & O_CREAT)) {


		return fd_open(conn, fsp, flags, mode);
	}

	if (flags & O_EXCL) {


		status = fd_open(conn, fsp, flags, mode);


		*file_created = NT_STATUS_IS_OK(status);

		return status;
	}


	while(1) {
		int curr_flags = flags;

		if (file_existed) {

			curr_flags &= ~(O_CREAT);
			status = fd_open(conn, fsp, curr_flags, mode);
			if (NT_STATUS_EQUAL(status,
					NT_STATUS_OBJECT_NAME_NOT_FOUND)) {


				file_existed = false;
				DEBUG(10,("fd_open_atomic: file %s existed. "
					"Retry.\n",
					smb_fname_str_dbg(fsp->fsp_name)));
					continue;
			}
		} else {

			curr_flags |= O_EXCL;
			status = fd_open(conn, fsp, curr_flags, mode);
			if (NT_STATUS_EQUAL(status,
					NT_STATUS_OBJECT_NAME_COLLISION)) {


				file_existed = true;
				DEBUG(10,("fd_open_atomic: file %s "
					"did not exist. Retry.\n",
					smb_fname_str_dbg(fsp->fsp_name)));
				continue;
			}
			if (NT_STATUS_IS_OK(status)) {


				*file_created = true;
			}
		}

		break;
	}
	return status;
}
