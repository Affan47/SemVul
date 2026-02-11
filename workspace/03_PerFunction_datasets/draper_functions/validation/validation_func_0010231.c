share_special_load(const struct special_file *sp)
{
	FILE *f;
	int idx = 0;
	char *tmp;
	shared_file_t *sf = NULL;
	file_path_t fp[4];
	unsigned length = 0;

	tmp = get_folder_path(PRIVLIB_PATH, NULL);
	if (tmp != NULL)
		file_path_set(&fp[length++], tmp, sp->file);

	file_path_set(&fp[length++], settings_config_dir(), sp->file);
	file_path_set(&fp[length++], PRIVLIB_EXP, sp->file);
#ifndef OFFICIAL_BUILD
	file_path_set(&fp[length++], PACKAGE_EXTRA_SOURCE_DIR, sp->file);
#endif

	g_assert(length <= G_N_ELEMENTS(fp));

	f = file_config_open_read_norename_chosen(sp->what, fp, length, &idx);

	if (NULL == f)
		goto done;


	sf = shared_file_alloc();
	sf->flags |= SHARE_F_SPECIAL;
	sf->file_index = SPECIAL_FILE;

	{
		char *filename = make_pathname(fp[idx].dir, fp[idx].name);
		sf->file_path = atom_str_get(filename);
		HFREE_NULL(filename);
	}
	if (shared_file_set_names(sf, sp->file)) {
		shared_file_free(&sf);
	} else {
		sf->mime_type = sp->type;
	}

	fclose(f);

done:
	HFREE_NULL(tmp);

	return sf;
}
