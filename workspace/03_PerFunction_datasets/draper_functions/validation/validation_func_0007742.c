button_focus_in(GtkWidget *widget, GdkEventFocus *event, gComboBox *control)
{
	if (control->isReadOnly())
		return gcb_focus_in(widget, event, control);

	control->setFocus();
	return false;
}
