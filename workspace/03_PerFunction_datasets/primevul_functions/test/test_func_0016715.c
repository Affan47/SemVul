static NTSTATUS open_file(files_struct *fsp,
			  connection_struct *conn,
			  struct smb_request *req,
			  const char *parent_dir,
			  int flags,
			  mode_t unx_mode,
			  uint32 access_mask,
			  uint32 open_access_mask,
			  bool *p_file_created)
{
	struct smb_filename *smb_fname = fsp->fsp_name;
	NTSTATUS status = NT_STATUS_OK;
	int accmode = (flags & O_ACCMODE);
	int local_flags = flags;
	bool file_existed = VALID_STAT(fsp->fsp_name->st);

	fsp->fh->fd = -1;
	errno = EPERM;


	if (!CAN_WRITE(conn)) {

		if(accmode != O_RDONLY || (flags & O_TRUNC) || (flags & O_APPEND)) {
			DEBUG(3,("Permission denied opening %s\n",
				 smb_fname_str_dbg(smb_fname)));
			return NT_STATUS_ACCESS_DENIED;
		}
		if (flags & O_CREAT) {


			flags &= ~(O_CREAT|O_EXCL);
			local_flags &= ~(O_CREAT|O_EXCL);
		}
	}


	if ((accmode == O_RDONLY) && ((flags & O_TRUNC) == O_TRUNC)) {
		DEBUG(10,("open_file: truncate requested on read-only open "
			  "for file %s\n", smb_fname_str_dbg(smb_fname)));
		local_flags = (flags & ~O_ACCMODE)|O_RDWR;
	}

	if ((open_access_mask & (FILE_READ_DATA|FILE_WRITE_DATA|FILE_APPEND_DATA|FILE_EXECUTE)) ||
	    (!file_existed && (local_flags & O_CREAT)) ||
	    ((local_flags & O_TRUNC) == O_TRUNC) ) {
		const char *wild;
		int ret;

#if defined(O_NONBLOCK) && defined(S_ISFIFO)


		if (file_existed && S_ISFIFO(smb_fname->st.st_ex_mode)) {
			local_flags &= ~O_TRUNC;
			local_flags |= O_NONBLOCK;
		}
#endif


		if (fsp->base_fsp) {


			wild = fsp->base_fsp->fsp_name->base_name;
		} else {
			wild = smb_fname->base_name;
		}
		if ((local_flags & O_CREAT) && !file_existed &&
		    ms_has_wild(wild))  {
			return NT_STATUS_OBJECT_NAME_INVALID;
		}


		if (!fsp->base_fsp) {

			if (file_existed) {
				status = smbd_check_access_rights(conn,
						smb_fname,
						false,
						access_mask);
			} else if (local_flags & O_CREAT){
				status = check_parent_access(conn,
						smb_fname,
						SEC_DIR_ADD_FILE);
			} else {

				return NT_STATUS_OBJECT_NAME_NOT_FOUND;
			}
			if (!NT_STATUS_IS_OK(status)) {
				DEBUG(10,("open_file: "
					"%s on file "
					"%s returned %s\n",
					file_existed ?
						"smbd_check_access_rights" :
						"check_parent_access",
					smb_fname_str_dbg(smb_fname),
					nt_errstr(status) ));
				return status;
			}
		}


		status = fd_open_atomic(conn, fsp, local_flags,
				unx_mode, p_file_created);
		if (!NT_STATUS_IS_OK(status)) {
			DEBUG(3,("Error opening file %s (%s) (local_flags=%d) "
				 "(flags=%d)\n", smb_fname_str_dbg(smb_fname),
				 nt_errstr(status),local_flags,flags));
			return status;
		}

		ret = SMB_VFS_FSTAT(fsp, &smb_fname->st);
		if (ret == -1) {

			DEBUG(0,("Error doing fstat on open file %s "
				"(%s)\n",
				smb_fname_str_dbg(smb_fname),
				strerror(errno) ));
			status = map_nt_error_from_unix(errno);
			fd_close(fsp);
			return status;
		}

		if (*p_file_created) {


			bool need_re_stat = false;


			if (lp_inherit_perms(SNUM(conn))) {
				inherit_access_posix_acl(conn, parent_dir,
							 smb_fname->base_name,
							 unx_mode);
				need_re_stat = true;
			}


			if (lp_inherit_owner(SNUM(conn))) {
				change_file_owner_to_parent(conn, parent_dir,
							    fsp);
				need_re_stat = true;
			}

			if (need_re_stat) {
				ret = SMB_VFS_FSTAT(fsp, &smb_fname->st);

				if (ret == -1) {
					DEBUG(0,("Error doing fstat on open file %s "
						 "(%s)\n",
						 smb_fname_str_dbg(smb_fname),
						 strerror(errno) ));
				}
			}

			notify_fname(conn, NOTIFY_ACTION_ADDED,
				     FILE_NOTIFY_CHANGE_FILE_NAME,
				     smb_fname->base_name);
		}
	} else {
		fsp->fh->fd = -1;
		if (!file_existed) {

			return NT_STATUS_OBJECT_NAME_NOT_FOUND;
		}

		status = smbd_check_access_rights(conn,
				smb_fname,
				false,
				access_mask);

		if (NT_STATUS_EQUAL(status, NT_STATUS_OBJECT_NAME_NOT_FOUND) &&
				fsp->posix_open &&
				S_ISLNK(smb_fname->st.st_ex_mode)) {


			DEBUG(10,("open_file: allowing POSIX "
				  "open on bad symlink %s\n",
				  smb_fname_str_dbg(smb_fname)));
			status = NT_STATUS_OK;
		}

		if (!NT_STATUS_IS_OK(status)) {
			DEBUG(10,("open_file: "
				"smbd_check_access_rights on file "
				"%s returned %s\n",
				smb_fname_str_dbg(smb_fname),
				nt_errstr(status) ));
			return status;
		}
	}


	if(S_ISDIR(smb_fname->st.st_ex_mode)) {
		fd_close(fsp);
		errno = EISDIR;
		return NT_STATUS_FILE_IS_A_DIRECTORY;
	}

	fsp->file_id = vfs_file_id_from_sbuf(conn, &smb_fname->st);
	fsp->vuid = req ? req->vuid : UID_FIELD_INVALID;
	fsp->file_pid = req ? req->smbpid : 0;
	fsp->can_lock = True;
	fsp->can_read = ((access_mask & FILE_READ_DATA) != 0);
	fsp->can_write =
		CAN_WRITE(conn) &&
		((access_mask & (FILE_WRITE_DATA | FILE_APPEND_DATA)) != 0);
	fsp->print_file = NULL;
	fsp->modified = False;
	fsp->sent_oplock_break = NO_BREAK_SENT;
	fsp->is_directory = False;
	if (conn->aio_write_behind_list &&
	    is_in_path(smb_fname->base_name, conn->aio_write_behind_list,
		       conn->case_sensitive)) {
		fsp->aio_write_behind = True;
	}

	fsp->wcp = NULL;

	DEBUG(2,("%s opened file %s read=%s write=%s (numopen=%d)\n",
		 conn->session_info->unix_info->unix_name,
		 smb_fname_str_dbg(smb_fname),
		 BOOLSTR(fsp->can_read), BOOLSTR(fsp->can_write),
		 conn->num_files_open));

	errno = 0;
	return NT_STATUS_OK;
}
