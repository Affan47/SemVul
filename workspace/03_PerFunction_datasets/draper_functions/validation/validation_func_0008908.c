need_pre_notify(gpointer key, gpointer value, gpointer user_data)
{
    crm_client_t *client = value;

    if (is_set(client->options, cib_notify_pre)) {
        gboolean *needed = user_data;

        *needed = TRUE;
    }
}
