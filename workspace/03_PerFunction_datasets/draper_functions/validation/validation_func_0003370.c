on_popup_remove (GtkAction *action, ProjectManagerPlugin *plugin)
{
	GList *selected;

	selected = gbf_project_view_get_all_selected (plugin->view);

	if (selected != NULL)
	{
		if (confirm_removal (plugin, selected))
		{
			GError *err = NULL;
			GList *item;
			gboolean update = FALSE;

			for (item = g_list_first (selected); item != NULL; item = g_list_next (item))
			{
				GbfTreeData *data = (GbfTreeData *)(item->data);
				AnjutaProjectNode *node;

				switch (data->type)
				{
				case GBF_TREE_NODE_GROUP:
				case GBF_TREE_NODE_TARGET:
				case GBF_TREE_NODE_SOURCE:
				case GBF_TREE_NODE_MODULE:
				case GBF_TREE_NODE_PACKAGE:
					node = gbf_tree_data_get_node (data);
					if (node != NULL)
					{
						if (!update) update_operation_begin (plugin);
						anjuta_pm_project_remove (plugin->project, node, &err);
						if (err)
						{
							const gchar *name;

							update_operation_end (plugin, TRUE);
							update = FALSE;
							name = anjuta_project_node_get_name (node);
							anjuta_util_dialog_error (get_plugin_parent_window (plugin),
										  _("Failed to remove '%s':\n%s"),
										  name, err->message);
							g_error_free (err);
						}
					}
					break;
				case GBF_TREE_NODE_SHORTCUT:
					gbf_project_view_remove_data (plugin->view, data, NULL);
					break;
				default:
					break;
				}
			}
			if (update) update_operation_end (plugin, TRUE);
		}
		g_list_free (selected);
	}
}
