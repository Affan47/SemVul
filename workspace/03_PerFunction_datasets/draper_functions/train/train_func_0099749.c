prefs_filtering_action_open(GSList *action_list,
    PrefsFilteringActionSignal *cb)
{
	inc_lock();

	if (!filtering_action.window) {
		prefs_filtering_action_create();
	} else {
#if !GTK_CHECK_VERSION(3, 0, 0)

		gtk_cmoption_menu_set_menu(GTK_CMOPTION_MENU(filtering_action.color_optmenu),
				colorlabel_create_color_menu());
#endif
	}

	manage_window_set_transient(GTK_WINDOW(filtering_action.window));
	gtk_widget_grab_focus(filtering_action.ok_btn);

	filtering_action_callback = cb;

	prefs_filtering_action_set_dialog(action_list);

	gtk_widget_show(filtering_action.window);
}
