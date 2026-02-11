gcr_tree_selector_constructor (GType type, guint n_props, GObjectConstructParam *props)
{
	GcrTreeSelector *self = GCR_TREE_SELECTOR (G_OBJECT_CLASS (gcr_tree_selector_parent_class)->constructor(type, n_props, props));
	const GcrColumn *column;
	guint i;

	g_return_val_if_fail (self, NULL);
	g_return_val_if_fail (self->pv->columns, NULL);

	self->pv->model = gcr_collection_model_new_full (self->pv->collection,
	                                                 GCR_COLLECTION_MODEL_TREE,
	                                                 self->pv->columns);

	gtk_tree_view_set_model (GTK_TREE_VIEW (self), GTK_TREE_MODEL (self->pv->model));


	add_check_column (self, gcr_collection_model_column_for_selected (self->pv->model));

	for (column = self->pv->columns, i = 0; column->property_name; ++column, ++i) {
		if (column->flags & GCR_COLUMN_HIDDEN)
			continue;

		if (column->column_type == G_TYPE_STRING)
			add_string_column (self, column, i);
		else if (column->column_type == G_TYPE_ICON)
			add_icon_column (self, column, i);
		else
			g_warning ("skipping unsupported column '%s' of type: %s",
			           column->property_name, g_type_name (column->column_type));
	}

	return G_OBJECT (self);
}
