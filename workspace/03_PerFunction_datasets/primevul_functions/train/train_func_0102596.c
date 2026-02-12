NTSTATUS set_nt_acl(files_struct *fsp, uint32 security_info_sent, SEC_DESC *psd)
{
	connection_struct *conn = fsp->conn;
	uid_t user = (uid_t)-1;
	gid_t grp = (gid_t)-1;
	SMB_STRUCT_STAT sbuf;
	DOM_SID file_owner_sid;
	DOM_SID file_grp_sid;
	canon_ace *file_ace_list = NULL;
	canon_ace *dir_ace_list = NULL;
	bool acl_perms = False;
	mode_t orig_mode = (mode_t)0;
	NTSTATUS status;
	bool set_acl_as_root = false;
	bool acl_set_support = false;
	bool ret = false;

	DEBUG(10,("set_nt_acl: called for file %s\n", fsp->fsp_name ));

	if (!CAN_WRITE(conn)) {
		DEBUG(10,("set acl rejected on read-only share\n"));
		return NT_STATUS_MEDIA_WRITE_PROTECTED;
	}


	if(fsp->is_directory || fsp->fh->fd == -1) {
		if(SMB_VFS_STAT(fsp->conn,fsp->fsp_name, &sbuf) != 0)
			return map_nt_error_from_unix(errno);
	} else {
		if(SMB_VFS_FSTAT(fsp, &sbuf) != 0)
			return map_nt_error_from_unix(errno);
	}


	orig_mode = sbuf.st_mode;


	status = unpack_nt_owners( SNUM(conn), &user, &grp, security_info_sent, psd);
	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}


	if (((user != (uid_t)-1) && (sbuf.st_uid != user)) || (( grp != (gid_t)-1) && (sbuf.st_gid != grp))) {

		DEBUG(3,("set_nt_acl: chown %s. uid = %u, gid = %u.\n",
				fsp->fsp_name, (unsigned int)user, (unsigned int)grp ));

		if(try_chown( fsp->conn, fsp->fsp_name, user, grp) == -1) {
			DEBUG(3,("set_nt_acl: chown %s, %u, %u failed. Error = %s.\n",
				fsp->fsp_name, (unsigned int)user, (unsigned int)grp, strerror(errno) ));
			if (errno == EPERM) {
				return NT_STATUS_INVALID_OWNER;
			}
			return map_nt_error_from_unix(errno);
		}


		if(fsp->is_directory) {
			if(SMB_VFS_STAT(fsp->conn, fsp->fsp_name, &sbuf) != 0) {
				return map_nt_error_from_unix(errno);
			}
		} else {

			int sret;

			if(fsp->fh->fd == -1)
				sret = SMB_VFS_STAT(fsp->conn, fsp->fsp_name, &sbuf);
			else
				sret = SMB_VFS_FSTAT(fsp, &sbuf);

			if(sret != 0)
				return map_nt_error_from_unix(errno);
		}


		orig_mode = sbuf.st_mode;


		set_acl_as_root = true;
	}

	create_file_sids(&sbuf, &file_owner_sid, &file_grp_sid);

	acl_perms = unpack_canon_ace( fsp, &sbuf, &file_owner_sid, &file_grp_sid,
					&file_ace_list, &dir_ace_list, security_info_sent, psd);


	if (!file_ace_list && !dir_ace_list) {
		return NT_STATUS_OK;
	}

	if (!acl_perms) {
		DEBUG(3,("set_nt_acl: cannot set permissions\n"));
		free_canon_ace_list(file_ace_list);
		free_canon_ace_list(dir_ace_list);
		return NT_STATUS_ACCESS_DENIED;
	}


	if(!(security_info_sent & DACL_SECURITY_INFORMATION) || (psd->dacl == NULL)) {
		free_canon_ace_list(file_ace_list);
		free_canon_ace_list(dir_ace_list);
		return NT_STATUS_OK;
	}


	if (acl_perms && file_ace_list) {
		if (set_acl_as_root) {
			become_root();
		}
		ret = set_canon_ace_list(fsp, file_ace_list, False, &sbuf, &acl_set_support);
		if (set_acl_as_root) {
			unbecome_root();
		}
		if (acl_set_support && ret == false) {
			DEBUG(3,("set_nt_acl: failed to set file acl on file %s (%s).\n", fsp->fsp_name, strerror(errno) ));
			free_canon_ace_list(file_ace_list);
			free_canon_ace_list(dir_ace_list);
			return map_nt_error_from_unix(errno);
		}
	}

	if (acl_perms && acl_set_support && fsp->is_directory) {
		if (dir_ace_list) {
			if (set_acl_as_root) {
				become_root();
			}
			ret = set_canon_ace_list(fsp, dir_ace_list, True, &sbuf, &acl_set_support);
			if (set_acl_as_root) {
				unbecome_root();
			}
			if (ret == false) {
				DEBUG(3,("set_nt_acl: failed to set default acl on directory %s (%s).\n", fsp->fsp_name, strerror(errno) ));
				free_canon_ace_list(file_ace_list);
				free_canon_ace_list(dir_ace_list);
				return map_nt_error_from_unix(errno);
			}
		} else {
			int sret = -1;


			if (set_acl_as_root) {
				become_root();
			}
			sret = SMB_VFS_SYS_ACL_DELETE_DEF_FILE(conn, fsp->fsp_name);
			if (set_acl_as_root) {
				unbecome_root();
			}
			if (sret == -1) {
				if (acl_group_override(conn, &sbuf, fsp->fsp_name)) {
					DEBUG(5,("set_nt_acl: acl group control on and "
						"current user in file %s primary group. Override delete_def_acl\n",
						fsp->fsp_name ));

					become_root();
					sret = SMB_VFS_SYS_ACL_DELETE_DEF_FILE(conn, fsp->fsp_name);
					unbecome_root();
				}

				if (sret == -1) {
					DEBUG(3,("set_nt_acl: sys_acl_delete_def_file failed (%s)\n", strerror(errno)));
					free_canon_ace_list(file_ace_list);
					free_canon_ace_list(dir_ace_list);
					return map_nt_error_from_unix(errno);
				}
			}
		}
	}

	if (acl_set_support) {
		if (set_acl_as_root) {
			become_root();
		}
		store_inheritance_attributes(fsp, file_ace_list, dir_ace_list,
				(psd->type & SE_DESC_DACL_PROTECTED) ? True : False);
		if (set_acl_as_root) {
			unbecome_root();
		}
	}


	if(!acl_set_support && acl_perms) {
		mode_t posix_perms;

		if (!convert_canon_ace_to_posix_perms( fsp, file_ace_list, &posix_perms)) {
			free_canon_ace_list(file_ace_list);
			free_canon_ace_list(dir_ace_list);
			DEBUG(3,("set_nt_acl: failed to convert file acl to posix permissions for file %s.\n",
				fsp->fsp_name ));
			return NT_STATUS_ACCESS_DENIED;
		}

		if (orig_mode != posix_perms) {
			int sret = -1;

			DEBUG(3,("set_nt_acl: chmod %s. perms = 0%o.\n",
				fsp->fsp_name, (unsigned int)posix_perms ));

			if (set_acl_as_root) {
				become_root();
			}
			sret = SMB_VFS_CHMOD(conn,fsp->fsp_name, posix_perms);
			if (set_acl_as_root) {
				unbecome_root();
			}
			if(sret == -1) {
				if (acl_group_override(conn, &sbuf, fsp->fsp_name)) {
					DEBUG(5,("set_nt_acl: acl group control on and "
						"current user in file %s primary group. Override chmod\n",
						fsp->fsp_name ));

					become_root();
					sret = SMB_VFS_CHMOD(conn,fsp->fsp_name, posix_perms);
					unbecome_root();
				}

				if (sret == -1) {
					DEBUG(3,("set_nt_acl: chmod %s, 0%o failed. Error = %s.\n",
						fsp->fsp_name, (unsigned int)posix_perms, strerror(errno) ));
					free_canon_ace_list(file_ace_list);
					free_canon_ace_list(dir_ace_list);
					return map_nt_error_from_unix(errno);
				}
			}
		}
	}

	free_canon_ace_list(file_ace_list);
	free_canon_ace_list(dir_ace_list);
	return NT_STATUS_OK;
}
