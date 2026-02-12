uint8_t *reds_get_agent_data_buffer(RedsState *reds, MainChannelClient *mcc, size_t size)
{
    RedCharDeviceVDIPort *dev = reds->agent_dev.get();
    RedClient *client;

    if (!dev->priv->client_agent_started) {


        return (uint8_t*) g_malloc(size);
    }

    spice_assert(dev->priv->recv_from_client_buf == NULL);
    client = mcc->get_client();
    dev->priv->recv_from_client_buf =
        dev->write_buffer_get_client((RedCharDeviceClientOpaque *)client,
                                     size + sizeof(VDIChunkHeader));


    if (!dev->priv->recv_from_client_buf) {
        return NULL;
    }
    dev->priv->recv_from_client_buf_pushed = FALSE;
    return dev->priv->recv_from_client_buf->buf + sizeof(VDIChunkHeader);
}
