void reds_on_main_agent_start(RedsState *reds, MainChannelClient *mcc, uint32_t num_tokens)
{
    RedCharDevice *dev_state = reds->agent_dev.get();
    RedClient *client;

    if (!reds->vdagent) {
        return;
    }
    spice_assert(reds->vdagent->st && reds->vdagent->st == dev_state);
    client = mcc->get_client();
    reds->agent_dev->priv->client_agent_started = true;


    RedCharDeviceClientOpaque *client_opaque = (RedCharDeviceClientOpaque *) client;
    if (!dev_state->client_exists(client_opaque)) {
        int client_added;

        client_added = dev_state->client_add(client_opaque, TRUE,
                                             REDS_VDI_PORT_NUM_RECEIVE_BUFFS,
                                             REDS_AGENT_WINDOW_SIZE,
                                             num_tokens,
                                             mcc->is_waiting_for_migrate_data());

        if (!client_added) {
            spice_warning("failed to add client to agent");
            mcc->shutdown();
            return;
        }
    } else {
        dev_state->send_to_client_tokens_set(client_opaque, num_tokens);
    }

    reds_send_device_display_info(reds);

    agent_msg_filter_config(&reds->agent_dev->priv->write_filter, reds->config->agent_copypaste,
                            reds->config->agent_file_xfer,
                            reds_use_client_monitors_config(reds));
    reds->agent_dev->priv->write_filter.discard_all = FALSE;
}
