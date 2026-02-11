goc_widget_connect_signals (GtkWidget *widget, GocWidget *item,
			    gboolean do_connect)
{
		if (GTK_IS_CONTAINER (widget)) {
			GList *children = gtk_container_get_children (GTK_CONTAINER (widget));
			GList *ptr;
			for (ptr = children; ptr; ptr = ptr->next) {
				GtkWidget *child = ptr->data;
				goc_widget_connect_signals (child, item, do_connect);
			}
			g_list_free (children);
		}

		if (do_connect) {
			g_signal_connect (widget, "enter-notify-event",
					  G_CALLBACK (enter_notify_cb), item);
			g_signal_connect (widget, "button-press-event",
					  G_CALLBACK (button_press_cb), item);
		} else {
			g_signal_handlers_disconnect_by_func
				(widget, G_CALLBACK (enter_notify_cb), item);
			g_signal_handlers_disconnect_by_func
				(widget, G_CALLBACK (button_press_cb), item);
		}
}
