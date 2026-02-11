prefs_matcher_enable_widget(GtkWidget* widget, const gboolean enable)
{
	cm_return_if_fail(widget != NULL);

	if(enable == TRUE) {
		gtk_widget_set_sensitive(widget, TRUE);
		gtk_widget_show(widget);
	} else {
		gtk_widget_set_sensitive(widget, FALSE);
		gtk_widget_hide(widget);
	}
}
