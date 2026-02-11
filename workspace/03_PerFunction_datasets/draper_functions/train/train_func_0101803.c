python_assist_query_calltip (PythonAssist* assist, const gchar *call_context)
{
	IAnjutaEditor *editor = IANJUTA_EDITOR (assist->priv->iassist);

	gint offset = python_assist_get_calltip_context_position (assist);

	gchar *interpreter_path;
	const gchar *cur_filename;
	gchar *source = ianjuta_editor_get_text_all (editor, NULL);
	const gchar *project = assist->priv->project_root;
	gchar *tmp_file;
	gchar *ropecommand;

	cur_filename = assist->priv->editor_filename;
	if (!project)
		project = g_get_tmp_dir ();

	interpreter_path = g_settings_get_string (assist->priv->settings,
	                                          PREF_INTERPRETER_PATH);

	tmp_file = create_tmp_file (source);
	g_free (source);

	if (!tmp_file)
		return;

	ropecommand = g_strdup_printf("%s %s -o calltip -p \"%s\" -r \"%s\" -s \"%s\" -f %d",
								interpreter_path, AUTOCOMPLETE_SCRIPT, project,
								cur_filename, tmp_file, offset);

	DEBUG_PRINT ("%s", ropecommand);

	g_free (tmp_file);


	assist->priv->calltip_launcher = anjuta_launcher_new ();
	g_signal_connect (assist->priv->calltip_launcher, "child-exited",
	                  G_CALLBACK(on_calltip_finished), assist);
	anjuta_launcher_execute (assist->priv->calltip_launcher, ropecommand,
	                         on_calltip_output,
	                         assist);
	g_free (ropecommand);
}
