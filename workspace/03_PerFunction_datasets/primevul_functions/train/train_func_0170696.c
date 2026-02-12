static int final_maxfragmentlen(SSL *s, unsigned int context, int sent)
{


    if (s->server && s->hit && USE_MAX_FRAGMENT_LENGTH_EXT(s->session)
            && !sent ) {
        SSLfatal(s, SSL_AD_MISSING_EXTENSION, SSL_F_FINAL_MAXFRAGMENTLEN,
                 SSL_R_BAD_EXTENSION);
        return 0;
    }


    if (s->session && USE_MAX_FRAGMENT_LENGTH_EXT(s->session)
            && s->max_send_fragment < GET_MAX_FRAGMENT_LENGTH(s->session))

        if (!ssl3_setup_buffers(s)) {

            return 0;
        }

    return 1;
}
