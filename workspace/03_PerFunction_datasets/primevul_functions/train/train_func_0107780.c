static void call_nt_transact_get_user_quota(connection_struct *conn,
					    struct smb_request *req,
					    uint16 **ppsetup,
					    uint32 setup_count,
					    char **ppparams,
					    uint32 parameter_count,
					    char **ppdata,
					    uint32 data_count,
					    uint32 max_data_count)
{
	NTSTATUS nt_status = NT_STATUS_OK;
	char *params = *ppparams;
	char *pdata = *ppdata;
	char *entry;
	int data_len=0,param_len=0;
	int qt_len=0;
	int entry_len = 0;
	files_struct *fsp = NULL;
	uint16 level = 0;
	size_t sid_len;
	DOM_SID sid;
	bool start_enum = True;
	SMB_NTQUOTA_STRUCT qt;
	SMB_NTQUOTA_LIST *tmp_list;
	SMB_NTQUOTA_HANDLE *qt_handle = NULL;

	ZERO_STRUCT(qt);


	if (conn->server_info->utok.uid != 0 && !conn->admin_user) {
		DEBUG(1,("get_user_quota: access_denied service [%s] user "
			 "[%s]\n", lp_servicename(SNUM(conn)),
			 conn->server_info->unix_name));
		reply_nterror(req, NT_STATUS_ACCESS_DENIED);
		return;
	}


	if (parameter_count < 4) {
		DEBUG(0,("TRANSACT_GET_USER_QUOTA: requires %d >= 4 bytes parameters\n",parameter_count));
		reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
		return;
	}


	fsp = file_fsp(req, SVAL(params,0));
	if (!check_fsp_ntquota_handle(conn, req, fsp)) {
		DEBUG(3,("TRANSACT_GET_USER_QUOTA: no valid QUOTA HANDLE\n"));
		reply_nterror(req, NT_STATUS_INVALID_HANDLE);
		return;
	}


	qt_handle = (SMB_NTQUOTA_HANDLE *)fsp->fake_file_handle->private_data;

	level = SVAL(params,2);


	switch (level) {
		case TRANSACT_GET_USER_QUOTA_LIST_CONTINUE:


			if (qt_handle->quota_list!=NULL &&
			    qt_handle->tmp_list==NULL) {


				free_ntquota_list(&(qt_handle->quota_list));


				param_len = 4;
				params = nttrans_realloc(ppparams, param_len);
				if(params == NULL) {
					reply_nterror(req, NT_STATUS_NO_MEMORY);
					return;
				}

				data_len = 0;
				SIVAL(params,0,data_len);

				break;
			}

			start_enum = False;

		case TRANSACT_GET_USER_QUOTA_LIST_START:

			if (qt_handle->quota_list==NULL &&
				qt_handle->tmp_list==NULL) {
				start_enum = True;
			}

			if (start_enum && vfs_get_user_ntquota_list(fsp,&(qt_handle->quota_list))!=0) {
				reply_nterror(req, NT_STATUS_INTERNAL_ERROR);
				return;
			}


			param_len = 4;
			params = nttrans_realloc(ppparams, param_len);
			if(params == NULL) {
				reply_nterror(req, NT_STATUS_NO_MEMORY);
				return;
			}


			max_data_count = MIN(max_data_count,2048);

			pdata = nttrans_realloc(ppdata, max_data_count);
			if(pdata == NULL) {
				reply_nterror(req, NT_STATUS_NO_MEMORY);
				return;
			}

			entry = pdata;


			if (start_enum) {
				qt_handle->tmp_list = qt_handle->quota_list;
			}

			tmp_list = qt_handle->tmp_list;

			for (;((tmp_list!=NULL)&&((qt_len +40+SID_MAX_SIZE)<max_data_count));
				tmp_list=tmp_list->next,entry+=entry_len,qt_len+=entry_len) {

				sid_len = ndr_size_dom_sid(
					&tmp_list->quotas->sid, NULL, 0);
				entry_len = 40 + sid_len;


				SIVAL(entry,0,entry_len);


				SIVAL(entry,4,sid_len);


				SBIG_UINT(entry,8,(uint64_t)0);


				SBIG_UINT(entry,16,tmp_list->quotas->usedspace);


				SBIG_UINT(entry,24,tmp_list->quotas->softlim);


				SBIG_UINT(entry,32,tmp_list->quotas->hardlim);


				sid_linearize(entry+40, sid_len, &tmp_list->quotas->sid);
			}

			qt_handle->tmp_list = tmp_list;


			SIVAL(entry-entry_len,0,0);

			data_len = 4+qt_len;

			SIVAL(params,0,data_len);

			break;

		case TRANSACT_GET_USER_QUOTA_FOR_SID:


			if (data_count < 8) {
				DEBUG(0,("TRANSACT_GET_USER_QUOTA_FOR_SID: requires %d >= %d bytes data\n",data_count,8));
				reply_nterror(req, NT_STATUS_INVALID_LEVEL);
				return;
			}

			sid_len = IVAL(pdata,4);

			if (sid_len > (1024*1024)) {
				reply_nterror(req, NT_STATUS_NO_MEMORY);
				return;
			}

			if (data_count < 8+sid_len) {
				DEBUG(0,("TRANSACT_GET_USER_QUOTA_FOR_SID: requires %d >= %lu bytes data\n",data_count,(unsigned long)(8+sid_len)));
				reply_nterror(req, NT_STATUS_INVALID_LEVEL);
				return;
			}

			data_len = 4+40+sid_len;

			if (max_data_count < data_len) {
				DEBUG(0,("TRANSACT_GET_USER_QUOTA_FOR_SID: max_data_count(%d) < data_len(%d)\n",
					max_data_count, data_len));
				param_len = 4;
				SIVAL(params,0,data_len);
				data_len = 0;
				nt_status = NT_STATUS_BUFFER_TOO_SMALL;
				break;
			}

			if (!sid_parse(pdata+8,sid_len,&sid)) {
				reply_nterror(req, NT_STATUS_INVALID_PARAMETER);
				return;
			}

			if (vfs_get_ntquota(fsp, SMB_USER_QUOTA_TYPE, &sid, &qt)!=0) {
				ZERO_STRUCT(qt);


			}


			param_len = 4;
			params = nttrans_realloc(ppparams, param_len);
			if(params == NULL) {
				reply_nterror(req, NT_STATUS_NO_MEMORY);
				return;
			}

			pdata = nttrans_realloc(ppdata, data_len);
			if(pdata == NULL) {
				reply_nterror(req, NT_STATUS_NO_MEMORY);
				return;
			}

			entry = pdata;


			SIVAL(params,0,data_len);


			SIVAL(entry,0,0);


			SIVAL(entry,4,sid_len);


			SBIG_UINT(entry,8,(uint64_t)0);


			SBIG_UINT(entry,16,qt.usedspace);


			SBIG_UINT(entry,24,qt.softlim);


			SBIG_UINT(entry,32,qt.hardlim);


			sid_linearize(entry+40, sid_len, &sid);

			break;

		default:
			DEBUG(0,("do_nt_transact_get_user_quota: fnum %d unknown level 0x%04hX\n",fsp->fnum,level));
			reply_nterror(req, NT_STATUS_INVALID_LEVEL);
			return;
			break;
	}

	send_nt_replies(conn, req, nt_status, params, param_len,
			pdata, data_len);
}
