insert_paste_prompt(void)
{
	char *str;

	paste_prompt = TRUE;
	paste_old_prompt = g_strdup(active_entry->prompt);
	printformat_window(active_win, MSGLEVEL_CLIENTNOTICE,
			   TXT_PASTE_WARNING,
			   paste_line_count,
			   active_win->active == NULL ? "window" :
			   active_win->active->visible_name);

	str = format_get_text(MODULE_NAME, active_win, NULL, NULL,
			      TXT_PASTE_PROMPT, 0, 0);
	gui_entry_set_prompt(active_entry, str);
	paste_entry = gui_entry_get_text(active_entry);
	paste_entry_pos = gui_entry_get_pos(active_entry);
	gui_entry_set_text(active_entry, "");
	g_free(str);
}
