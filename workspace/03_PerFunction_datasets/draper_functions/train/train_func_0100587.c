cct_accept(MainInfo *min)
{
	P_Controls	*page = &the_page;

	if(page->modified)
	{
		if(ctrl_mouse_ambiguity_exists(page->ctrlinfo))
		{
			dlg_dialog_async_new_simple(_("Note: The mouse button control settings\n"
						    "are ambiguous: the same button+modifier\n"
						    "is used for more than one function. This\n"
						    "might make their behaviour pretty weird..."),
							_("Warning"), _("_OK"), NULL, NULL);
		}
		ctrl_destroy(min->cfg.ctrlinfo);
		min->cfg.ctrlinfo = page->ctrlinfo;
		page->ctrlinfo = NULL;
		cfg_set_flags(CFLG_RESET_KEYBOARD);
		page->modified = FALSE;
	}
}
