gwy_app_data_proxy_disconnect_mask(GwyAppDataProxy *proxy,
                                   gint id)
{
    GwyAppDataAssociation *assoc;
    GList *item;
    GtkTreeIter iter;
    GObject *object;

    gwy_debug("%u: from %p", id, proxy->container);
    assoc = gwy_app_data_assoc_get(&proxy->associated_mask, id);
    g_return_if_fail(assoc);
    object = assoc->object;
    g_object_set_qdata(object, container_quark, NULL);
    g_object_set_qdata(object, own_key_quark, NULL);
    g_signal_handlers_disconnect_by_func(object,
                                         gwy_app_data_proxy_mask_changed,
                                         proxy);
    item = proxy->associated_mask;
    proxy->associated_mask = g_list_remove_link(proxy->associated_mask, item);
    g_slice_free(GwyAppDataAssociation, assoc);
    g_list_free_1(item);
    g_object_unref(object);

    if (!gwy_app_data_proxy_find_object(proxy->lists[PAGE_CHANNELS].store, id,
                                        &iter))
        return;
    gtk_list_store_set(proxy->lists[PAGE_CHANNELS].store, &iter,
                       MODEL_TIMESTAMP, gwy_get_timestamp(),
                       -1);
    gwy_app_data_browser_notify_watch(channel_watchers, proxy->container, id,
                                      GWY_DATA_WATCH_EVENT_CHANGED);
}
