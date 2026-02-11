nautilus_drag_autoscroll_start (NautilusDragInfo *drag_info,
				GtkWidget        *widget,
				GSourceFunc       callback,
				gpointer          user_data)
{
	if (nautilus_drag_autoscroll_in_scroll_region (widget)) {
		if (drag_info->auto_scroll_timeout_id == 0) {
			drag_info->waiting_to_autoscroll = TRUE;
			drag_info->start_auto_scroll_in = g_get_monotonic_time ()
				+ AUTOSCROLL_INITIAL_DELAY;

			drag_info->auto_scroll_timeout_id = g_timeout_add
				(AUTOSCROLL_TIMEOUT_INTERVAL,
				 callback,
			 	 user_data);
		}
	} else {
		if (drag_info->auto_scroll_timeout_id != 0) {
			g_source_remove (drag_info->auto_scroll_timeout_id);
			drag_info->auto_scroll_timeout_id = 0;
		}
	}
}
