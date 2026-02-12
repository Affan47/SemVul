RedVDIReadBuf::~RedVDIReadBuf()
{
    dev->priv->num_read_buf--;


    if (dev->priv->agent_attached) {
       dev->wakeup();
    }
}
