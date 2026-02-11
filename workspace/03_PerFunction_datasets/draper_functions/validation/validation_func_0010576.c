gsql_content_set_name (GSQLContent *content, gchar *name)
{
	GSQL_TRACE_FUNC;

	g_return_if_fail (GSQL_IS_CONTENT (content));
	g_return_if_fail (name != NULL);

	if (content->private->name)
		g_free (content->private->name);

	content->private->name = g_strdup (name);
	gsql_content_update_labels (content);

}
