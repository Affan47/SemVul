void callbacks_hadjustment_value_changed (GtkAdjustment *adjustment, gpointer user_data){


	if (screen.state == SCROLLBAR) {
		screenRenderInfo.lowerLeftX = gtk_adjustment_get_value (adjustment);
	}
}
