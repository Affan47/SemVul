gnome_scan_enum_widget_set (GnomeScanParamWidget *gspw, GValue *value)
{
	GnomeScanEnumWidgetPrivate *priv = GET_PRIVATE (gspw);
	GtkTreeIter iter;
	GValue *test_value;

	gtk_tree_model_get_iter_first (GTK_TREE_MODEL (priv->liststore), &iter);
	for (; gtk_list_store_iter_is_valid (priv->liststore, &iter)
		 ; gtk_tree_model_iter_next (GTK_TREE_MODEL (priv->liststore), &iter)) {
		gtk_tree_model_get (GTK_TREE_MODEL (priv->liststore), &iter,
							ENUM_VALUE, &test_value,
							-1);
		if (gs_param_values_cmp (gspw->pspec, value, test_value) == 0) {
			gtk_combo_box_set_active_iter (GTK_COMBO_BOX (priv->combo),
										   &iter);
			break;
		}
	}
}
