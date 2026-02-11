reset_visuals(bool load_prefs)
{
	int i;
	struct flavor *f;


	for (i = 0; i < z_info->f_max; i++)
	{
		int j;
		feature_type *f_ptr = &f_info[i];


		for (j = 0; j < FEAT_LIGHTING_MAX; j++)
		{
			f_ptr->x_attr[j] = f_ptr->d_attr;
			f_ptr->x_char[j] = f_ptr->d_char;
		}
	}


	for (i = 0; i < z_info->k_max; i++)
	{
		object_kind *k_ptr = &k_info[i];


		k_ptr->x_attr = k_ptr->d_attr;
		k_ptr->x_char = k_ptr->d_char;
	}


	for (i = 0; i < z_info->r_max; i++)
	{
		monster_race *r_ptr = &r_info[i];


		r_ptr->x_attr = r_ptr->d_attr;
		r_ptr->x_char = r_ptr->d_char;
	}


	for (f = flavors; f; f = f->next)
	{
		f->x_attr = f->d_attr;
		f->x_char = f->d_char;
	}


	for (i = 0; i < (int)N_ELEMENTS(tval_to_attr); i++)
	{

		tval_to_attr[i] = TERM_WHITE;
	}

	if (!load_prefs)
		return;


	if (use_graphics) {

		graphics_mode *mode = get_graphics_mode(use_graphics);
		if (mode && strstr(mode->pref,".prf")) {
			(void)process_pref_file(mode->pref, FALSE, FALSE);
		} else {
			(void)process_pref_file("graf.prf", FALSE, FALSE);
		}


	} else {
		process_pref_file("font.prf", FALSE, FALSE);
	}
}
