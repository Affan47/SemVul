gw_folder_get_disk ( GtkCTree *ctree, GtkCTreeNode *node)
{
	GtkCTreeNode *parent = NULL;
	GtkCTreeNode *root = NULL;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	root = gw_gui_manager_main_interface_get_tree_root ( );

	if ( GTK_CTREE_ROW ( node)->parent == root)
	{
		return node;
	}

	parent = GTK_CTREE_ROW ( node)->parent;

	while ( GTK_CTREE_ROW ( GTK_CTREE_ROW ( parent)->parent)->parent != NULL )
	{
		parent = GTK_CTREE_ROW ( parent)->parent;
	}

	return parent;
}
