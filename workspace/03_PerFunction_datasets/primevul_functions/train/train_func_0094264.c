static void call_trans2mkdir(connection_struct *conn, struct smb_request *req,
			     char **pparams, int total_params,
			     char **ppdata, int total_data,
			     unsigned int max_data_bytes)
{
	struct files_struct *fsp = NULL;
	struct smb_filename *smb_dname = NULL;
	char *params = *pparams;
	char *pdata = *ppdata;
	char *directory = NULL;
	NTSTATUS status = NT_STATUS_OK;
	struct ea_list *ea_list = NULL;
	uint32_t ucf_flags = ucf_flags_from_smb_request(req);
	TALLOC_CTX *ctx = talloc_tos();

	if (!CAN_WRITE(conn)) {
		reply_nterror(req, NT_STATUS_ACCESS_DENIED);
		return;
	}

	if (total_params < 5) {
		reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
		return;
	}

	if (req->posix_pathnames) {
		srvstr_get_path_posix(ctx,
			params,
			req->flags2,
			&directory,
			&params[4],
			total_params - 4,
			STR_TERMINATE,
			&status);
	} else {
		srvstr_get_path(ctx,
			params,
			req->flags2,
			&directory,
			&params[4],
			total_params - 4,
			STR_TERMINATE,
			&status);
	}
	if (!NT_STATUS_IS_OK(status)) {
		reply_nterror(req, status);
		return;
	}

	DEBUG(3,("call_trans2mkdir : name = %s\n", directory));

	status = filename_convert(ctx,
				conn,
				directory,
				ucf_flags,
				0,
				&smb_dname);

	if (!NT_STATUS_IS_OK(status)) {
		if (NT_STATUS_EQUAL(status,NT_STATUS_PATH_NOT_COVERED)) {
			reply_botherror(req,
				NT_STATUS_PATH_NOT_COVERED,
				ERRSRV, ERRbadpath);
			return;
		}
		reply_nterror(req, status);
		return;
        }


	if (total_data && (total_data != 4)) {

		if (total_data < 10) {
			reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
			goto out;
		}

		if (IVAL(pdata,0) > total_data) {
			DEBUG(10,("call_trans2mkdir: bad total data size (%u) > %u\n",
				IVAL(pdata,0), (unsigned int)total_data));
			reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
			goto out;
		}

		ea_list = read_ea_list(talloc_tos(), pdata + 4,
				       total_data - 4);
		if (!ea_list) {
			reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
			goto out;
		}

		if (!lp_ea_support(SNUM(conn))) {
			reply_nterror(req, NT_STATUS_EAS_NOT_SUPPORTED);
			goto out;
		}
	}


	status = SMB_VFS_CREATE_FILE(
		conn,
		req,
		smb_dname,
		MAXIMUM_ALLOWED_ACCESS,
		FILE_SHARE_NONE,
		FILE_CREATE,
		FILE_DIRECTORY_FILE,
		FILE_ATTRIBUTE_DIRECTORY,
		0,
		NULL,
		0,
		0,
		NULL,
		NULL,
		&fsp,
		NULL,
		NULL, NULL);
	if (!NT_STATUS_IS_OK(status)) {
		reply_nterror(req, status);
		goto out;
	}


	if (ea_list) {
		status = set_ea(conn, fsp, ea_list);
		if (!NT_STATUS_IS_OK(status)) {
			reply_nterror(req, status);
			goto out;
		}
	}


	*pparams = (char *)SMB_REALLOC(*pparams,2);
	if(*pparams == NULL) {
		reply_nterror(req, NT_STATUS_NO_MEMORY);
		goto out;
	}
	params = *pparams;

	SSVAL(params,0,0);

	send_trans2_replies(conn, req, NT_STATUS_OK, params, 2, *ppdata, 0, max_data_bytes);

 out:
	if (fsp != NULL) {
		close_file(NULL, fsp, NORMAL_CLOSE);
		fsp = NULL;
	}
	TALLOC_FREE(smb_dname);
	return;
}
