e_tree_drag_source_set (ETree *tree,
                        GdkModifierType start_button_mask,
                        const GtkTargetEntry *targets,
                        gint n_targets,
                        GdkDragAction actions)
{
	ETreeDragSourceSite *site;
	GtkWidget *canvas;

	g_return_if_fail (E_IS_TREE (tree));

	canvas = GTK_WIDGET (tree->priv->table_canvas);
	site = tree->priv->site;

	tree->priv->do_drag = TRUE;

	gtk_widget_add_events (
		canvas,
		gtk_widget_get_events (canvas) |
		GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK |
		GDK_BUTTON_MOTION_MASK | GDK_STRUCTURE_MASK);

	if (site) {
		if (site->target_list)
			gtk_target_list_unref (site->target_list);
	} else {
		site = g_new0 (ETreeDragSourceSite, 1);
		tree->priv->site = site;
	}

	site->start_button_mask = start_button_mask;

	if (targets)
		site->target_list = gtk_target_list_new (targets, n_targets);
	else
		site->target_list = NULL;

	site->actions = actions;
}
