gtt_projects_tree_set_active_bgcolor (GttProjectsTree *gpt, gchar *color)
{
	GttProjectsTreePrivate *priv = GTT_PROJECTS_TREE_GET_PRIVATE (gpt);

	if (priv->active_bgcolor)
	{
		g_free (priv->active_bgcolor);
	}

	if (color)
	{
		priv->active_bgcolor = g_strdup (color);
	}
	else
	{
		priv->active_bgcolor = NULL;
	}

	gtt_projects_tree_update_all_rows (gpt);

}
