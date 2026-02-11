send_client_notify(gpointer key, gpointer value, gpointer user_data)
{
    xmlNode *update_msg = user_data;
    crm_client_t *client = value;

    if (client == NULL) {
        crm_err("Asked to send event to  NULL client");
        return;
    } else if (client->name == NULL) {
        crm_trace("Asked to send event to client with no name");
        return;
    }

    if (lrmd_server_send_notify(client, update_msg) <= 0) {
        crm_warn("Notification of client %s/%s failed", client->name, client->id);
    }
}
