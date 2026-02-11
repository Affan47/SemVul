trendtime_export_csv(GtkWidget *widget, gpointer user_data)
{
struct trendtime_data *data;
GtkTreeModel *model;
GtkTreeIter	iter;
gboolean valid;
gchar *filename = NULL;
GIOChannel *io;
gchar *outstr, *name;
gint tmpfor;

	DB( g_print("\n[trendtime] export csv\n") );

	data = g_object_get_data(G_OBJECT(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW)), "inst_data");

	tmpfor  = gtk_combo_box_get_active(GTK_COMBO_BOX(data->CY_for));

	name = g_strdup_printf("hb-trendtime_%s.csv", CYA_TIMESELECT[tmpfor]);

	if( ui_file_chooser_csv(GTK_WINDOW(data->window), GTK_FILE_CHOOSER_ACTION_SAVE, &filename, name) == TRUE )
	{
		DB( g_print(" + filename is %s\n", filename) );

		io = g_io_channel_new_file(filename, "w", NULL);
		if(io != NULL)
		{

			outstr = g_strdup_printf("%s;%s;\n", _("Time slice"), _("Amount"));
			g_io_channel_write_chars(io, outstr, -1, NULL, NULL);

			model = gtk_tree_view_get_model(GTK_TREE_VIEW(data->LV_report));
			valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(model), &iter);

			while (valid)
			{
			gchar *name;
			gdouble amount;

				gtk_tree_model_get (model, &iter,

					LST_STAT_TITLE  , &name,
					LST_STAT_AMOUNT , &amount,

					-1);

				outstr = g_strdup_printf("%s;%.2f\n", name, amount);
				g_io_channel_write_chars(io, outstr, -1, NULL, NULL);

				DB( g_print("%s", outstr) );

				g_free(outstr);

				valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(model), &iter);
			}

			g_io_channel_unref (io);
		}

		g_free( filename );
	}

	g_free(name);


}
