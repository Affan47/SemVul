static int final_alpn(SSL *s, unsigned int context, int sent)
{
    if (!s->server && !sent && s->session->ext.alpn_selected != NULL)
            s->ext.early_data_ok = 0;

    if (!s->server || !SSL_IS_TLS13(s))
        return 1;


    return tls_handle_alpn(s);
}
