plugin_init(G_GNUC_UNUSED GeanyData * data)
{
	GeanyDocument *doc = NULL;

	doc = document_get_current();

	main_locale_init(LOCALEDIR, GETTEXT_PACKAGE);

	glatex_init_configuration();
	glatex_init_encodings_latex();

	add_wizard_to_tools_menu();

	init_keybindings();


	if (glatex_set_toolbar_active == TRUE)
	{
		glatex_toolbar = init_toolbar();
	}
	else
	{
		glatex_toolbar = NULL;
	}

	if (glatex_wizard_to_generic_toolbar == TRUE)
	{
		add_wizard_to_generic_toolbar();
	}
	else
	{
		glatex_wizard_generic_toolbar_item = NULL;
	}

	if (doc != NULL)
	{
		if (glatex_add_menu_on_startup == TRUE||
			doc->file_type->id == GEANY_FILETYPES_LATEX)
		{
			add_menu_to_menubar();
		}
	}

}
