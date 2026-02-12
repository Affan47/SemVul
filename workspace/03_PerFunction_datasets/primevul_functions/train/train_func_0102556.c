static bool unpack_canon_ace(files_struct *fsp,
							SMB_STRUCT_STAT *pst,
							DOM_SID *pfile_owner_sid,
							DOM_SID *pfile_grp_sid,
							canon_ace **ppfile_ace, canon_ace **ppdir_ace,
							uint32 security_info_sent, SEC_DESC *psd)
{
	canon_ace *file_ace = NULL;
	canon_ace *dir_ace = NULL;

	*ppfile_ace = NULL;
	*ppdir_ace = NULL;

	if(security_info_sent == 0) {
		DEBUG(0,("unpack_canon_ace: no security info sent !\n"));
		return False;
	}


	if(!(security_info_sent & DACL_SECURITY_INFORMATION) || !psd->dacl)
		return True;


	if (!create_canon_ace_lists( fsp, pst, pfile_owner_sid, pfile_grp_sid,
								&file_ace, &dir_ace, psd->dacl))
		return False;

	if ((file_ace == NULL) && (dir_ace == NULL)) {

		return True;
	}


	print_canon_ace_list( "file ace - before merge", file_ace);
	merge_aces( &file_ace );

	print_canon_ace_list( "dir ace - before merge", dir_ace);
	merge_aces( &dir_ace );


	print_canon_ace_list( "file ace - before deny", file_ace);
	process_deny_list( &file_ace);

	print_canon_ace_list( "dir ace - before deny", dir_ace);
	process_deny_list( &dir_ace);


	print_canon_ace_list( "file ace - before valid", file_ace);


	pst->st_mode = create_default_mode(fsp, False);

	if (!ensure_canon_entry_valid(&file_ace, fsp->conn->params, fsp->is_directory, pfile_owner_sid, pfile_grp_sid, pst, True)) {
		free_canon_ace_list(file_ace);
		free_canon_ace_list(dir_ace);
		return False;
	}

	print_canon_ace_list( "dir ace - before valid", dir_ace);


	pst->st_mode = create_default_mode(fsp, True);

	if (dir_ace && !ensure_canon_entry_valid(&dir_ace, fsp->conn->params, fsp->is_directory, pfile_owner_sid, pfile_grp_sid, pst, True)) {
		free_canon_ace_list(file_ace);
		free_canon_ace_list(dir_ace);
		return False;
	}

	print_canon_ace_list( "file ace - return", file_ace);
	print_canon_ace_list( "dir ace - return", dir_ace);

	*ppfile_ace = file_ace;
	*ppdir_ace = dir_ace;
	return True;

}
