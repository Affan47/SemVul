static void reds_reset_vdp(RedsState *reds)
{
    RedCharDeviceVDIPort *dev = reds->agent_dev.get();
    SpiceCharDeviceInterface *sif;

    dev->priv->read_state = VDI_PORT_READ_STATE_READ_HEADER;
    dev->priv->receive_pos = (uint8_t *)&dev->priv->vdi_chunk_header;
    dev->priv->receive_len = sizeof(dev->priv->vdi_chunk_header);
    dev->priv->message_receive_len = 0;
    dev->priv->current_read_buf.reset();


    agent_msg_filter_init(&dev->priv->read_filter, reds->config->agent_copypaste,
                          reds->config->agent_file_xfer,
                          reds_use_client_monitors_config(reds), TRUE);


    dev->priv->write_filter.result = AGENT_MSG_FILTER_DISCARD;
    dev->priv->write_filter.discard_all = TRUE;
    dev->priv->client_agent_started = false;
    dev->priv->agent_supports_graphics_device_info = false;


    dev->priv->agent_attached = FALSE;
    dev->stop();
    dev->reset();
    dev->reset_dev_instance(NULL);

    sif = spice_char_device_get_interface(reds->vdagent);
    if (sif->state) {
        sif->state(reds->vdagent, 0);
    }
}
