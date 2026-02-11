drag_data_recieved_cb (GtkWidget	*widget,
		       GdkDragContext   *context,
		       gint              x,
		       gint              y,
		       GtkSelectionData *selection_data,
		       guint             info,
		       guint             time)
{
	PanelWidget         *panel_widget;
	PanelObjectPackType  pack_type = PANEL_OBJECT_PACK_START;
	int                  pack_index = 0;

	g_return_if_fail (PANEL_IS_TOPLEVEL (widget));


	if (!panel_check_dnd_target_data (widget, context, &info, NULL)) {
		gtk_drag_finish (context, FALSE, FALSE, time);
		return;
	}

	panel_widget = panel_toplevel_get_panel_widget (PANEL_TOPLEVEL (widget));

	panel_widget_get_insert_at_cursor (panel_widget, &pack_type, &pack_index);

	panel_receive_dnd_data (
		panel_widget, info, pack_type, pack_index,
		selection_data, context, time);
}
