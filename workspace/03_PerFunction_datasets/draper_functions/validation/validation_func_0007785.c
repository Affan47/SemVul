configure_button_cb (GtkWidget* button,
                     ArioPluginManager* pm)
{
        ArioPluginInfo *info;
        GtkWindow *toplevel;

        info = plugin_manager_get_selected_plugin (pm);

        g_return_if_fail (info != NULL);

        ARIO_LOG_DBG ("Configuring: %s\n",  ario_plugin_info_get_name (info));

        toplevel = GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET(pm)));

        ario_plugins_engine_configure_plugin (info, toplevel);

        ARIO_LOG_DBG ("Done");
}
