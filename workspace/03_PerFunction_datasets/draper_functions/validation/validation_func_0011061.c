sheet_widget_radio_button_set_active (SheetWidgetRadioButton *swrb,
				      gboolean active)
{
	GList *ptr;

	if (swrb->active == active)
		return;
	swrb->active = active;

	swrb->being_updated = TRUE;

	for (ptr = swrb->sow.so.realized_list; ptr != NULL ; ptr = ptr->next) {
		SheetObjectView *view = ptr->data;
		GocWidget *item = get_goc_widget (view);
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (item->widget),
					      active);
	}

	g_object_notify (G_OBJECT (swrb), "active");

	swrb->being_updated = FALSE;
}
