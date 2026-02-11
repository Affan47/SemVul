on_goto_file_tag_decl_activate (GtkAction *action, SymbolDBPlugin *sdb_plugin)
{
	IAnjutaEditor *ed;
	gchar *word;

	if (sdb_plugin->current_editor)
	{
		ed = IANJUTA_EDITOR (sdb_plugin->current_editor);
		word = ianjuta_editor_get_current_word (ed, NULL);
		if (word)
		{
			goto_file_tag (sdb_plugin, word, FALSE);
			g_free (word);
		}
	}
}
