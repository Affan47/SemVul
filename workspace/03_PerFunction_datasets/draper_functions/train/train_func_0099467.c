check_nm_ev_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
	GtkWidget* xyplot = NULL;
	GList* data_list = NULL;
	GList* current = NULL;
	XYPlotWinData* data;
	gboolean nm = FALSE;
	GtkWidget* window = NULL;
	gdouble xmax = 0;
	gdouble ymax = 0;

	if(!user_data || !G_IS_OBJECT(user_data)) return;

	xyplot = GTK_WIDGET(user_data);
	data_list = g_object_get_data(G_OBJECT (xyplot), "DataList");

	if(!data_list) return;
	window = g_object_get_data(G_OBJECT (xyplot), "Window");

	nm = gtk_toggle_button_get_active(togglebutton);
	current=g_list_first(data_list);
	for(; current != NULL; current = current->next)
	{
		gint loop;
		data = (XYPlotWinData*)current->data;
		for (loop=0; loop<data->size; loop++)
		{
			if(fabs(data->x[loop])>1e-10)
			{
				if(nm) data->x[loop]= 1239.8424121/data->x[loop];
				else data->x[loop]= 1239.8424121/data->x[loop];
			}
			else
				data->x[loop]= 1e-10;
			if(xmax<data->x[loop]) xmax = data->x[loop];
			if(ymax<data->y[loop]) ymax = data->y[loop];
		}
	}
	xmax = xmax*1.5;
	ymax = ymax*2.0;
	spectrum_win_set_xmin(window, 0.0);
	spectrum_win_set_xmax(window, xmax);
	spectrum_win_set_ymax(window, ymax);
	spectrum_win_set_half_width(window, fabs(xmax/50));
	spectrum_win_reset_ymin_ymax(GTK_WIDGET(xyplot));
	if(nm)
	{
		spectrum_win_set_xlabel(window, "nm");
	}
	else
	{
		spectrum_win_set_xlabel(window, "eV");
	}
	gtk_widget_queue_draw(GTK_WIDGET(xyplot));

}
