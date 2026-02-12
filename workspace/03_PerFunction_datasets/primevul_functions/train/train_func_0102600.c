static bool create_canon_ace_lists(files_struct *fsp, SMB_STRUCT_STAT *pst,
							DOM_SID *pfile_owner_sid,
							DOM_SID *pfile_grp_sid,
							canon_ace **ppfile_ace, canon_ace **ppdir_ace,
							SEC_ACL *dacl)
{
	bool all_aces_are_inherit_only = (fsp->is_directory ? True : False);
	canon_ace *file_ace = NULL;
	canon_ace *dir_ace = NULL;
	canon_ace *current_ace = NULL;
	bool got_dir_allow = False;
	bool got_file_allow = False;
	int i, j;

	*ppfile_ace = NULL;
	*ppdir_ace = NULL;


	for(i = 0; i < dacl->num_aces; i++) {
		SEC_ACE *psa = &dacl->aces[i];

		if((psa->type != SEC_ACE_TYPE_ACCESS_ALLOWED) && (psa->type != SEC_ACE_TYPE_ACCESS_DENIED)) {
			DEBUG(3,("create_canon_ace_lists: unable to set anything but an ALLOW or DENY ACE.\n"));
			return False;
		}

		if (nt4_compatible_acls()) {


			se_map_generic(&psa->access_mask, &file_generic_mapping);

			psa->access_mask &= (UNIX_ACCESS_NONE|FILE_ALL_ACCESS);

			if(psa->access_mask != UNIX_ACCESS_NONE)
				psa->access_mask &= ~UNIX_ACCESS_NONE;
		}
	}


	for(i = 0; i < dacl->num_aces; i++) {
		SEC_ACE *psa1 = &dacl->aces[i];

		for (j = i + 1; j < dacl->num_aces; j++) {
			SEC_ACE *psa2 = &dacl->aces[j];

			if (psa1->access_mask != psa2->access_mask)
				continue;

			if (!sid_equal(&psa1->trustee, &psa2->trustee))
				continue;


			if (psa1->flags & SEC_ACE_FLAG_INHERIT_ONLY) {

				psa1->flags |= (psa2->flags & (SEC_ACE_FLAG_CONTAINER_INHERIT|SEC_ACE_FLAG_OBJECT_INHERIT));
				psa2->flags &= ~(SEC_ACE_FLAG_CONTAINER_INHERIT|SEC_ACE_FLAG_OBJECT_INHERIT);

			} else if (psa2->flags & SEC_ACE_FLAG_INHERIT_ONLY) {

				psa2->flags |= (psa1->flags & (SEC_ACE_FLAG_CONTAINER_INHERIT|SEC_ACE_FLAG_OBJECT_INHERIT));
				psa1->flags &= ~(SEC_ACE_FLAG_CONTAINER_INHERIT|SEC_ACE_FLAG_OBJECT_INHERIT);

			}
		}
	}

	for(i = 0; i < dacl->num_aces; i++) {
		SEC_ACE *psa = &dacl->aces[i];


		if ((current_ace = SMB_MALLOC_P(canon_ace)) == NULL) {
			free_canon_ace_list(file_ace);
			free_canon_ace_list(dir_ace);
			DEBUG(0,("create_canon_ace_lists: malloc fail.\n"));
			return False;
		}

		ZERO_STRUCTP(current_ace);

		sid_copy(&current_ace->trustee, &psa->trustee);


		if( sid_equal(&current_ace->trustee, &global_sid_World)) {
			current_ace->owner_type = WORLD_ACE;
			current_ace->unix_ug.world = -1;
			current_ace->type = SMB_ACL_OTHER;
		} else if (sid_equal(&current_ace->trustee, &global_sid_Creator_Owner)) {
			current_ace->owner_type = UID_ACE;
			current_ace->unix_ug.uid = pst->st_uid;
			current_ace->type = SMB_ACL_USER_OBJ;


			if (nt4_compatible_acls())
				psa->flags |= SEC_ACE_FLAG_INHERIT_ONLY;
		} else if (sid_equal(&current_ace->trustee, &global_sid_Creator_Group)) {
			current_ace->owner_type = GID_ACE;
			current_ace->unix_ug.gid = pst->st_gid;
			current_ace->type = SMB_ACL_GROUP_OBJ;


			if (nt4_compatible_acls())
				psa->flags |= SEC_ACE_FLAG_INHERIT_ONLY;

		} else if (sid_to_uid( &current_ace->trustee, &current_ace->unix_ug.uid)) {
			current_ace->owner_type = UID_ACE;


			if (current_ace->unix_ug.uid == pst->st_uid) {
				current_ace->type = SMB_ACL_USER_OBJ;
			} else {
				current_ace->type = SMB_ACL_USER;
			}
		} else if (sid_to_gid( &current_ace->trustee, &current_ace->unix_ug.gid)) {
			current_ace->owner_type = GID_ACE;


			if (current_ace->unix_ug.gid == pst->st_gid) {
				current_ace->type = SMB_ACL_GROUP_OBJ;
			} else {
				current_ace->type = SMB_ACL_GROUP;
			}
		} else {


			if (non_mappable_sid(&psa->trustee)) {
				DEBUG(10, ("create_canon_ace_lists: ignoring "
					   "non-mappable SID %s\n",
					   sid_string_dbg(&psa->trustee)));
				SAFE_FREE(current_ace);
				continue;
			}

			free_canon_ace_list(file_ace);
			free_canon_ace_list(dir_ace);
			DEBUG(0, ("create_canon_ace_lists: unable to map SID "
				  "%s to uid or gid.\n",
				  sid_string_dbg(&current_ace->trustee)));
			SAFE_FREE(current_ace);
			return False;
		}


		current_ace->perms |= map_nt_perms( &psa->access_mask, S_IRUSR);
		current_ace->attr = (psa->type == SEC_ACE_TYPE_ACCESS_ALLOWED) ? ALLOW_ACE : DENY_ACE;
		current_ace->inherited = ((psa->flags & SEC_ACE_FLAG_INHERITED_ACE) ? True : False);


		if (fsp->is_directory) {


			if ((psa->flags & (SEC_ACE_FLAG_OBJECT_INHERIT|SEC_ACE_FLAG_CONTAINER_INHERIT)) ==
				(SEC_ACE_FLAG_OBJECT_INHERIT|SEC_ACE_FLAG_CONTAINER_INHERIT)) {

				DLIST_ADD_END(dir_ace, current_ace, canon_ace *);


				if (current_ace->attr == ALLOW_ACE)
					got_dir_allow = True;

				if ((current_ace->attr == DENY_ACE) && got_dir_allow) {
					DEBUG(0,("create_canon_ace_lists: malformed ACL in inheritable ACL ! \
Deny entry after Allow entry. Failing to set on file %s.\n", fsp->fsp_name ));
					free_canon_ace_list(file_ace);
					free_canon_ace_list(dir_ace);
					return False;
				}

				if( DEBUGLVL( 10 )) {
					dbgtext("create_canon_ace_lists: adding dir ACL:\n");
					print_canon_ace( current_ace, 0);
				}


				if (!(psa->flags & SEC_ACE_FLAG_INHERIT_ONLY)) {
					canon_ace *dup_ace = dup_canon_ace(current_ace);

					if (!dup_ace) {
						DEBUG(0,("create_canon_ace_lists: malloc fail !\n"));
						free_canon_ace_list(file_ace);
						free_canon_ace_list(dir_ace);
						return False;
					}


					current_ace = dup_ace;
				} else {


					current_ace = NULL;
				}
			}
		}


		if (current_ace && !(psa->flags & SEC_ACE_FLAG_INHERIT_ONLY)) {
			DLIST_ADD_END(file_ace, current_ace, canon_ace *);


			if (current_ace->attr == ALLOW_ACE)
				got_file_allow = True;

			if ((current_ace->attr == DENY_ACE) && got_file_allow) {
				DEBUG(0,("create_canon_ace_lists: malformed ACL in file ACL ! \
Deny entry after Allow entry. Failing to set on file %s.\n", fsp->fsp_name ));
				free_canon_ace_list(file_ace);
				free_canon_ace_list(dir_ace);
				return False;
			}

			if( DEBUGLVL( 10 )) {
				dbgtext("create_canon_ace_lists: adding file ACL:\n");
				print_canon_ace( current_ace, 0);
			}
			all_aces_are_inherit_only = False;


			current_ace = NULL;
		}


		SAFE_FREE(current_ace);
	}

	if (fsp->is_directory && all_aces_are_inherit_only) {


		DEBUG(10,("create_canon_ace_lists: Win2k inherit acl traverse. Ignoring DACL.\n"));
		free_canon_ace_list(file_ace);
		free_canon_ace_list(dir_ace);
		file_ace = NULL;
		dir_ace = NULL;
	} else {


		if (file_ace) {
			check_owning_objs(file_ace, pfile_owner_sid, pfile_grp_sid);
		}
		if (dir_ace) {
			check_owning_objs(dir_ace, pfile_owner_sid, pfile_grp_sid);
		}
	}

	*ppfile_ace = file_ace;
	*ppdir_ace = dir_ace;

	return True;
}
