static const char *set_realm(cmd_parms *cmd, void *config, const char *realm)
{
    digest_config_rec *conf = (digest_config_rec *) config;
#ifdef AP_DEBUG
    int i;


    for (i = 0; i < SECRET_LEN; i++) {
        if (secret[i] != 0)
            break;
    }
    ap_assert(i < SECRET_LEN);
#endif


    conf->realm = realm;


    apr_sha1_init(&conf->nonce_ctx);
    apr_sha1_update_binary(&conf->nonce_ctx, secret, SECRET_LEN);
    apr_sha1_update_binary(&conf->nonce_ctx, (const unsigned char *) realm,
                           strlen(realm));

    return DECLINE_CMD;
}
