init_dh(SERVICE_OPTIONS *section) {
    DH *dh=NULL;

    s_log(LOG_DEBUG, "DH initialization");
#ifdef HAVE_OSSL_ENGINE_H
    if(!section->engine)
#endif
        dh=read_dh(section->cert);
    if(!dh)
        dh=get_dh2048();
    if(!dh) {
        s_log(LOG_NOTICE, "DH initialization failed");
        return 1;
    }
    SSL_CTX_set_tmp_dh(section->ctx, dh);
    s_log(LOG_DEBUG, "DH initialized with %d-bit key", 8*DH_size(dh));
    DH_free(dh);
    return 0;
}
