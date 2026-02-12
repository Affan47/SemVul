static NTSTATUS posix_get_nt_acl_common(struct connection_struct *conn,
				      const char *name,
				      const SMB_STRUCT_STAT *sbuf,
				      struct pai_val *pal,
				      SMB_ACL_T posix_acl,
				      SMB_ACL_T def_acl,
				      uint32_t security_info,
				      SEC_DESC **ppdesc)
{
	DOM_SID owner_sid;
	DOM_SID group_sid;
	size_t sd_size = 0;
	SEC_ACL *psa = NULL;
	size_t num_acls = 0;
	size_t num_def_acls = 0;
	size_t num_aces = 0;
	canon_ace *file_ace = NULL;
	canon_ace *dir_ace = NULL;
	SEC_ACE *nt_ace_list = NULL;
	size_t num_profile_acls = 0;
	DOM_SID orig_owner_sid;
	SEC_DESC *psd = NULL;
	int i;


	create_file_sids(sbuf, &owner_sid, &group_sid);

	if (lp_profile_acls(SNUM(conn))) {

		sid_copy(&orig_owner_sid, &owner_sid);
		sid_copy(&owner_sid, &global_sid_Builtin_Administrators);
		sid_copy(&group_sid, &global_sid_Builtin_Users);
		num_profile_acls = 3;
	}

	if ((security_info & DACL_SECURITY_INFORMATION) && !(security_info & PROTECTED_DACL_SECURITY_INFORMATION)) {


		file_ace = canonicalise_acl(conn, name, posix_acl, sbuf,
					    &owner_sid, &group_sid, pal,
					    SMB_ACL_TYPE_ACCESS);


		if (count_canon_ace_list(file_ace) == 0) {
			DEBUG(0,("get_nt_acl : No ACLs on file (%s) !\n", name));
			goto done;
		}

		if (S_ISDIR(sbuf->st_mode) && def_acl) {
			dir_ace = canonicalise_acl(conn, name, def_acl,
						   sbuf,
						   &global_sid_Creator_Owner,
						   &global_sid_Creator_Group,
						   pal, SMB_ACL_TYPE_DEFAULT);
		}


		{
			canon_ace *ace;
			enum security_ace_type nt_acl_type;

			if (nt4_compatible_acls() && dir_ace) {


				ace = canon_ace_entry_for(dir_ace, SMB_ACL_OTHER, NULL);
				if (ace && !ace->perms) {
					DLIST_REMOVE(dir_ace, ace);
					SAFE_FREE(ace);

					ace = canon_ace_entry_for(file_ace, SMB_ACL_OTHER, NULL);
					if (ace && !ace->perms) {
						DLIST_REMOVE(file_ace, ace);
						SAFE_FREE(ace);
					}
				}


#if 0
				ace = canon_ace_entry_for(dir_ace, SMB_ACL_GROUP_OBJ, NULL);
				if (ace && !ace->perms) {
					DLIST_REMOVE(dir_ace, ace);
					SAFE_FREE(ace);
				}
#endif

				ace = canon_ace_entry_for(file_ace, SMB_ACL_GROUP_OBJ, NULL);
				if (ace && !ace->perms) {
					DLIST_REMOVE(file_ace, ace);
					SAFE_FREE(ace);
				}
			}

			num_acls = count_canon_ace_list(file_ace);
			num_def_acls = count_canon_ace_list(dir_ace);


			if ((nt_ace_list = SMB_MALLOC_ARRAY(SEC_ACE,num_acls + num_profile_acls + num_def_acls)) == NULL) {
				DEBUG(0,("get_nt_acl: Unable to malloc space for nt_ace_list.\n"));
				goto done;
			}

			memset(nt_ace_list, '\0', (num_acls + num_def_acls) * sizeof(SEC_ACE) );


			for (ace = file_ace; ace != NULL; ace = ace->next) {
				SEC_ACCESS acc;

				acc = map_canon_ace_perms(SNUM(conn),
						&nt_acl_type,
						ace->perms,
						S_ISDIR(sbuf->st_mode));
				init_sec_ace(&nt_ace_list[num_aces++],
					&ace->trustee,
					nt_acl_type,
					acc,
					ace->inherited ?
						SEC_ACE_FLAG_INHERITED_ACE : 0);
			}


			if (lp_profile_acls(SNUM(conn))) {
 				add_or_replace_ace(nt_ace_list, &num_aces,
 						   &global_sid_Builtin_Users,
 						   SEC_ACE_TYPE_ACCESS_ALLOWED,
 						   FILE_GENERIC_ALL, 0);
			}

			for (ace = dir_ace; ace != NULL; ace = ace->next) {
				SEC_ACCESS acc;

				acc = map_canon_ace_perms(SNUM(conn),
						&nt_acl_type,
						ace->perms,
						S_ISDIR(sbuf->st_mode));
				init_sec_ace(&nt_ace_list[num_aces++],
					&ace->trustee,
					nt_acl_type,
					acc,
					SEC_ACE_FLAG_OBJECT_INHERIT|
					SEC_ACE_FLAG_CONTAINER_INHERIT|
					SEC_ACE_FLAG_INHERIT_ONLY|
					(ace->inherited ?
					   SEC_ACE_FLAG_INHERITED_ACE : 0));
			}


			if (lp_profile_acls(SNUM(conn))) {
 				add_or_replace_ace(nt_ace_list, &num_aces,
 						&global_sid_Builtin_Users,
 						SEC_ACE_TYPE_ACCESS_ALLOWED,
 						FILE_GENERIC_ALL,
 						SEC_ACE_FLAG_OBJECT_INHERIT |
 						SEC_ACE_FLAG_CONTAINER_INHERIT |
 						SEC_ACE_FLAG_INHERIT_ONLY);
			}


			num_aces = merge_default_aces(nt_ace_list, num_aces);

			if (lp_profile_acls(SNUM(conn))) {
				for (i = 0; i < num_aces; i++) {
					if (sid_equal(&nt_ace_list[i].trustee, &owner_sid)) {
						add_or_replace_ace(nt_ace_list, &num_aces,
	    							   &orig_owner_sid,
			    					   nt_ace_list[i].type,
					    			   nt_ace_list[i].access_mask,
								   nt_ace_list[i].flags);
						break;
					}
				}
			}
		}

		if (num_aces) {
			if((psa = make_sec_acl( talloc_tos(), NT4_ACL_REVISION, num_aces, nt_ace_list)) == NULL) {
				DEBUG(0,("get_nt_acl: Unable to malloc space for acl.\n"));
				goto done;
			}
		}
	}

	psd = make_standard_sec_desc( talloc_tos(),
			(security_info & OWNER_SECURITY_INFORMATION) ? &owner_sid : NULL,
			(security_info & GROUP_SECURITY_INFORMATION) ? &group_sid : NULL,
			psa,
			&sd_size);

	if(!psd) {
		DEBUG(0,("get_nt_acl: Unable to malloc space for security descriptor.\n"));
		sd_size = 0;
		goto done;
	}


	if (get_protected_flag(pal) || !lp_map_acl_inherit(SNUM(conn))) {
		psd->type |= SE_DESC_DACL_PROTECTED;
	}

	if (psd->dacl) {
		dacl_sort_into_canonical_order(psd->dacl->aces, (unsigned int)psd->dacl->num_aces);
	}

	*ppdesc = psd;

 done:

	if (posix_acl) {
		SMB_VFS_SYS_ACL_FREE_ACL(conn, posix_acl);
	}
	if (def_acl) {
		SMB_VFS_SYS_ACL_FREE_ACL(conn, def_acl);
	}
	free_canon_ace_list(file_ace);
	free_canon_ace_list(dir_ace);
	free_inherited_info(pal);
	SAFE_FREE(nt_ace_list);

	return NT_STATUS_OK;
}
