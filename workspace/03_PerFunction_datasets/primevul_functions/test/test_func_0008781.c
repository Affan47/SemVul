void callbacks_vadjustment_value_changed (GtkAdjustment *adjustment, gpointer user_data){


	if (screen.state == SCROLLBAR) {
		screenRenderInfo.lowerLeftY = adjustment->upper -
			(gtk_adjustment_get_value (adjustment) + adjustment->page_size) + adjustment->lower;
	}
}
