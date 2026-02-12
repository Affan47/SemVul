vnc_display_setup_auth(int *auth,
                       int *subauth,
                       QCryptoTLSCreds *tlscreds,
                       bool password,
                       bool sasl,
                       bool websocket,
                       Error **errp)
{


    if (websocket || !tlscreds) {
        if (password) {
            VNC_DEBUG("Initializing VNC server with password auth\n");
            *auth = VNC_AUTH_VNC;
        } else if (sasl) {
            VNC_DEBUG("Initializing VNC server with SASL auth\n");
            *auth = VNC_AUTH_SASL;
        } else {
            VNC_DEBUG("Initializing VNC server with no auth\n");
            *auth = VNC_AUTH_NONE;
        }
        *subauth = VNC_AUTH_INVALID;
    } else {
        bool is_x509 = object_dynamic_cast(OBJECT(tlscreds),
                                           TYPE_QCRYPTO_TLS_CREDS_X509) != NULL;
        bool is_anon = object_dynamic_cast(OBJECT(tlscreds),
                                           TYPE_QCRYPTO_TLS_CREDS_ANON) != NULL;

        if (!is_x509 && !is_anon) {
            error_setg(errp,
                       "Unsupported TLS cred type %s",
                       object_get_typename(OBJECT(tlscreds)));
            return -1;
        }
        *auth = VNC_AUTH_VENCRYPT;
        if (password) {
            if (is_x509) {
                VNC_DEBUG("Initializing VNC server with x509 password auth\n");
                *subauth = VNC_AUTH_VENCRYPT_X509VNC;
            } else {
                VNC_DEBUG("Initializing VNC server with TLS password auth\n");
                *subauth = VNC_AUTH_VENCRYPT_TLSVNC;
            }

        } else if (sasl) {
            if (is_x509) {
                VNC_DEBUG("Initializing VNC server with x509 SASL auth\n");
                *subauth = VNC_AUTH_VENCRYPT_X509SASL;
            } else {
                VNC_DEBUG("Initializing VNC server with TLS SASL auth\n");
                *subauth = VNC_AUTH_VENCRYPT_TLSSASL;
            }
        } else {
            if (is_x509) {
                VNC_DEBUG("Initializing VNC server with x509 no auth\n");
                *subauth = VNC_AUTH_VENCRYPT_X509NONE;
            } else {
                VNC_DEBUG("Initializing VNC server with TLS no auth\n");
                *subauth = VNC_AUTH_VENCRYPT_TLSNONE;
            }
        }
    }
    return 0;
}
