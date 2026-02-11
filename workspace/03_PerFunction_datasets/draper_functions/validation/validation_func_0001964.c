gdm_session_select_session_type (GdmSession *self,
                                 const char *text)
{
        GHashTableIter iter;
        gpointer key, value;

        g_hash_table_iter_init (&iter, self->priv->conversations);
        while (g_hash_table_iter_next (&iter, &key, &value)) {
                GdmSessionConversation *conversation;

                conversation = (GdmSessionConversation *) value;

                gdm_dbus_worker_call_set_session_type (conversation->worker_proxy,
                                                       text,
                                                       NULL, NULL, NULL);
        }
}
