addConvFromList(GtkWidget* list)
{
	gint n = 0;
	gdouble* X = NULL;
	gdouble* Y = NULL;
	GdkColor color;
	GtkWidget* xyplot = getPointsFromList(list, &X, &Y, &n);
	GtkWidget* entryHalfWidth = NULL;
	gdouble halfWidth = 0.05;
	GabeditXYPlotConvType convType = GABEDIT_XYPLOT_CONV_LORENTZ;
  	GtkWidget* toggleLorentzian = g_object_get_data(G_OBJECT (list), "ToggleLorentzian");

	if(!xyplot) return;

	entryHalfWidth = g_object_get_data(G_OBJECT(list),"EntryHalfWidth");
	if(entryHalfWidth)
	{
		G_CONST_RETURN gchar* tentry;
		tentry = gtk_entry_get_text(GTK_ENTRY(entryHalfWidth));
		halfWidth = atof(tentry);
		if(halfWidth<1e-12)
		{
			gtk_entry_set_text(GTK_ENTRY(entryHalfWidth),"0.05");
			halfWidth = 0.05;
		}
	}
	if(!GTK_TOGGLE_BUTTON (toggleLorentzian)->active) convType = GABEDIT_XYPLOT_CONV_GAUSS;
	color.red = 65000;
	color.green = 0;
	color.blue = 0;
	gabedit_xyplot_add_data_conv(GABEDIT_XYPLOT(xyplot), n, X,  Y, halfWidth, convType, &color);
	gabedit_xyplot_set_range_ymin (GABEDIT_XYPLOT(xyplot), 0);
	gabedit_xyplot_set_range_ymax (GABEDIT_XYPLOT(xyplot), 100);
	if(X)
	{
		gabedit_xyplot_set_range_xmin (GABEDIT_XYPLOT(xyplot), (gint)(X[0]-10*halfWidth));
		gabedit_xyplot_set_range_xmax (GABEDIT_XYPLOT(xyplot), (gint)(X[n-1]+10*halfWidth+0.5));
	}
	if(X) g_free(X);
	if(Y) g_free(Y);
}
