OnSpaceToggled ()
{
	if (gtk_toggle_button_get_active (space_btn)) {
		gtk_widget_set_sensitive (GTK_WIDGET (padding_btn), true);
		gtk_widget_set_sensitive (dist_lbl, true);
	} else {
		gtk_widget_set_sensitive (GTK_WIDGET (padding_btn), false);
		gtk_widget_set_sensitive (dist_lbl, false);
	}
}
