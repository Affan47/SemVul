abi_widget_realize (GtkWidget * widget)
{
	AbiWidget * abi;
	GdkWindowAttr attributes;
	gint attributes_mask;
	GtkAllocation alloc;


	UT_return_if_fail (widget != NULL);
	UT_return_if_fail (IS_ABI_WIDGET(widget));

	gtk_widget_set_realized(widget, true);
	abi = ABI_WIDGET(widget);

	gtk_widget_get_allocation(widget, &alloc);
	attributes.x = alloc.x;
	attributes.y = alloc.y;
	attributes.width = ABI_DEFAULT_WIDTH;
	attributes.height = ABI_DEFAULT_HEIGHT;
	attributes.wclass = GDK_INPUT_OUTPUT;
	attributes.window_type = GDK_WINDOW_CHILD;
	attributes.event_mask = gtk_widget_get_events (widget) |
						GDK_EXPOSURE_MASK | GDK_BUTTON_PRESS_MASK | GDK_KEY_PRESS_MASK |
						GDK_BUTTON_RELEASE_MASK | GDK_POINTER_MOTION_MASK |
						GDK_POINTER_MOTION_HINT_MASK | GDK_ENTER_NOTIFY_MASK |
						GDK_LEAVE_NOTIFY_MASK |
						GDK_FOCUS_CHANGE_MASK |
						GDK_STRUCTURE_MASK;
	attributes.visual = gtk_widget_get_visual (widget);

	attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL;

	gtk_widget_set_window(widget,
	                      gdk_window_new (gtk_widget_get_parent_window (widget),
	                                      &attributes, attributes_mask));
	gdk_window_set_user_data (gtk_widget_get_window(widget), abi);


	g_signal_connect_after(G_OBJECT(widget),"map",
			       G_CALLBACK (s_abi_widget_map_cb),
			       (gpointer) abi);
}
