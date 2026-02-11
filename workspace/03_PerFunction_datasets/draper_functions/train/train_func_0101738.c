glade_gtk_action_post_create (GladeWidgetAdaptor *adaptor,
			      GObject            *object,
			      GladeCreateReason   reason)
{
	GladeWidget *gwidget = glade_widget_get_from_gobject (object);

	if (reason == GLADE_CREATE_REBUILD)
		return;

	if (!gtk_action_get_name (GTK_ACTION (object)))
		glade_widget_property_set (gwidget, "name", "untitled");

	glade_widget_set_action_sensitive (gwidget, "launch_editor", FALSE);
	glade_widget_property_set_sensitive (gwidget, "accelerator", FALSE,
					     ACTION_ACCEL_INSENSITIVE_MSG);
}
