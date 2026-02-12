static void reds_update_agent_properties(RedsState *reds)
{
    if (!reds->agent_dev || reds->config == NULL) {
        return;
    }

    reds->agent_dev->priv->write_filter.copy_paste_enabled = reds->config->agent_copypaste;
    reds->agent_dev->priv->read_filter.copy_paste_enabled = reds->config->agent_copypaste;

    reds->agent_dev->priv->write_filter.file_xfer_enabled = reds->config->agent_file_xfer;
    reds->agent_dev->priv->read_filter.file_xfer_enabled = reds->config->agent_file_xfer;
}
