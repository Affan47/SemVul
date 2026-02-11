shell_view_set_enabled(gboolean setting)
{
    if (!params.gui_running)
	return;

    if (setting) {
	shell->_pulses = 0;
	widget_set_cursor(shell->window, GDK_LEFT_PTR);
    } else {
	widget_set_cursor(shell->window, GDK_WATCH);
    }

    gtk_widget_set_sensitive(shell->hpaned, setting);
    shell_action_set_enabled("ViewMenuAction", setting);
    shell_action_set_enabled("RefreshAction", setting);
    shell_action_set_enabled("CopyAction", setting);
    shell_action_set_enabled("ReportAction", setting);
    shell_action_set_enabled("SyncManagerAction", setting && sync_manager_count_entries() > 0);
    shell_action_set_enabled("SaveGraphAction",
			     setting ? shell->view_type ==
			     SHELL_VIEW_PROGRESS : FALSE);
}
