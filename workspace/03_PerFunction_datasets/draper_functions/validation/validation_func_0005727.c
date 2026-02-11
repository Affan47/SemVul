on_user_list_selection(struct SCNotification* nt,
				   ScintillaObject* scintilla,
				   presage_t presage)
{
    char* selection;
    char* completion;

    g_print("on_user_list_selection()\n");

    if (glob_function_keys_mode)
    {

	const char* separator;

	separator = strchr (nt->text, ' ');
	if (NULL == separator)
	{

	    return;
	}
	selection = strdup (separator + 1);
    }
    else
    {
	selection = strdup (nt->text);
    }

    g_print("selected text: %s\n", nt->text);

    if (PRESAGE_OK == presage_completion (presage, selection, &completion))
    {
	uptr_t length = strlen (completion);
	sptr_t str = (sptr_t) completion;

	scintilla_send_message (scintilla,
				SCI_ADDTEXT,
				length,
				str);
    }

    free (selection);
    presage_free_string (completion);


}
