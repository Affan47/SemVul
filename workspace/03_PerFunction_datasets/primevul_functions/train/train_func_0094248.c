static void call_trans2findfirst(connection_struct *conn,
				 struct smb_request *req,
				 char **pparams, int total_params,
				 char **ppdata, int total_data,
				 unsigned int max_data_bytes)
{


	struct smb_filename *smb_dname = NULL;
	char *params = *pparams;
	char *pdata = *ppdata;
	char *data_end;
	uint32_t dirtype;
	int maxentries;
	uint16_t findfirst_flags;
	bool close_after_first;
	bool close_if_end;
	bool requires_resume_key;
	int info_level;
	char *directory = NULL;
	char *mask = NULL;
	char *p;
	int last_entry_off=0;
	int dptr_num = -1;
	int numentries = 0;
	int i;
	bool finished = False;
	bool dont_descend = False;
	bool out_of_space = False;
	int space_remaining;
	struct ea_list *ea_list = NULL;
	NTSTATUS ntstatus = NT_STATUS_OK;
	bool ask_sharemode = lp_smbd_search_ask_sharemode(SNUM(conn));
	struct smbd_server_connection *sconn = req->sconn;
	uint32_t ucf_flags = UCF_ALWAYS_ALLOW_WCARD_LCOMP |
			ucf_flags_from_smb_request(req);
	bool backup_priv = false;
	bool as_root = false;
	files_struct *fsp = NULL;
	const struct loadparm_substitution *lp_sub =
		loadparm_s3_global_substitution();
	int ret;

	if (total_params < 13) {
		reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
		goto out;
	}

	dirtype = SVAL(params,0);
	maxentries = SVAL(params,2);
	findfirst_flags = SVAL(params,4);
	close_after_first = (findfirst_flags & FLAG_TRANS2_FIND_CLOSE);
	close_if_end = (findfirst_flags & FLAG_TRANS2_FIND_CLOSE_IF_END);
	requires_resume_key = (findfirst_flags & FLAG_TRANS2_FIND_REQUIRE_RESUME);
	backup_priv = ((findfirst_flags & FLAG_TRANS2_FIND_BACKUP_INTENT) &&
				security_token_has_privilege(get_current_nttok(conn),
						SEC_PRIV_BACKUP));

	info_level = SVAL(params,6);

	DEBUG(3,("call_trans2findfirst: dirtype = %x, maxentries = %d, close_after_first=%d, \
close_if_end = %d requires_resume_key = %d backup_priv = %d level = 0x%x, max_data_bytes = %d\n",
		(unsigned int)dirtype, maxentries, close_after_first, close_if_end, requires_resume_key,
		(int)backup_priv,
		info_level, max_data_bytes));

	if (!maxentries) {

		maxentries = 1;
	}

	switch (info_level) {
		case SMB_FIND_INFO_STANDARD:
		case SMB_FIND_EA_SIZE:
		case SMB_FIND_EA_LIST:
		case SMB_FIND_FILE_DIRECTORY_INFO:
		case SMB_FIND_FILE_FULL_DIRECTORY_INFO:
		case SMB_FIND_FILE_NAMES_INFO:
		case SMB_FIND_FILE_BOTH_DIRECTORY_INFO:
		case SMB_FIND_ID_FULL_DIRECTORY_INFO:
		case SMB_FIND_ID_BOTH_DIRECTORY_INFO:
			break;
		case SMB_FIND_FILE_UNIX:
		case SMB_FIND_FILE_UNIX_INFO2:
			if (!lp_unix_extensions()) {
				reply_nterror(req, NT_STATUS_INVALID_LEVEL);
				goto out;
			}
			break;
		default:
			reply_nterror(req, NT_STATUS_INVALID_LEVEL);
			goto out;
	}

	if (req->posix_pathnames) {

		ask_sharemode = false;
	}

	if (req->posix_pathnames) {
		srvstr_get_path_posix(talloc_tos(),
				params,
				req->flags2,
				&directory,
				params+12,
				total_params - 12,
				STR_TERMINATE,
				&ntstatus);
	} else {
		srvstr_get_path(talloc_tos(),
				params,
				req->flags2,
				&directory,
				params+12,
				total_params - 12,
				STR_TERMINATE,
				&ntstatus);
	}
	if (!NT_STATUS_IS_OK(ntstatus)) {
		reply_nterror(req, ntstatus);
		goto out;
	}

	if (backup_priv) {
		become_root();
		as_root = true;
		ntstatus = filename_convert_with_privilege(talloc_tos(),
				conn,
				req,
				directory,
				ucf_flags,
				&smb_dname);
	} else {
		ntstatus = filename_convert(talloc_tos(), conn,
				    directory,
				    ucf_flags,
				    0,
				    &smb_dname);
	}

	if (!NT_STATUS_IS_OK(ntstatus)) {
		if (NT_STATUS_EQUAL(ntstatus,NT_STATUS_PATH_NOT_COVERED)) {
			reply_botherror(req, NT_STATUS_PATH_NOT_COVERED,
					ERRSRV, ERRbadpath);
			goto out;
		}
		reply_nterror(req, ntstatus);
		goto out;
	}


	if (smb_dname->fsp != NULL) {
		ntstatus = fd_close(smb_dname->fsp);
		if (!NT_STATUS_IS_OK(ntstatus)) {
			reply_nterror(req, ntstatus);
			goto out;
		}


		file_free(req, smb_dname->fsp);
		SMB_ASSERT(smb_dname->fsp == NULL);
	}

	mask = get_original_lcomp(talloc_tos(),
				conn,
				directory,
				ucf_flags);
	if (mask == NULL) {
		reply_nterror(req, NT_STATUS_NO_MEMORY);
		goto out;
	}

	directory = smb_dname->base_name;

	p = strrchr_m(directory,'/');
	if(p == NULL) {

		if((directory[0] == '.') && (directory[1] == '\0')) {
			mask = talloc_strdup(talloc_tos(),"*");
			if (!mask) {
				reply_nterror(req, NT_STATUS_NO_MEMORY);
				goto out;
			}
		}
	} else {
		*p = 0;
	}

	if (p == NULL || p == directory) {
		struct smb_filename *old_name = smb_dname;


		smb_dname = synthetic_smb_fname(talloc_tos(),
						".",
						NULL,
						&old_name->st,
						old_name->twrp,
						old_name->flags);
		TALLOC_FREE(old_name);
		if (smb_dname == NULL) {
			reply_nterror(req, NT_STATUS_NO_MEMORY);
			goto out;
		}
		directory = smb_dname->base_name;
	}

	DEBUG(5,("dir=%s, mask = %s\n",directory, mask));

	if (info_level == SMB_FIND_EA_LIST) {
		uint32_t ea_size;

		if (total_data < 4) {
			reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
			goto out;
		}

		ea_size = IVAL(pdata,0);
		if (ea_size != total_data) {
			DEBUG(4,("call_trans2findfirst: Rejecting EA request with incorrect \
total_data=%u (should be %u)\n", (unsigned int)total_data, (unsigned int)IVAL(pdata,0) ));
			reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
			goto out;
		}

		if (!lp_ea_support(SNUM(conn))) {
			reply_nterror(req, NT_STATUS_EAS_NOT_SUPPORTED);
			goto out;
		}


		ea_list = read_ea_name_list(talloc_tos(), pdata + 4, ea_size - 4);
		if (!ea_list) {
			reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
			goto out;
		}
	}

	if (max_data_bytes + DIR_ENTRY_SAFETY_MARGIN < max_data_bytes) {
		reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
		goto out;
	}

	*ppdata = (char *)SMB_REALLOC(
		*ppdata, max_data_bytes + DIR_ENTRY_SAFETY_MARGIN);
	if(*ppdata == NULL ) {
		reply_nterror(req, NT_STATUS_NO_MEMORY);
		goto out;
	}
	pdata = *ppdata;
	data_end = pdata + max_data_bytes + DIR_ENTRY_SAFETY_MARGIN - 1;


	memset(pdata + total_data, 0, ((max_data_bytes + DIR_ENTRY_SAFETY_MARGIN) - total_data));

	*pparams = (char *)SMB_REALLOC(*pparams, 10);
	if (*pparams == NULL) {
		reply_nterror(req, NT_STATUS_NO_MEMORY);
		goto out;
	}
	params = *pparams;


	ret = vfs_stat(conn, smb_dname);
	if (ret == -1) {
		ntstatus = map_nt_error_from_unix(errno);
		reply_nterror(req, ntstatus);
		goto out;
	}

	ntstatus = openat_pathref_fsp(conn->cwd_fsp, smb_dname);
	if (!NT_STATUS_IS_OK(ntstatus)) {
		reply_nterror(req, ntstatus);
		goto out;
	}


	ntstatus = SMB_VFS_CREATE_FILE(
			conn,
			req,
			smb_dname,
			FILE_LIST_DIRECTORY,
			FILE_SHARE_READ|
			FILE_SHARE_WRITE,
			FILE_OPEN,
			FILE_DIRECTORY_FILE,
			FILE_ATTRIBUTE_DIRECTORY,
			NO_OPLOCK,
			NULL,
			0,
			0,
			NULL,
			NULL,
			&fsp,
			NULL,
			NULL,
			NULL);

	if (!NT_STATUS_IS_OK(ntstatus)) {
		DBG_ERR("failed to open directory %s\n",
			smb_fname_str_dbg(smb_dname));
		reply_nterror(req, ntstatus);
		goto out;
	}


	ntstatus = dptr_create(conn,
				req,
				fsp,
				False,
				True,
				req->smbpid,
				mask,
				dirtype,
				&fsp->dptr);

	if (!NT_STATUS_IS_OK(ntstatus)) {


		close_file(NULL, fsp, NORMAL_CLOSE);
		fsp = NULL;
		reply_nterror(req, ntstatus);
		goto out;
	}

	if (backup_priv) {


		dptr_set_priv(fsp->dptr);
	}

	dptr_num = dptr_dnum(fsp->dptr);
	DEBUG(4,("dptr_num is %d, wcard = %s, attr = %d\n", dptr_num, mask, dirtype));


	DEBUG(8,("dirpath=<%s> dontdescend=<%s>\n",
		 directory,lp_dont_descend(talloc_tos(), lp_sub, SNUM(conn))));
	if (in_list(directory,
		    lp_dont_descend(talloc_tos(), lp_sub, SNUM(conn)),
			conn->case_sensitive)) {
		dont_descend = True;
	}

	p = pdata;
	space_remaining = max_data_bytes;
	out_of_space = False;

	for (i=0;(i<maxentries) && !finished && !out_of_space;i++) {
		bool got_exact_match = False;


		if (space_remaining < DIRLEN_GUESS && numentries > 0) {
			out_of_space = True;
			finished = False;
		} else {
			ntstatus = get_lanman2_dir_entry(talloc_tos(),
					conn,
					fsp->dptr,
					req->flags2,
					mask,dirtype,info_level,
					requires_resume_key,dont_descend,
					ask_sharemode,
					&p,pdata,data_end,
					space_remaining,
					&got_exact_match,
					&last_entry_off, ea_list);
			if (NT_STATUS_EQUAL(ntstatus,
					NT_STATUS_ILLEGAL_CHARACTER)) {


				continue;
			}
			if (NT_STATUS_EQUAL(ntstatus, STATUS_MORE_ENTRIES)) {
				out_of_space = true;
			} else {
				finished = !NT_STATUS_IS_OK(ntstatus);
			}
		}

		if (!finished && !out_of_space)
			numentries++;


		if(got_exact_match)
			finished = True;


		if (PTR_DIFF(p,pdata) > max_data_bytes) {
			space_remaining = 0;
			out_of_space = true;
		} else {
			space_remaining = max_data_bytes - PTR_DIFF(p,pdata);
		}
	}


	if(close_after_first || (finished && close_if_end)) {
		DEBUG(5,("call_trans2findfirst - (2) closing dptr_num %d\n", dptr_num));
		dptr_num = -1;
		close_file(NULL, fsp, NORMAL_CLOSE);
		fsp = NULL;
	}


	if(numentries == 0) {
		dptr_num = -1;


		if (fsp != NULL) {
			close_file(NULL, fsp, NORMAL_CLOSE);
			fsp = NULL;
		}
		if (get_Protocol() < PROTOCOL_NT1) {
			reply_force_doserror(req, ERRDOS, ERRnofiles);
			goto out;
		} else {
			reply_botherror(req, NT_STATUS_NO_SUCH_FILE,
					ERRDOS, ERRbadfile);
			goto out;
		}
	}


	SSVAL(params,0,dptr_num);
	SSVAL(params,2,numentries);
	SSVAL(params,4,finished);
	SSVAL(params,6,0);
	SSVAL(params,8,last_entry_off);

	send_trans2_replies(conn, req, NT_STATUS_OK, params, 10, pdata, PTR_DIFF(p,pdata),
			    max_data_bytes);

	if ((! *directory) && dptr_path(sconn, dptr_num)) {
		directory = talloc_strdup(talloc_tos(),dptr_path(sconn, dptr_num));
		if (!directory) {
			reply_nterror(req, NT_STATUS_NO_MEMORY);
		}
	}

	DEBUG( 4, ( "%s mask=%s directory=%s dirtype=%d numentries=%d\n",
		smb_fn_name(req->cmd),
		mask, directory, dirtype, numentries ) );


	if(!mangle_is_8_3_wildcards( mask, False, conn->params)) {
		char mangled_name[13];
		name_to_8_3(mask, mangled_name, True, conn->params);
	}
 out:

	if (as_root) {
		unbecome_root();
	}

	TALLOC_FREE(smb_dname);
	return;
}
