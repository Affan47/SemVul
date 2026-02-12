static NTSTATUS smb_info_set_ea(connection_struct *conn,
				const char *pdata,
				int total_data,
				files_struct *fsp,
				struct smb_filename *smb_fname)
{
	struct ea_list *ea_list = NULL;
	TALLOC_CTX *ctx = NULL;
	NTSTATUS status = NT_STATUS_OK;

	if (total_data < 10) {


		if ((total_data == 4) && (IVAL(pdata,0) == 4)) {

			return NT_STATUS_OK;
		}

		return NT_STATUS_INVALID_PARAMETER;
	}

	if (IVAL(pdata,0) > total_data) {
		DEBUG(10,("smb_info_set_ea: bad total data size (%u) > %u\n",
			IVAL(pdata,0), (unsigned int)total_data));
		return NT_STATUS_INVALID_PARAMETER;
	}

	ctx = talloc_tos();
	ea_list = read_ea_list(ctx, pdata + 4, total_data - 4);
	if (!ea_list) {
		return NT_STATUS_INVALID_PARAMETER;
	}

	if (fsp == NULL) {


		SMB_ASSERT(smb_fname->flags & SMB_FILENAME_POSIX_PATH);
		return NT_STATUS_ACCESS_DENIED;
	}

	status = set_ea(conn, fsp, ea_list);

	return status;
}
