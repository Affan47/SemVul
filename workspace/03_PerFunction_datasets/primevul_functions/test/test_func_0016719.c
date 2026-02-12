static NTSTATUS open_file_ntcreate(connection_struct *conn,
			    struct smb_request *req,
			    uint32 access_mask,
			    uint32 share_access,
			    uint32 create_disposition,
			    uint32 create_options,
			    uint32 new_dos_attributes,
			    int oplock_request,

			    uint32_t private_flags,
			    int *pinfo,
			    files_struct *fsp)
{
	struct smb_filename *smb_fname = fsp->fsp_name;
	int flags=0;
	int flags2=0;
	bool file_existed = VALID_STAT(smb_fname->st);
	bool def_acl = False;
	bool posix_open = False;
	bool new_file_created = False;
	bool first_open_attempt = true;
	NTSTATUS fsp_open = NT_STATUS_ACCESS_DENIED;
	mode_t new_unx_mode = (mode_t)0;
	mode_t unx_mode = (mode_t)0;
	int info;
	uint32 existing_dos_attributes = 0;
	struct timeval request_time = timeval_zero();
	struct share_mode_lock *lck = NULL;
	uint32 open_access_mask = access_mask;
	NTSTATUS status;
	char *parent_dir;
	SMB_STRUCT_STAT saved_stat = smb_fname->st;
	struct timespec old_write_time;
	struct file_id id;

	if (conn->printer) {


		if (pinfo) {
			*pinfo = FILE_WAS_CREATED;
		}

		DEBUG(10, ("open_file_ntcreate: printer open fname=%s\n",
			   smb_fname_str_dbg(smb_fname)));

		if (!req) {
			DEBUG(0,("open_file_ntcreate: printer open without "
				"an SMB request!\n"));
			return NT_STATUS_INTERNAL_ERROR;
		}

		return print_spool_open(fsp, smb_fname->base_name,
					req->vuid);
	}

	if (!parent_dirname(talloc_tos(), smb_fname->base_name, &parent_dir,
			    NULL)) {
		return NT_STATUS_NO_MEMORY;
	}

	if (new_dos_attributes & FILE_FLAG_POSIX_SEMANTICS) {
		posix_open = True;
		unx_mode = (mode_t)(new_dos_attributes & ~FILE_FLAG_POSIX_SEMANTICS);
		new_dos_attributes = 0;
	} else {


		new_dos_attributes &= ~FILE_ATTRIBUTE_DIRECTORY;


		unx_mode = unix_mode(conn, new_dos_attributes | FILE_ATTRIBUTE_ARCHIVE,
				     smb_fname, parent_dir);
	}

	DEBUG(10, ("open_file_ntcreate: fname=%s, dos_attrs=0x%x "
		   "access_mask=0x%x share_access=0x%x "
		   "create_disposition = 0x%x create_options=0x%x "
		   "unix mode=0%o oplock_request=%d private_flags = 0x%x\n",
		   smb_fname_str_dbg(smb_fname), new_dos_attributes,
		   access_mask, share_access, create_disposition,
		   create_options, (unsigned int)unx_mode, oplock_request,
		   (unsigned int)private_flags));

	if ((req == NULL) && ((oplock_request & INTERNAL_OPEN_ONLY) == 0)) {
		DEBUG(0, ("No smb request but not an internal only open!\n"));
		return NT_STATUS_INTERNAL_ERROR;
	}


	if (req) {
		void *ptr;
		if (get_deferred_open_message_state(req,
				&request_time,
				&ptr)) {


			if (is_deferred_open_async(ptr)) {
				SET_STAT_INVALID(smb_fname->st);
				file_existed = false;
			}


			remove_deferred_open_message_smb(req->sconn, req->mid);

			first_open_attempt = false;
		}
	}

	if (!posix_open) {
		new_dos_attributes &= SAMBA_ATTRIBUTES_MASK;
		if (file_existed) {
			existing_dos_attributes = dos_mode(conn, smb_fname);
		}
	}


	if (!lp_oplocks(SNUM(conn)) ||
	    IS_VETO_OPLOCK_PATH(conn, smb_fname->base_name)) {

		oplock_request &= SAMBA_PRIVATE_OPLOCK_MASK;
	}


	if (!lp_posix_pathnames() && strstr(smb_fname->base_name,".+,;=[].")) {


		DEBUG(5,("open_file_ntcreate: OS/2 long filenames are not "
			 "supported.\n"));
		if (use_nt_status()) {
			return NT_STATUS_OBJECT_NAME_NOT_FOUND;
		}
		return NT_STATUS_DOS(ERRDOS, ERRcannotopen);
	}

	switch( create_disposition ) {
		case FILE_OPEN:

			if (!file_existed) {
				DEBUG(5,("open_file_ntcreate: FILE_OPEN "
					 "requested for file %s and file "
					 "doesn't exist.\n",
					 smb_fname_str_dbg(smb_fname)));
				errno = ENOENT;
				return NT_STATUS_OBJECT_NAME_NOT_FOUND;
			}
			break;

		case FILE_OVERWRITE:


			if (!file_existed) {
				DEBUG(5,("open_file_ntcreate: FILE_OVERWRITE "
					 "requested for file %s and file "
					 "doesn't exist.\n",
					 smb_fname_str_dbg(smb_fname) ));
				errno = ENOENT;
				return NT_STATUS_OBJECT_NAME_NOT_FOUND;
			}
			break;

		case FILE_CREATE:


			if (file_existed) {
				DEBUG(5,("open_file_ntcreate: FILE_CREATE "
					 "requested for file %s and file "
					 "already exists.\n",
					 smb_fname_str_dbg(smb_fname)));
				if (S_ISDIR(smb_fname->st.st_ex_mode)) {
					errno = EISDIR;
				} else {
					errno = EEXIST;
				}
				return map_nt_error_from_unix(errno);
			}
			break;

		case FILE_SUPERSEDE:
		case FILE_OVERWRITE_IF:
		case FILE_OPEN_IF:
			break;
		default:
			return NT_STATUS_INVALID_PARAMETER;
	}

	flags2 = disposition_to_open_flags(create_disposition);


	if (!posix_open && file_existed &&
	    ((create_disposition == FILE_OVERWRITE) ||
	     (create_disposition == FILE_OVERWRITE_IF))) {
		if (!open_match_attributes(conn, existing_dos_attributes,
					   new_dos_attributes,
					   smb_fname->st.st_ex_mode,
					   unx_mode, &new_unx_mode)) {
			DEBUG(5,("open_file_ntcreate: attributes missmatch "
				 "for file %s (%x %x) (0%o, 0%o)\n",
				 smb_fname_str_dbg(smb_fname),
				 existing_dos_attributes,
				 new_dos_attributes,
				 (unsigned int)smb_fname->st.st_ex_mode,
				 (unsigned int)unx_mode ));
			errno = EACCES;
			return NT_STATUS_ACCESS_DENIED;
		}
	}

	status = smbd_calculate_access_mask(conn, smb_fname,
					false,
					access_mask,
					&access_mask);
	if (!NT_STATUS_IS_OK(status)) {
		DEBUG(10, ("open_file_ntcreate: smbd_calculate_access_mask "
			"on file %s returned %s\n",
			smb_fname_str_dbg(smb_fname), nt_errstr(status)));
		return status;
	}

	open_access_mask = access_mask;

	if (flags2 & O_TRUNC) {
		open_access_mask |= FILE_WRITE_DATA;
	}

	DEBUG(10, ("open_file_ntcreate: fname=%s, after mapping "
		   "access_mask=0x%x\n", smb_fname_str_dbg(smb_fname),
		    access_mask));


	flags = calculate_open_access_flags(access_mask, oplock_request,
					    private_flags);


#if defined(O_SYNC)
	if ((create_options & FILE_WRITE_THROUGH) && lp_strict_sync(SNUM(conn))) {
		flags2 |= O_SYNC;
	}
#endif

	if (posix_open && (access_mask & FILE_APPEND_DATA)) {
		flags2 |= O_APPEND;
	}

	if (!posix_open && !CAN_WRITE(conn)) {


		flags2 &= ~(O_CREAT|O_TRUNC);
	}

	if (first_open_attempt && lp_kernel_oplocks(SNUM(conn))) {


		flags2 |= O_NONBLOCK;
	}


	if (flags != O_RDONLY && file_existed &&
	    (!CAN_WRITE(conn) || IS_DOS_READONLY(existing_dos_attributes))) {
		DEBUG(5,("open_file_ntcreate: write access requested for "
			 "file %s on read only %s\n",
			 smb_fname_str_dbg(smb_fname),
			 !CAN_WRITE(conn) ? "share" : "file" ));
		errno = EACCES;
		return NT_STATUS_ACCESS_DENIED;
	}

	fsp->file_id = vfs_file_id_from_sbuf(conn, &smb_fname->st);
	fsp->share_access = share_access;
	fsp->fh->private_options = private_flags;
	fsp->access_mask = open_access_mask;


	fsp->posix_open = posix_open;


	fsp->oplock_type = (oplock_request & ~SAMBA_PRIVATE_OPLOCK_MASK);

	if (timeval_is_zero(&request_time)) {
		request_time = fsp->open_time;
	}


        if ((flags2 & O_CREAT) && lp_inherit_acls(SNUM(conn)) &&
	    (def_acl = directory_has_default_acl(conn, parent_dir))) {
		unx_mode = (0777 & lp_create_mask(SNUM(conn)));
	}

	DEBUG(4,("calling open_file with flags=0x%X flags2=0x%X mode=0%o, "
		"access_mask = 0x%x, open_access_mask = 0x%x\n",
		 (unsigned int)flags, (unsigned int)flags2,
		 (unsigned int)unx_mode, (unsigned int)access_mask,
		 (unsigned int)open_access_mask));

	fsp_open = open_file(fsp, conn, req, parent_dir,
			     flags|flags2, unx_mode, access_mask,
			     open_access_mask, &new_file_created);

	if (NT_STATUS_EQUAL(fsp_open, NT_STATUS_NETWORK_BUSY)) {
		struct deferred_open_record state;


		if (file_existed && S_ISFIFO(fsp->fsp_name->st.st_ex_mode)) {
			DEBUG(10, ("FIFO busy\n"));
			return NT_STATUS_NETWORK_BUSY;
		}
		if (req == NULL) {
			DEBUG(10, ("Internal open busy\n"));
			return NT_STATUS_NETWORK_BUSY;
		}


		lck = get_existing_share_mode_lock(talloc_tos(), fsp->file_id);
		if (lck == NULL) {
			state.delayed_for_oplocks = false;
			state.async_open = false;
			state.id = fsp->file_id;
			defer_open(NULL, request_time, timeval_set(0, 0),
				   req, &state);
			DEBUG(10, ("No share mode lock found after "
				   "EWOULDBLOCK, retrying sync\n"));
			return NT_STATUS_SHARING_VIOLATION;
		}

		if (!validate_oplock_types(lck)) {
			smb_panic("validate_oplock_types failed");
		}

		if (delay_for_oplock(fsp, 0, lck, false, create_disposition)) {
			schedule_defer_open(lck, request_time, req);
			TALLOC_FREE(lck);
			DEBUG(10, ("Sent oplock break request to kernel "
				   "oplock holder\n"));
			return NT_STATUS_SHARING_VIOLATION;
		}


		state.delayed_for_oplocks = false;
		state.async_open = false;
		state.id = lck->data->id;
		defer_open(lck, request_time, timeval_set(0, 0), req, &state);
		TALLOC_FREE(lck);
		DEBUG(10, ("No Samba oplock around after EWOULDBLOCK. "
			   "Retrying sync\n"));
		return NT_STATUS_SHARING_VIOLATION;
	}

	if (!NT_STATUS_IS_OK(fsp_open)) {
		if (NT_STATUS_EQUAL(fsp_open, NT_STATUS_RETRY)) {
			schedule_async_open(request_time, req);
		}
		return fsp_open;
	}

	if (file_existed && !check_same_dev_ino(&saved_stat, &smb_fname->st)) {


		fd_close(fsp);
		DEBUG(1,("open_file_ntcreate: file %s - dev/ino mismatch. "
			"Old (dev=0x%llu, ino =0x%llu). "
			"New (dev=0x%llu, ino=0x%llu). Failing open "
			" with NT_STATUS_ACCESS_DENIED.\n",
			 smb_fname_str_dbg(smb_fname),
			 (unsigned long long)saved_stat.st_ex_dev,
			 (unsigned long long)saved_stat.st_ex_ino,
			 (unsigned long long)smb_fname->st.st_ex_dev,
			 (unsigned long long)smb_fname->st.st_ex_ino));
		return NT_STATUS_ACCESS_DENIED;
	}

	old_write_time = smb_fname->st.st_ex_mtime;


	id = fsp->file_id;

	lck = get_share_mode_lock(talloc_tos(), id,
				  conn->connectpath,
				  smb_fname, &old_write_time);

	if (lck == NULL) {
		DEBUG(0, ("open_file_ntcreate: Could not get share "
			  "mode lock for %s\n",
			  smb_fname_str_dbg(smb_fname)));
		fd_close(fsp);
		return NT_STATUS_SHARING_VIOLATION;
	}


	if (!validate_oplock_types(lck)) {
		smb_panic("validate_oplock_types failed");
	}

	if (has_delete_on_close(lck, fsp->name_hash)) {
		TALLOC_FREE(lck);
		fd_close(fsp);
		return NT_STATUS_DELETE_PENDING;
	}

	status = open_mode_check(conn, lck,
				 access_mask, share_access);

	if (NT_STATUS_EQUAL(status, NT_STATUS_SHARING_VIOLATION) ||
	    (lck->data->num_share_modes > 0)) {


		file_existed = true;
	}

	if ((req != NULL) &&
	    delay_for_oplock(
		    fsp, oplock_request, lck,
		    NT_STATUS_EQUAL(status, NT_STATUS_SHARING_VIOLATION),
		    create_disposition)) {
		schedule_defer_open(lck, request_time, req);
		TALLOC_FREE(lck);
		fd_close(fsp);
		return NT_STATUS_SHARING_VIOLATION;
	}

	if (!NT_STATUS_IS_OK(status)) {
		uint32 can_access_mask;
		bool can_access = True;

		SMB_ASSERT(NT_STATUS_EQUAL(status, NT_STATUS_SHARING_VIOLATION));


		if (private_flags &
		    (NTCREATEX_OPTIONS_PRIVATE_DENY_DOS|
		     NTCREATEX_OPTIONS_PRIVATE_DENY_FCB)) {
			if (req == NULL) {
				DEBUG(0, ("DOS open without an SMB "
					  "request!\n"));
				TALLOC_FREE(lck);
				fd_close(fsp);
				return NT_STATUS_INTERNAL_ERROR;
			}


			status = fcb_or_dos_open(req,
						 conn,
						 fsp,
						 smb_fname,
						 id,
						 req->smbpid,
						 req->vuid,
						 access_mask,
						 share_access,
						 create_options);

			if (NT_STATUS_IS_OK(status)) {
				TALLOC_FREE(lck);
				if (pinfo) {
					*pinfo = FILE_WAS_OPENED;
				}
				return NT_STATUS_OK;
			}
		}


		if (flags & O_RDWR) {
			can_access_mask = FILE_READ_DATA|FILE_WRITE_DATA;
		} else if (flags & O_WRONLY) {
			can_access_mask = FILE_WRITE_DATA;
		} else {
			can_access_mask = FILE_READ_DATA;
		}

		if (((can_access_mask & FILE_WRITE_DATA) &&
		     !CAN_WRITE(conn)) ||
		    !NT_STATUS_IS_OK(smbd_check_access_rights(conn,
							      smb_fname,
							      false,
							      can_access_mask))) {
			can_access = False;
		}


		if (!(oplock_request & INTERNAL_OPEN_ONLY) &&
		    !conn->sconn->using_smb2 &&
		    lp_defer_sharing_violations()) {
			struct timeval timeout;
			struct deferred_open_record state;
			int timeout_usecs;


			timeout_usecs = lp_parm_int(SNUM(conn),
						    "smbd","sharedelay",
						    SHARING_VIOLATION_USEC_WAIT);


			timeout = timeval_set(0, timeout_usecs);


			state.delayed_for_oplocks = False;
			state.async_open = false;
			state.id = id;

			if ((req != NULL)
			    && !request_timed_out(request_time,
						  timeout)) {
				defer_open(lck, request_time, timeout,
					   req, &state);
			}
		}

		TALLOC_FREE(lck);
		fd_close(fsp);
		if (can_access) {


			status = NT_STATUS_SHARING_VIOLATION;
		} else {
			status = NT_STATUS_ACCESS_DENIED;
		}
		return status;
	}

	grant_fsp_oplock_type(fsp, lck, oplock_request);


	if (!new_file_created && clear_ads(create_disposition) &&
	    !is_ntfs_stream_smb_fname(smb_fname)) {
		status = delete_all_streams(conn, smb_fname->base_name);
		if (!NT_STATUS_IS_OK(status)) {
			TALLOC_FREE(lck);
			fd_close(fsp);
			return status;
		}
	}


	if (fsp->fh->fd != -1 && lp_kernel_share_modes(SNUM(conn))) {
		int ret_flock;
		ret_flock = SMB_VFS_KERNEL_FLOCK(fsp, share_access, access_mask);
		if(ret_flock == -1 ){

			TALLOC_FREE(lck);
			fd_close(fsp);

			return NT_STATUS_SHARING_VIOLATION;
		}
	}


	if (conn->sconn->using_smb2) {


		fsp->access_mask = access_mask;
	} else {

		fsp->access_mask = access_mask | FILE_READ_ATTRIBUTES;
	}

	if (file_existed) {

		if (is_stat_open(open_access_mask)) {
			fsp->oplock_type = NO_OPLOCK;
		}
	}

	if (new_file_created) {
		info = FILE_WAS_CREATED;
	} else {
		if (flags2 & O_TRUNC) {
			info = FILE_WAS_OVERWRITTEN;
		} else {
			info = FILE_WAS_OPENED;
		}
	}

	if (pinfo) {
		*pinfo = info;
	}


	status = set_file_oplock(fsp);
	if (!NT_STATUS_IS_OK(status)) {


		fsp->oplock_type = NO_OPLOCK;
	}

	if (!set_share_mode(lck, fsp, get_current_uid(conn),
			    req ? req->mid : 0,
			    fsp->oplock_type)) {
		TALLOC_FREE(lck);
		fd_close(fsp);
		return NT_STATUS_NO_MEMORY;
	}


	if (create_options & FILE_DELETE_ON_CLOSE) {

		status = can_set_delete_on_close(fsp, new_dos_attributes);

		if (!NT_STATUS_IS_OK(status)) {

			del_share_mode(lck, fsp);
			TALLOC_FREE(lck);
			fd_close(fsp);
			return status;
		}


		fsp->initial_delete_on_close = True;
	}

	if (info != FILE_WAS_OPENED) {

		if (lp_map_archive(SNUM(conn)) ||
		    lp_store_dos_attributes(SNUM(conn))) {
			if (!posix_open) {
				if (file_set_dosmode(conn, smb_fname,
					    new_dos_attributes | FILE_ATTRIBUTE_ARCHIVE,
					    parent_dir, true) == 0) {
					unx_mode = smb_fname->st.st_ex_mode;
				}
			}
		}
	}


	if (posix_open) {

		fsp->is_sparse = true;
	} else {
		fsp->is_sparse = (file_existed &&
			(existing_dos_attributes & FILE_ATTRIBUTE_SPARSE));
	}


	if (!posix_open && new_file_created && !def_acl) {

		int saved_errno = errno;


		if (SMB_VFS_FCHMOD_ACL(fsp, unx_mode) == -1 &&
		    errno == ENOSYS) {
			errno = saved_errno;
		}

	} else if (new_unx_mode) {

		int ret = -1;


		{
			int saved_errno = errno;

			ret = SMB_VFS_FCHMOD_ACL(fsp, new_unx_mode);

			if (ret == -1 && errno == ENOSYS) {
				errno = saved_errno;
			} else {
				DEBUG(5, ("open_file_ntcreate: reset "
					  "attributes of file %s to 0%o\n",
					  smb_fname_str_dbg(smb_fname),
					  (unsigned int)new_unx_mode));
				ret = 0;
			}
		}

		if ((ret == -1) &&
		    (SMB_VFS_FCHMOD(fsp, new_unx_mode) == -1))
			DEBUG(5, ("open_file_ntcreate: failed to reset "
				  "attributes of file %s to 0%o\n",
				  smb_fname_str_dbg(smb_fname),
				  (unsigned int)new_unx_mode));
	}

	TALLOC_FREE(lck);

	return NT_STATUS_OK;
}
