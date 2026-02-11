__socket_disconnect (rpc_transport_t *this)
{
        socket_private_t *priv = NULL;
        int               ret = -1;

        GF_VALIDATE_OR_GOTO ("socket", this, out);
        GF_VALIDATE_OR_GOTO ("socket", this->private, out);

        priv = this->private;

        if (priv->sock != -1) {
                priv->connected = -1;
                ret = shutdown (priv->sock, SHUT_RDWR);
                if (ret) {


                        gf_log (this->name, GF_LOG_DEBUG,
                                "shutdown() returned %d. %s",
                                ret, strerror (errno));
                }
        }

out:
        return ret;
}
