init_upnp (void)
{
        GUPnPWhiteList *white_list;

#if !GLIB_CHECK_VERSION(2, 35, 0)
        g_type_init ();
#endif

        context_manager = gupnp_context_manager_new (NULL, upnp_port);
        g_assert (context_manager != NULL);

        if (interfaces != NULL) {
                white_list = gupnp_context_manager_get_white_list
                                            (context_manager);
                gupnp_white_list_add_entryv (white_list, interfaces);
                gupnp_white_list_set_enabled (white_list, TRUE);
        }

        g_signal_connect (context_manager,
                          "context-available",
                          G_CALLBACK (on_context_available),
                          NULL);

        return TRUE;
}
