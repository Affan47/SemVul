prefs_filtering_action_register_cb(void)
{
	FilteringAction *action;

	action = prefs_filtering_action_dialog_to_action(TRUE);
	if (action == NULL)
		return;

	prefs_filtering_action_list_view_set_row(NULL, action);

	filteringaction_free(action);


	gtk_combo_box_set_active(GTK_COMBO_BOX(filtering_action.account_combo), 0);
	gtk_combo_box_set_active(GTK_COMBO_BOX(filtering_action.tags_combo), 0);
	gtk_entry_set_text(GTK_ENTRY(filtering_action.dest_entry), "");
}
