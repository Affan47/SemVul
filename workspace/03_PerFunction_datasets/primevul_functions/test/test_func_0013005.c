void reds_client_disconnect(RedsState *reds, RedClient *client)
{
    RedsMigTargetClient *mig_client;

    if (reds->config->exit_on_disconnect)
    {
        spice_debug("Exiting server because of client disconnect.");
        exit(0);
    }

    if (!client || client->is_disconnecting()) {
        spice_debug("client %p already during disconnection", client);
        return;
    }

    spice_debug("trace");


    client->set_disconnecting();


    mig_client = reds_mig_target_client_find(reds, client);
    if (mig_client) {
        reds_mig_target_client_free(reds, mig_client);
    }

    if (reds->mig_wait_disconnect) {
        reds_mig_remove_wait_disconnect_client(reds, client);
    }


    RedCharDeviceClientOpaque *client_opaque = (RedCharDeviceClientOpaque *) client;
    if (reds->agent_dev->client_exists(client_opaque)) {
        reds->agent_dev->client_remove(client_opaque);
    }

    reds->clients.remove(client);
    client->destroy();


    if (reds->clients.empty()) {

        if (reds->agent_dev->priv->agent_attached) {
            RedCharDeviceWriteBuffer *char_dev_buf =
                vdagent_new_write_buffer(reds->agent_dev.get(),
                                         VD_AGENT_CLIENT_DISCONNECTED,
                                         0,
                                         false);

            reds->agent_dev->write_buffer_add(char_dev_buf);
        }


        agent_msg_filter_init(&reds->agent_dev->priv->write_filter, reds->config->agent_copypaste,
                              reds->config->agent_file_xfer,
                              reds_use_client_monitors_config(reds), TRUE);


        reds->agent_dev->priv->read_filter.result = AGENT_MSG_FILTER_DISCARD;
        reds->agent_dev->priv->read_filter.discard_all = TRUE;
        g_free(reds->agent_dev->priv->mig_data);
        reds->agent_dev->priv->mig_data = NULL;

        reds_mig_cleanup(reds);
    }
}
