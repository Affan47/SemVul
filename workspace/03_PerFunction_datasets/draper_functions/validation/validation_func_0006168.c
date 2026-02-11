update_inactive_actions(GncPluginPage *plugin_page)
{
    GncMainWindow  *window;
    GtkActionGroup *action_group;
    GtkAction *file_save_action;


    gboolean is_readwrite = !qof_book_is_readonly(gnc_get_current_book());
    gboolean is_dirty = qof_book_session_not_saved (gnc_get_current_book ());


    if (!plugin_page || !GNC_IS_PLUGIN_PAGE(plugin_page))
        return;

    window = GNC_MAIN_WINDOW(plugin_page->window);
    g_return_if_fail(GNC_IS_MAIN_WINDOW(window));
    action_group = gnc_main_window_get_action_group(window, PLUGIN_ACTIONS_NAME);
    g_return_if_fail(GTK_IS_ACTION_GROUP(action_group));


    gnc_plugin_update_actions (action_group, readonly_inactive_actions,
                               "sensitive", is_readwrite);

    file_save_action = gtk_action_group_get_action (action_group,
                       "FileSaveAction");
    gtk_action_set_sensitive (file_save_action, is_readwrite && is_dirty);
}
