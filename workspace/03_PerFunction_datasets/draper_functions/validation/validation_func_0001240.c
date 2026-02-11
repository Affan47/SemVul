brasero_data_project_add_loading_node_real (BraseroDataProject *self,
					    const gchar *uri,
					    const gchar *name_arg,
					    gboolean is_hidden,
					    BraseroFileNode *parent)
{
	gchar *name;
	BraseroFileNode *node;
	BraseroURINode *graft;
	BraseroFileNode *sibling;
	BraseroDataProjectPrivate *priv;

	priv = BRASERO_DATA_PROJECT_PRIVATE (self);

	graft = g_hash_table_lookup (priv->grafts, uri);
	if (!parent)
		parent = priv->root;

	if (!name_arg) {

		name = brasero_utils_get_uri_name (uri);
	}
	else
		name = g_strdup (name_arg);


	sibling = brasero_file_node_check_name_existence (parent, name);
	if (sibling) {
		if (BRASERO_FILE_NODE_VIRTUAL (sibling)) {
			node = brasero_file_node_new_loading (name);
			brasero_data_project_virtual_sibling (self, node, sibling);
		}
		else if (brasero_data_project_node_signal (self, NAME_COLLISION_SIGNAL, sibling)) {
			g_free (name);
			return NULL;
		}
		else {


			brasero_data_project_remove_real (self, sibling);
			node = brasero_file_node_new_loading (name);
			graft = g_hash_table_lookup (priv->grafts, uri);
		}
	}
	else
		node = brasero_file_node_new_loading (name);

	g_free (name);

	brasero_file_node_add (parent, node, priv->sort_func);

	node->is_hidden = is_hidden;
	if (!brasero_data_project_add_node_real (self, node, graft, uri))
		return NULL;

	return node;
}
