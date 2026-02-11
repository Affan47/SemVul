cx_select_files(void)
{
	int i, fn;
	FLAG select;
	const char *sre;
	FILE_ENTRY *pfe;

	if (line_tmp.size == 0) {
		next_mode = MODE_SPECIAL_RETURN;
		return;
	}
	sre = USTR(textline->line);
	if (match_sre(sre) < 0)

		return;

	if (get_current_mode() == MODE_SELECT) {
		select = 1; fn = FN_SELECT;
	}
	else {
		select = 0; fn = FN_DESELECT;
	}
	for (i = 0; i < ppanel_file->pd->cnt; i++) {
		pfe = ppanel_file->files[i];
		if (select == !pfe->select && match(SDSTR(pfe->file)))
			ppanel_file->selected += selectfile(pfe,fn);
	}
	win_panel();
	next_mode = MODE_SPECIAL_RETURN;
}
