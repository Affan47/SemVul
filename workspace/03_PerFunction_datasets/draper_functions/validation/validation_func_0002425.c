reload_icons (GladeNamedIconChooserDialog *dialog)
{
	GtkListStore *store = dialog->priv->icons_store;
	GtkTreeIter   iter;
	guint         i;
	GList        *l, *icons = NULL;

	GDK_THREADS_ENTER ();


	for (i = 0; i < G_N_ELEMENTS (standard_contexts); i++) {

		GList *icons_in_context = gtk_icon_theme_list_icons (dialog->priv->icon_theme,
								     standard_contexts[i].name);

		for (l = icons_in_context; l; l = l->next) {

			IconData *data = g_slice_new (IconData);

			data->name = (gchar *) l->data;
			data->context = i;

			icons = g_list_prepend (icons, data);
		}

		g_list_free (icons_in_context);
	}


	icons = g_list_sort (icons, (GCompareFunc) icon_data_compare);


	for (l = icons; l; l = l->next) {

		IconData *data = (IconData *) l->data;

		gtk_list_store_append (store, &iter);
		gtk_list_store_set (store, &iter,
				    ICONS_CONTEXT_COLUMN,  data->context,
				    ICONS_STANDARD_COLUMN, is_standard_icon_name (data->name),
				    ICONS_NAME_COLUMN,     data->name,
			    	    -1);

		g_free (data->name);
		g_slice_free (IconData, data);
	}

	g_list_free (icons);

	chooser_set_model (dialog);

	GDK_THREADS_LEAVE ();

	return FALSE;
}
