git_revisions_get_command_line (GiggleJob  *job,
                                gchar     **command_line)
{
	GiggleGitRevisionsPriv *priv;
	GString                *str;
	GList                  *files;

	priv = GIGGLE_GIT_REVISIONS (job)->priv;

	files = priv->files;
	str = g_string_new (GIT_COMMAND " rev-list --all --header --topo-order --parents");

	while (files) {
		g_string_append_printf (str, " %s", (gchar *) files->data);
		files = files->next;
	}

	*command_line = g_string_free (str, FALSE);
	return TRUE;
}
