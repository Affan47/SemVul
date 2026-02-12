static NTSTATUS get_ea_list_from_fsp(TALLOC_CTX *mem_ctx,
				files_struct *fsp,
				size_t *pea_total_len,
				struct ea_list **ea_list)
{

	size_t i, num_names;
	char **names;
	struct ea_list *ea_list_head = NULL;
	bool posix_pathnames = false;
	NTSTATUS status;

	*pea_total_len = 0;
	*ea_list = NULL;


	if (fsp == NULL) {
		return NT_STATUS_OK;
	}

	if (!lp_ea_support(SNUM(fsp->conn))) {
		return NT_STATUS_OK;
	}

	if (is_ntfs_stream_smb_fname(fsp->fsp_name)) {
		return NT_STATUS_INVALID_PARAMETER;
	}

	posix_pathnames = (fsp->fsp_name->flags & SMB_FILENAME_POSIX_PATH);

	status = get_ea_names_from_fsp(talloc_tos(),
				fsp,
				&names,
				&num_names);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	if (num_names == 0) {
		return NT_STATUS_OK;
	}

	for (i=0; i<num_names; i++) {
		struct ea_list *listp;
		fstring dos_ea_name;

		if (strnequal(names[i], "system.", 7)
		    || samba_private_attr_name(names[i]))
			continue;


		if (!posix_pathnames &&
				is_invalid_windows_ea_name(names[i])) {
			continue;
		}

		listp = talloc(mem_ctx, struct ea_list);
		if (listp == NULL) {
			return NT_STATUS_NO_MEMORY;
		}

		status = get_ea_value_fsp(listp,
					  fsp,
					  names[i],
					  &listp->ea);

		if (!NT_STATUS_IS_OK(status)) {
			TALLOC_FREE(listp);
			return status;
		}

		if (listp->ea.value.length == 0) {


			TALLOC_FREE(listp);
			continue;
		} else if (listp->ea.value.length > 65536) {


			DBG_ERR("EA [%s] on file [%s] exceeds "
				"maximum permitted EA size of 64KiB: %zu\n.",
				listp->ea.name, fsp_str_dbg(fsp),
				listp->ea.value.length);
			TALLOC_FREE(listp);
			continue;
		}

		push_ascii_fstring(dos_ea_name, listp->ea.name);

		*pea_total_len +=
			4 + strlen(dos_ea_name) + 1 + listp->ea.value.length;

		DEBUG(10,("get_ea_list_from_file: total_len = %u, %s, val len "
			  "= %u\n", (unsigned int)*pea_total_len, dos_ea_name,
			  (unsigned int)listp->ea.value.length));

		DLIST_ADD_END(ea_list_head, listp);

	}


	if (*pea_total_len) {
		*pea_total_len += 4;
	}

	DEBUG(10, ("get_ea_list_from_file: total_len = %u\n",
		   (unsigned int)*pea_total_len));

	*ea_list = ea_list_head;
	return NT_STATUS_OK;
}
