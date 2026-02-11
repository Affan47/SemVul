gtksharp_widget_base_drag_data_received (GtkWidget* widget, GdkDragContext* context, gint x, gint y, GtkSelectionData* selection_data, guint info, guint time_)
{
	GtkWidgetClass *klass = (GtkWidgetClass *) get_threshold_class (G_OBJECT (widget));
	if (klass->drag_data_received)
		(* klass->drag_data_received) (widget, context, x, y, selection_data, info, time_);
}
