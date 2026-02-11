create_enum_editor (RBObjectPropertyEditor *editor, const char *property, GParamSpec *pspec)
{
	GParamSpecEnum *penum;
	GtkListStore *model;
	GtkCellRenderer *renderer;
	GtkWidget *control;
	int p;

	control = gtk_combo_box_new ();
	penum = G_PARAM_SPEC_ENUM (pspec);
	renderer = gtk_cell_renderer_text_new ();

	model = gtk_list_store_new (2, G_TYPE_STRING, G_TYPE_INT);
	gtk_combo_box_set_model (GTK_COMBO_BOX (control), GTK_TREE_MODEL (model));
	for (p = 0; p < penum->enum_class->n_values; p++) {
		gtk_list_store_insert_with_values (model, NULL, p,
						   0, penum->enum_class->values[p].value_name,
						   1, p,
						   -1);
	}
	gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (control), renderer, TRUE);
	gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT (control), renderer, "text", 0, NULL);

	g_object_bind_property (editor->priv->object, property,
				control, "active",
				G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);

	return control;
}
