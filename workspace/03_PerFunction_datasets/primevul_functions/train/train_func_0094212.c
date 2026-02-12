static NTSTATUS smbd_marshall_dir_entry(TALLOC_CTX *ctx,
				    connection_struct *conn,
				    uint16_t flags2,
				    uint32_t info_level,
				    struct ea_list *name_list,
				    bool check_mangled_names,
				    bool requires_resume_key,
				    uint32_t mode,
				    const char *fname,
				    const struct smb_filename *smb_fname,
				    int space_remaining,
				    uint8_t align,
				    bool do_pad,
				    char *base_data,
				    char **ppdata,
				    char *end_data,
				    uint64_t *last_entry_off)
{
	char *p, *q, *pdata = *ppdata;
	uint32_t reskey=0;
	uint64_t file_size = 0;
	uint64_t allocation_size = 0;
	uint64_t file_id = 0;
	size_t len = 0;
	struct timespec mdate_ts = {0};
	struct timespec adate_ts = {0};
	struct timespec cdate_ts = {0};
	struct timespec create_date_ts = {0};
	time_t mdate = (time_t)0, adate = (time_t)0, create_date = (time_t)0;
	char *nameptr;
	char *last_entry_ptr;
	bool was_8_3;
	int off;
	int pad = 0;
	NTSTATUS status;
	struct readdir_attr_data *readdir_attr_data = NULL;

	if (!(mode & FILE_ATTRIBUTE_DIRECTORY)) {
		file_size = get_file_size_stat(&smb_fname->st);
	}
	allocation_size = SMB_VFS_GET_ALLOC_SIZE(conn, NULL, &smb_fname->st);


	if (smb_fname->fsp != NULL &&
	    !(mode & FILE_ATTRIBUTE_REPARSE_POINT)) {
		status = SMB_VFS_FREADDIR_ATTR(smb_fname->fsp,
					       ctx,
					       &readdir_attr_data);
		if (!NT_STATUS_IS_OK(status)) {
			if (!NT_STATUS_EQUAL(NT_STATUS_NOT_SUPPORTED,
					     status)) {
				return status;
			}
		}
	}

	file_id = SMB_VFS_FS_FILE_ID(conn, &smb_fname->st);

	mdate_ts = smb_fname->st.st_ex_mtime;
	adate_ts = smb_fname->st.st_ex_atime;
	create_date_ts = get_create_timespec(conn, NULL, smb_fname);
	cdate_ts = get_change_timespec(conn, NULL, smb_fname);

	if (lp_dos_filetime_resolution(SNUM(conn))) {
		dos_filetime_timespec(&create_date_ts);
		dos_filetime_timespec(&mdate_ts);
		dos_filetime_timespec(&adate_ts);
		dos_filetime_timespec(&cdate_ts);
	}

	create_date = convert_timespec_to_time_t(create_date_ts);
	mdate = convert_timespec_to_time_t(mdate_ts);
	adate = convert_timespec_to_time_t(adate_ts);


	SMB_ASSERT(align >= 1);

	off = (int)PTR_DIFF(pdata, base_data);
	pad = (off + (align-1)) & ~(align-1);
	pad -= off;

	if (pad && pad > space_remaining) {
		DEBUG(9,("smbd_marshall_dir_entry: out of space "
			"for padding (wanted %u, had %d)\n",
			(unsigned int)pad,
			space_remaining ));
		return STATUS_MORE_ENTRIES;
	}

	off += pad;

	if (pad) {
		memset(pdata, 0, pad);
	}
	space_remaining -= pad;

	DEBUG(10,("smbd_marshall_dir_entry: space_remaining = %d\n",
		space_remaining ));

	pdata += pad;
	p = pdata;
	last_entry_ptr = p;

	pad = 0;
	off = 0;

	switch (info_level) {
	case SMB_FIND_INFO_STANDARD:
		DEBUG(10,("smbd_marshall_dir_entry: SMB_FIND_INFO_STANDARD\n"));
		if(requires_resume_key) {
			SIVAL(p,0,reskey);
			p += 4;
		}
		srv_put_dos_date2(p,0,create_date);
		srv_put_dos_date2(p,4,adate);
		srv_put_dos_date2(p,8,mdate);
		SIVAL(p,12,(uint32_t)file_size);
		SIVAL(p,16,(uint32_t)allocation_size);
		SSVAL(p,20,mode);
		p += 23;
		nameptr = p;
		if (flags2 & FLAGS2_UNICODE_STRINGS) {
			p += ucs2_align(base_data, p, 0);
		}
		status = srvstr_push(base_data, flags2, p,
				  fname, PTR_DIFF(end_data, p),
				  STR_TERMINATE, &len);
		if (!NT_STATUS_IS_OK(status)) {
			return status;
		}
		if (flags2 & FLAGS2_UNICODE_STRINGS) {
			if (len > 2) {
				SCVAL(nameptr, -1, len - 2);
			} else {
				SCVAL(nameptr, -1, 0);
			}
		} else {
			if (len > 1) {
				SCVAL(nameptr, -1, len - 1);
			} else {
				SCVAL(nameptr, -1, 0);
			}
		}
		p += len;
		break;

	case SMB_FIND_EA_SIZE:
		DEBUG(10,("smbd_marshall_dir_entry: SMB_FIND_EA_SIZE\n"));
		if (requires_resume_key) {
			SIVAL(p,0,reskey);
			p += 4;
		}
		srv_put_dos_date2(p,0,create_date);
		srv_put_dos_date2(p,4,adate);
		srv_put_dos_date2(p,8,mdate);
		SIVAL(p,12,(uint32_t)file_size);
		SIVAL(p,16,(uint32_t)allocation_size);
		SSVAL(p,20,mode);
		{
			unsigned int ea_size = estimate_ea_size(smb_fname->fsp);
			SIVAL(p,22,ea_size);
		}
		p += 27;
		nameptr = p - 1;
		status = srvstr_push(base_data, flags2,
				  p, fname, PTR_DIFF(end_data, p),
				  STR_TERMINATE | STR_NOALIGN, &len);
		if (!NT_STATUS_IS_OK(status)) {
			return status;
		}
		if (flags2 & FLAGS2_UNICODE_STRINGS) {
			if (len > 2) {
				len -= 2;
			} else {
				len = 0;
			}
		} else {
			if (len > 1) {
				len -= 1;
			} else {
				len = 0;
			}
		}
		SCVAL(nameptr,0,len);
		p += len;
		SCVAL(p,0,0); p += 1;
		break;

	case SMB_FIND_EA_LIST:
	{
		struct ea_list *file_list = NULL;
		size_t ea_len = 0;

		DEBUG(10,("smbd_marshall_dir_entry: SMB_FIND_EA_LIST\n"));
		if (!name_list) {
			return NT_STATUS_INVALID_PARAMETER;
		}
		if (requires_resume_key) {
			SIVAL(p,0,reskey);
			p += 4;
		}
		srv_put_dos_date2(p,0,create_date);
		srv_put_dos_date2(p,4,adate);
		srv_put_dos_date2(p,8,mdate);
		SIVAL(p,12,(uint32_t)file_size);
		SIVAL(p,16,(uint32_t)allocation_size);
		SSVAL(p,20,mode);
		p += 22;

		status = get_ea_list_from_fsp(ctx,
					       smb_fname->fsp,
					       &ea_len, &file_list);
		if (!NT_STATUS_IS_OK(status)) {
			file_list = NULL;
		}
		name_list = ea_list_union(name_list, file_list, &ea_len);


		if (PTR_DIFF(p + 255 + ea_len,pdata) > space_remaining) {
			DEBUG(9,("smbd_marshall_dir_entry: out of space "
				"(wanted %u, had %d)\n",
				(unsigned int)PTR_DIFF(p + 255 + ea_len,pdata),
				space_remaining ));
			return STATUS_MORE_ENTRIES;
		}


		p += fill_ea_buffer(ctx, p, space_remaining, conn, name_list);
		nameptr = p;
		status = srvstr_push(base_data, flags2,
				  p + 1, fname, PTR_DIFF(end_data, p+1),
				  STR_TERMINATE | STR_NOALIGN, &len);
		if (!NT_STATUS_IS_OK(status)) {
			return status;
		}
		if (flags2 & FLAGS2_UNICODE_STRINGS) {
			if (len > 2) {
				len -= 2;
			} else {
				len = 0;
			}
		} else {
			if (len > 1) {
				len -= 1;
			} else {
				len = 0;
			}
		}
		SCVAL(nameptr,0,len);
		p += len + 1;
		SCVAL(p,0,0); p += 1;
		break;
	}

	case SMB_FIND_FILE_BOTH_DIRECTORY_INFO:
		DEBUG(10,("smbd_marshall_dir_entry: SMB_FIND_FILE_BOTH_DIRECTORY_INFO\n"));
		was_8_3 = mangle_is_8_3(fname, True, conn->params);
		p += 4;
		SIVAL(p,0,reskey); p += 4;
		put_long_date_full_timespec(conn->ts_res,p,&create_date_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&adate_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&mdate_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&cdate_ts); p += 8;
		SOFF_T(p,0,file_size); p += 8;
		SOFF_T(p,0,allocation_size); p += 8;
		SIVAL(p,0,mode); p += 4;
		q = p; p += 4;
		if (mode & FILE_ATTRIBUTE_REPARSE_POINT) {
			SIVAL(p, 0, IO_REPARSE_TAG_DFS);
		} else {
			unsigned int ea_size = estimate_ea_size(smb_fname->fsp);
			SIVAL(p,0,ea_size);
		}
		p += 4;


		if (!was_8_3 && check_mangled_names) {
			char mangled_name[13];
			if (!name_to_8_3(fname,mangled_name,True,
					   conn->params)) {

				memset(mangled_name,'\0',12);
			}
			mangled_name[12] = 0;
			status = srvstr_push(base_data, flags2,
					  p+2, mangled_name, 24,
					  STR_UPPER|STR_UNICODE, &len);
			if (!NT_STATUS_IS_OK(status)) {
				return status;
			}
			if (len < 24) {
				memset(p + 2 + len,'\0',24 - len);
			}
			SSVAL(p, 0, len);
		} else {
			memset(p,'\0',26);
		}
		p += 2 + 24;
		status = srvstr_push(base_data, flags2, p,
				  fname, PTR_DIFF(end_data, p),
				  STR_TERMINATE_ASCII, &len);
		if (!NT_STATUS_IS_OK(status)) {
			return status;
		}
		SIVAL(q,0,len);
		p += len;

		len = PTR_DIFF(p, pdata);
		pad = (len + (align-1)) & ~(align-1);


		SIVAL(pdata,0,pad);


		if (do_pad) {
			memset(p, 0, pad - len);
			p = pdata + pad;
		} else {
			p = pdata + len;
		}
		break;

	case SMB_FIND_FILE_DIRECTORY_INFO:
		DEBUG(10,("smbd_marshall_dir_entry: SMB_FIND_FILE_DIRECTORY_INFO\n"));
		p += 4;
		SIVAL(p,0,reskey); p += 4;
		put_long_date_full_timespec(conn->ts_res,p,&create_date_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&adate_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&mdate_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&cdate_ts); p += 8;
		SOFF_T(p,0,file_size); p += 8;
		SOFF_T(p,0,allocation_size); p += 8;
		SIVAL(p,0,mode); p += 4;
		status = srvstr_push(base_data, flags2,
				  p + 4, fname, PTR_DIFF(end_data, p+4),
				  STR_TERMINATE_ASCII, &len);
		if (!NT_STATUS_IS_OK(status)) {
			return status;
		}
		SIVAL(p,0,len);
		p += 4 + len;

		len = PTR_DIFF(p, pdata);
		pad = (len + (align-1)) & ~(align-1);


		SIVAL(pdata,0,pad);


		if (do_pad) {
			memset(p, 0, pad - len);
			p = pdata + pad;
		} else {
			p = pdata + len;
		}
		break;

	case SMB_FIND_FILE_FULL_DIRECTORY_INFO:
		DEBUG(10,("smbd_marshall_dir_entry: SMB_FIND_FILE_FULL_DIRECTORY_INFO\n"));
		p += 4;
		SIVAL(p,0,reskey); p += 4;
		put_long_date_full_timespec(conn->ts_res,p,&create_date_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&adate_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&mdate_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&cdate_ts); p += 8;
		SOFF_T(p,0,file_size); p += 8;
		SOFF_T(p,0,allocation_size); p += 8;
		SIVAL(p,0,mode); p += 4;
		q = p; p += 4;
		if (mode & FILE_ATTRIBUTE_REPARSE_POINT) {
			SIVAL(p, 0, IO_REPARSE_TAG_DFS);
		} else {
			unsigned int ea_size = estimate_ea_size(smb_fname->fsp);
			SIVAL(p,0,ea_size);
		}
		p +=4;
		status = srvstr_push(base_data, flags2, p,
				  fname, PTR_DIFF(end_data, p),
				  STR_TERMINATE_ASCII, &len);
		if (!NT_STATUS_IS_OK(status)) {
			return status;
		}
		SIVAL(q, 0, len);
		p += len;

		len = PTR_DIFF(p, pdata);
		pad = (len + (align-1)) & ~(align-1);


		SIVAL(pdata,0,pad);


		if (do_pad) {
			memset(p, 0, pad - len);
			p = pdata + pad;
		} else {
			p = pdata + len;
		}
		break;

	case SMB_FIND_FILE_NAMES_INFO:
		DEBUG(10,("smbd_marshall_dir_entry: SMB_FIND_FILE_NAMES_INFO\n"));
		p += 4;
		SIVAL(p,0,reskey); p += 4;
		p += 4;


		status = srvstr_push(base_data, flags2, p,
				  fname, PTR_DIFF(end_data, p),
				  STR_TERMINATE_ASCII, &len);
		if (!NT_STATUS_IS_OK(status)) {
			return status;
		}
		SIVAL(p, -4, len);
		p += len;

		len = PTR_DIFF(p, pdata);
		pad = (len + (align-1)) & ~(align-1);


		SIVAL(pdata,0,pad);


		if (do_pad) {
			memset(p, 0, pad - len);
			p = pdata + pad;
		} else {
			p = pdata + len;
		}
		break;

	case SMB_FIND_ID_FULL_DIRECTORY_INFO:
		DEBUG(10,("smbd_marshall_dir_entry: SMB_FIND_ID_FULL_DIRECTORY_INFO\n"));
		p += 4;
		SIVAL(p,0,reskey); p += 4;
		put_long_date_full_timespec(conn->ts_res,p,&create_date_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&adate_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&mdate_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&cdate_ts); p += 8;
		SOFF_T(p,0,file_size); p += 8;
		SOFF_T(p,0,allocation_size); p += 8;
		SIVAL(p,0,mode); p += 4;
		q = p; p += 4;
		if (mode & FILE_ATTRIBUTE_REPARSE_POINT) {
			SIVAL(p, 0, IO_REPARSE_TAG_DFS);
		} else {
			unsigned int ea_size = estimate_ea_size(smb_fname->fsp);
			SIVAL(p,0,ea_size);
		}
		p += 4;
		SIVAL(p,0,0); p += 4;
		SBVAL(p,0,file_id); p += 8;
		status = srvstr_push(base_data, flags2, p,
				  fname, PTR_DIFF(end_data, p),
				  STR_TERMINATE_ASCII, &len);
		if (!NT_STATUS_IS_OK(status)) {
			return status;
		}
		SIVAL(q, 0, len);
		p += len;

		len = PTR_DIFF(p, pdata);
		pad = (len + (align-1)) & ~(align-1);


		SIVAL(pdata,0,pad);


		if (do_pad) {
			memset(p, 0, pad - len);
			p = pdata + pad;
		} else {
			p = pdata + len;
		}
		break;

	case SMB_FIND_ID_BOTH_DIRECTORY_INFO:
		DEBUG(10,("smbd_marshall_dir_entry: SMB_FIND_ID_BOTH_DIRECTORY_INFO\n"));
		was_8_3 = mangle_is_8_3(fname, True, conn->params);
		p += 4;
		SIVAL(p,0,reskey); p += 4;
		put_long_date_full_timespec(conn->ts_res,p,&create_date_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&adate_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&mdate_ts); p += 8;
		put_long_date_full_timespec(conn->ts_res,p,&cdate_ts); p += 8;
		SOFF_T(p,0,file_size); p += 8;
		SOFF_T(p,0,allocation_size); p += 8;
		SIVAL(p,0,mode); p += 4;
		q = p; p += 4;
		if (mode & FILE_ATTRIBUTE_REPARSE_POINT) {
			SIVAL(p, 0, IO_REPARSE_TAG_DFS);
		} else if (readdir_attr_data &&
			   readdir_attr_data->type == RDATTR_AAPL) {


			SIVAL(p, 0, readdir_attr_data->attr_data.aapl.max_access);
		} else {
			unsigned int ea_size = estimate_ea_size(smb_fname->fsp);
			SIVAL(p,0,ea_size);
		}
		p += 4;

		if (readdir_attr_data &&
		    readdir_attr_data->type == RDATTR_AAPL) {


			SSVAL(p, 0, 24);


			SBVAL(p, 2, readdir_attr_data->attr_data.aapl.rfork_size);


			memcpy(p + 10, &readdir_attr_data->attr_data.aapl.finder_info, 16);
		} else if (!was_8_3 && check_mangled_names) {
			char mangled_name[13];
			if (!name_to_8_3(fname,mangled_name,True,
					conn->params)) {

				memset(mangled_name,'\0',12);
			}
			mangled_name[12] = 0;
			status = srvstr_push(base_data, flags2,
					  p+2, mangled_name, 24,
					  STR_UPPER|STR_UNICODE, &len);
			if (!NT_STATUS_IS_OK(status)) {
				return status;
			}
			SSVAL(p, 0, len);
			if (len < 24) {
				memset(p + 2 + len,'\0',24 - len);
			}
			SSVAL(p, 0, len);
		} else {


			memset(p,'\0',26);
		}
		p += 26;


		if (readdir_attr_data &&
		    readdir_attr_data->type == RDATTR_AAPL) {


			uint16_t aapl_mode = (uint16_t)readdir_attr_data->attr_data.aapl.unix_mode;
			SSVAL(p, 0, aapl_mode);
		} else {
			SSVAL(p, 0, 0);
		}
		p += 2;

		SBVAL(p,0,file_id); p += 8;
		status = srvstr_push(base_data, flags2, p,
				  fname, PTR_DIFF(end_data, p),
				  STR_TERMINATE_ASCII, &len);
		if (!NT_STATUS_IS_OK(status)) {
			return status;
		}
		SIVAL(q,0,len);
		p += len;

		len = PTR_DIFF(p, pdata);
		pad = (len + (align-1)) & ~(align-1);


		SIVAL(pdata,0,pad);


		if (do_pad) {
			memset(p, 0, pad - len);
			p = pdata + pad;
		} else {
			p = pdata + len;
		}
		break;


	case SMB_FIND_FILE_UNIX:
	case SMB_FIND_FILE_UNIX_INFO2:
		p+= 4;
		SIVAL(p,0,reskey); p+= 4;


		if (info_level == SMB_FIND_FILE_UNIX) {
			DEBUG(10,("smbd_marshall_dir_entry: SMB_FIND_FILE_UNIX\n"));
			p = store_file_unix_basic(conn, p,
						NULL, &smb_fname->st);
			status = srvstr_push(base_data, flags2, p,
					  fname, PTR_DIFF(end_data, p),
					  STR_TERMINATE, &len);
			if (!NT_STATUS_IS_OK(status)) {
				return status;
			}
		} else {
			DEBUG(10,("smbd_marshall_dir_entry: SMB_FIND_FILE_UNIX_INFO2\n"));
			p = store_file_unix_basic_info2(conn, p,
						NULL, &smb_fname->st);
			nameptr = p;
			p += 4;
			status = srvstr_push(base_data, flags2, p, fname,
					  PTR_DIFF(end_data, p), 0, &len);
			if (!NT_STATUS_IS_OK(status)) {
				return status;
			}
			SIVAL(nameptr, 0, len);
		}

		p += len;

		len = PTR_DIFF(p, pdata);
		pad = (len + (align-1)) & ~(align-1);


		SIVAL(pdata,0,pad);


		if (do_pad) {
			memset(p, 0, pad - len);
			p = pdata + pad;
		} else {
			p = pdata + len;
		}


		break;

	default:
		return NT_STATUS_INVALID_LEVEL;
	}

	if (PTR_DIFF(p,pdata) > space_remaining) {
		DEBUG(9,("smbd_marshall_dir_entry: out of space "
			"(wanted %u, had %d)\n",
			(unsigned int)PTR_DIFF(p,pdata),
			space_remaining ));
		return STATUS_MORE_ENTRIES;
	}


	*last_entry_off = PTR_DIFF(last_entry_ptr,base_data);

	*ppdata = p;

	return NT_STATUS_OK;
}
