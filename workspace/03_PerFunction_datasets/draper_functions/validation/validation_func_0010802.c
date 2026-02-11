drag_motion_playlist_cb (GtkWidget      *widget,
			 GdkDragContext *context,
			 gint            x,
			 gint            y,
			 guint           _time,
			 Totem          *totem)
{
	GdkModifierType mask;

	gdk_window_get_pointer (gtk_widget_get_window (widget), NULL, NULL, &mask);

	if (mask & GDK_MOD1_MASK || gdk_drag_context_get_suggested_action (context) == GDK_ACTION_ASK)
		gdk_drag_status (context, GDK_ACTION_ASK, _time);
}
