void Socket::cleanSsl() {
    if (ssl != NULL) {
        SSL_free(ssl);
        ssl = NULL;
    }
    if (ctx != NULL ) {
        SSL_CTX_free(ctx);
        ctx = NULL;
    }
    issslserver = false;
    isssl = false;
}
