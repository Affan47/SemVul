ssl_servername_cb(SSL *ssl, int *ad, void *arg)
{
    VALUE ary, ssl_obj, ret_obj;
    void *ptr;
    int state = 0;
    const char *servername = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name);

    if (!servername)
        return SSL_TLSEXT_ERR_OK;

    if ((ptr = SSL_get_ex_data(ssl, ossl_ssl_ex_ptr_idx)) == NULL)
    	return SSL_TLSEXT_ERR_ALERT_FATAL;
    ssl_obj = (VALUE)ptr;
    ary = rb_ary_new2(2);
    rb_ary_push(ary, ssl_obj);
    rb_ary_push(ary, rb_str_new2(servername));

    ret_obj = rb_protect((VALUE(*)_((VALUE)))ossl_call_servername_cb, ary, &state);
    if (state) {
        rb_ivar_set(ssl_obj, ID_callback_state, INT2NUM(state));
        return SSL_TLSEXT_ERR_ALERT_FATAL;
    }

    return SSL_TLSEXT_ERR_OK;
}
