int Socket::startSslServer(X509 *x, EVP_PKEY *privKey, std::string &set_cipher_list)
{

    if (isssl) {
        stopSsl();
    }


    ssl = NULL;


#if OPENSSL_VERSION_NUMBER < 0x10100000L
    ctx = SSL_CTX_new(SSLv23_server_method());
#else
    ctx = SSL_CTX_new(TLS_server_method());
#endif

    if (ctx == NULL) {
#ifdef NETDEBUG

        std::cout << thread_id << "Error ssl context is null (check that openssl has been inited)" << std::endl;
#endif
        return -1;
    }


    if (SSL_CTX_set_timeout(ctx, 130l) < 1) {
        cleanSsl();
        return -1;
    }


    if (SSL_CTX_use_certificate(ctx, x) < 1) {
#ifdef NETDEBUG

        std::cout << thread_id << "Error using certificate" << std::endl;
#endif
        cleanSsl();
        return -1;
    }

    if (set_cipher_list.length() > 0)
        SSL_CTX_set_cipher_list(ctx, set_cipher_list.c_str());


    if (SSL_CTX_use_PrivateKey(ctx, privKey) < 1) {
#ifdef NETDEBUG

        std::cout << thread_id << "Error using private key" << std::endl;
#endif
        cleanSsl();
        return -1;
    }


    ERR_clear_error();
    ssl = SSL_new(ctx);
    SSL_set_options(ssl, SSL_OP_ALL);
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    SSL_set_accept_state(ssl);

    ERR_clear_error();
    if(!SSL_set_fd(ssl, this->getFD())) {
#ifdef NETDEBUG
        std::cout << thread_id << "Error setting ssl fd connection" << std::endl;
#endif
        log_ssl_errors("ssl_set_fd failed to client %s", "");
        cleanSsl();
        return -1;
    };


    ERR_clear_error();
    if (SSL_accept(ssl) < 0) {
#ifdef NETDEBUG

        std::cout << thread_id << "Error accepting ssl connection" << std::endl;
#endif
        log_ssl_errors("ssl_accept failed to client %s", "");
        cleanSsl();
        return -1;
    }

    ERR_clear_error();
    if (SSL_do_handshake(ssl) < 0) {
#ifdef NETDEBUG

        std::cout << thread_id << "Error doing ssl handshake" << std::endl;
#endif
        log_ssl_errors("ssl_handshake failed to client %s", "");
        cleanSsl();
        return -1;
    }
    isssl = true;
    issslserver = true;
    return 0;
}
