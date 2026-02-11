button_press_event (GtkWidget *widget,
		    GdkEventButton *event)
{
	NemoIconContainer *container;
	gboolean selection_changed;
	gboolean return_value;
	gboolean clicked_on_icon;

	container = NEMO_ICON_CONTAINER (widget);
        container->details->button_down_time = event->time;


        clear_keyboard_focus (container);
	clear_keyboard_rubberband_start (container);

	if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_3BUTTON_PRESS) {

		return TRUE;
	}


	clicked_on_icon = GTK_WIDGET_CLASS (nemo_icon_container_parent_class)->button_press_event (widget, event);


  	if (!gtk_widget_has_focus (widget) && !(is_renaming (container) || is_renaming_pending (container))) {
    		gtk_widget_grab_focus (widget);
    	}

	if (clicked_on_icon) {
		return TRUE;
	}

	if (event->button == DRAG_BUTTON &&
	    event->type == GDK_BUTTON_PRESS) {

		container->details->double_click_icon[1] = container->details->double_click_icon[0];
		container->details->double_click_icon[0] = NULL;
	}


	if (event->button == RUBBERBAND_BUTTON) {
		if (! button_event_modifies_selection (event)) {
			selection_changed = unselect_all (container);
			if (selection_changed) {
				g_signal_emit (container,
						 signals[SELECTION_CHANGED], 0);
			}
		}

		start_rubberbanding (container, event);
		return TRUE;
	}


	if (container->details->rubberband_info.active) {
		return TRUE;
	}


	if (event->button == MIDDLE_BUTTON) {
		selection_changed = unselect_all (container);
		if (selection_changed) {
			g_signal_emit (container, signals[SELECTION_CHANGED], 0);
		}
		g_signal_emit (widget, signals[MIDDLE_CLICK], 0, event);
		return TRUE;
	}


	if (event->button == CONTEXTUAL_MENU_BUTTON) {
		end_renaming_mode (container, TRUE);
		selection_changed = unselect_all (container);
		if (selection_changed) {
			g_signal_emit (container, signals[SELECTION_CHANGED], 0);
		}
		g_signal_emit (widget, signals[CONTEXT_CLICK_BACKGROUND], 0, event);
		return TRUE;
	}


	g_signal_emit (widget,
		       signals[BUTTON_PRESS], 0, event,
		       &return_value);
	return return_value;
}
