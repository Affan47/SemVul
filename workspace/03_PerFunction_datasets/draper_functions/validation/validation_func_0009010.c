aai_destroy_cb(GtkObject *object, gpointer user_data)
{
    ABInitialInfo *info = user_data;

    gnc_unregister_gui_component_by_data(ASSISTANT_AB_INITIAL_CM_CLASS, info);

    if (info->deferred_info)
    {
        g_message("Online Banking assistant is being closed but the wizard is still "
                  "running.  Inoring.");


        info->deferred_info->initial_info = NULL;
    }

    if (info->gnc_hash)
    {
#ifdef AQBANKING_VERSION_4_EXACTLY
        AB_Banking_OnlineFini(info->api, 0);
#else
        AB_Banking_OnlineFini(info->api);
#endif
        g_hash_table_destroy(info->gnc_hash);
        info->gnc_hash = NULL;
    }

    if (info->api)
    {
        gnc_AB_BANKING_delete(info->api);
        info->api = NULL;
    }

    gtk_widget_destroy(info->window);
    info->window = NULL;

    g_free(info);
}
