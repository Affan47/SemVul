static NTSTATUS append_parent_acl(files_struct *fsp,
				SMB_STRUCT_STAT *psbuf,
				SEC_DESC *psd,
				SEC_DESC **pp_new_sd)
{
	SEC_DESC *parent_sd = NULL;
	files_struct *parent_fsp = NULL;
	TALLOC_CTX *mem_ctx = talloc_parent(psd);
	char *parent_name = NULL;
	SEC_ACE *new_ace = NULL;
	unsigned int num_aces = psd->dacl->num_aces;
	SMB_STRUCT_STAT sbuf;
	NTSTATUS status;
	int info;
	unsigned int i, j;
	bool is_dacl_protected = (psd->type & SE_DESC_DACL_PROTECTED);

	ZERO_STRUCT(sbuf);

	if (mem_ctx == NULL) {
		return NT_STATUS_NO_MEMORY;
	}

	if (!parent_dirname_talloc(mem_ctx,
				fsp->fsp_name,
				&parent_name,
				NULL)) {
		return NT_STATUS_NO_MEMORY;
	}

	status = open_directory(fsp->conn,
				NULL,
				parent_name,
				&sbuf,
				FILE_READ_ATTRIBUTES,
				FILE_SHARE_NONE,
				FILE_OPEN,
				0,
				INTERNAL_OPEN_ONLY,
				&info,
				&parent_fsp);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}

	status = SMB_VFS_GET_NT_ACL(parent_fsp->conn, parent_fsp->fsp_name,
				    DACL_SECURITY_INFORMATION, &parent_sd );

	close_file(parent_fsp, NORMAL_CLOSE);

	if (!NT_STATUS_IS_OK(status)) {
		return status;
	}


	num_aces += parent_sd->dacl->num_aces;

	if((new_ace = TALLOC_ZERO_ARRAY(mem_ctx, SEC_ACE,
					num_aces)) == NULL) {
		return NT_STATUS_NO_MEMORY;
	}


	for (i = 0; i < psd->dacl->num_aces; i++) {
		sec_ace_copy(&new_ace[i], &psd->dacl->aces[i]);
	}


	for (j = 0; j < parent_sd->dacl->num_aces; j++) {
		SEC_ACE *se = &parent_sd->dacl->aces[j];

		if (fsp->is_directory) {
			if (!(se->flags & SEC_ACE_FLAG_CONTAINER_INHERIT)) {

				DEBUG(10,("append_parent_acl: directory %s "
					"ignoring non container "
					"inherit flags %u on ACE with sid %s "
					"from parent %s\n",
					fsp->fsp_name,
					(unsigned int)se->flags,
					sid_string_dbg(&se->trustee),
					parent_name));
				continue;
			}
		} else {
			if (!(se->flags & SEC_ACE_FLAG_OBJECT_INHERIT)) {

				DEBUG(10,("append_parent_acl: file %s "
					"ignoring non object "
					"inherit flags %u on ACE with sid %s "
					"from parent %s\n",
					fsp->fsp_name,
					(unsigned int)se->flags,
					sid_string_dbg(&se->trustee),
					parent_name));
				continue;
			}
		}

		if (is_dacl_protected) {


			unsigned int k;
			for (k = 0; k < psd->dacl->num_aces; k++) {
				if (sid_equal(&psd->dacl->aces[k].trustee,
						&se->trustee)) {
					break;
				}
			}
			if (k < psd->dacl->num_aces) {

				DEBUG(10,("append_parent_acl: path %s "
					"ignoring ACE with protected sid %s "
					"from parent %s\n",
					fsp->fsp_name,
					sid_string_dbg(&se->trustee),
					parent_name));
				continue;
			}
		}

		sec_ace_copy(&new_ace[i], se);
		if (se->flags & SEC_ACE_FLAG_NO_PROPAGATE_INHERIT) {
			new_ace[i].flags &= ~(SEC_ACE_FLAG_VALID_INHERIT);
		}
		new_ace[i].flags |= SEC_ACE_FLAG_INHERITED_ACE;

		if (fsp->is_directory) {


			new_ace[i].flags &= ~(SEC_ACE_FLAG_INHERIT_ONLY);
			if (se->flags & SEC_ACE_FLAG_NO_PROPAGATE_INHERIT) {

				new_ace[i].flags &=
					~(SEC_ACE_FLAG_CONTAINER_INHERIT|
					SEC_ACE_FLAG_OBJECT_INHERIT);
			}
		} else {


			new_ace[i].flags &= ~(SEC_ACE_FLAG_CONTAINER_INHERIT|
						SEC_ACE_FLAG_INHERIT_ONLY|
						SEC_ACE_FLAG_NO_PROPAGATE_INHERIT);
		}
		i++;

		DEBUG(10,("append_parent_acl: path %s "
			"inheriting ACE with sid %s "
			"from parent %s\n",
			fsp->fsp_name,
			sid_string_dbg(&se->trustee),
			parent_name));
	}


	psd->dacl->aces = new_ace;
	psd->dacl->num_aces = i;
	psd->type &= ~(SE_DESC_DACL_AUTO_INHERITED|
                         SE_DESC_DACL_AUTO_INHERIT_REQ);

	*pp_new_sd = psd;
	return status;
}
