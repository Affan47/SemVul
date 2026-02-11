args_to_job_recover_nlist (void)
{
	int		not_found = 0;
	int		i, prefix_len, len;
	char *		dest;

	if (C_chdir) {
		prefix_len = strlen (C_chdir) + 2;
	} else {
		prefix_len = 0;
	}

	for (i = 0; (i < n_file_arg) && (i < NDM_MAX_NLIST); i++) {
	    if (file_arg_new[i]) {
		len = strlen (file_arg_new[i]) + prefix_len + 1;

		dest = NDMOS_API_MALLOC (len);
		*dest = 0;
		if (C_chdir) {
			strcpy (dest, C_chdir);
		}
		if (file_arg_new[i][0] != '/') {
			strcat (dest, "/");
		}
		strcat (dest, file_arg_new[i]);

		normalize_name (file_arg_new[i]);
		normalize_name (file_arg[i]);
		normalize_name (dest);

		nlist[i].original_path = file_arg[i];
		nlist[i].destination_path = dest;
	    } else {
		len = strlen (file_arg[i]) + prefix_len + 1;

		dest = NDMOS_API_MALLOC (len);
		*dest = 0;
		if (C_chdir) {
			strcpy (dest, C_chdir);
		}
		if (file_arg[i][0] != '/') {
			strcat (dest, "/");
		}

		strcat (dest, file_arg[i]);

		normalize_name (file_arg[i]);
		normalize_name (dest);

		nlist[i].original_path = file_arg[i];
		nlist[i].destination_path = dest;
	    }
	}

	return not_found;
}
