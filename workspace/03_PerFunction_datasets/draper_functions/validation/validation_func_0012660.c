preferences_window_destroy(void)
{
    GtkWidget *dialog = (GtkWidget *) gtk_builder_get_object(xml_preferences_window, "preferences_window");
    if (plugin_last >= 0)
    {
        gmpc_plugin_preferences_destroy(plugins[plugin_last],
            (GtkWidget *) gtk_builder_get_object(xml_preferences_window,
            "plugin_container"));
        plugin_last = -1;

    } else if (plugin_last == PLUGIN_STATS)
    {
        plugin_stats_destroy((GtkWidget *) gtk_builder_get_object(xml_preferences_window, "plugin_container"));
    }
    gtk_widget_destroy(dialog);
    g_object_unref(xml_preferences_window);
    g_object_unref(plugin_store);
    plugin_store = NULL;
    xml_preferences_window = NULL;
    running = 0;
}
