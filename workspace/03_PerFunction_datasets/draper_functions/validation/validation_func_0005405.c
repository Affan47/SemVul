nautilus_window_view_visible (NautilusWindow *window,
			      NautilusView   *view)
{
	NautilusWindowSlot *slot;
	GList *l;

	g_return_if_fail (NAUTILUS_IS_WINDOW (window));


	slot = nautilus_view_get_nautilus_window_slot (view);
	if (g_object_get_data (G_OBJECT (slot), "nautilus-window-view-visible") != NULL) {
		return;
	}

	g_object_set_data (G_OBJECT (slot), "nautilus-window-view-visible", GINT_TO_POINTER (1));


	for (l = window->details->slots; l != NULL; l = l->next) {
		slot = l->data;
		if (g_object_get_data (G_OBJECT (slot), "nautilus-window-view-visible") == NULL) {
			return;
		}
	}


	for (l = window->details->slots; l != NULL; l = l->next) {
		slot = l->data;
		nautilus_window_slot_update_title (slot);
	}

	nautilus_window_grab_focus (window);


	gtk_widget_show (GTK_WIDGET (window));
}
