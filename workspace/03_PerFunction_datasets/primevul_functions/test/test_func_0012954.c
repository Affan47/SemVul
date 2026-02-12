RedCharDeviceVDIPort::~RedCharDeviceVDIPort()
{

    reset();
    priv->current_read_buf.reset();
    g_free(priv->mig_data);
    spice_extra_assert(priv->num_read_buf == 0);
}
