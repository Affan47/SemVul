ConnStateData::startPeekAndSplice()
{

    assert(sslServerBump);
    Http::StreamPointer context = pipeline.front();
    ClientHttpRequest *http = context ? context->http : nullptr;

    if (sslServerBump->step == Ssl::bumpStep1) {
        sslServerBump->step = Ssl::bumpStep2;


        ACLFilledChecklist *acl_checklist = new ACLFilledChecklist(Config.accessList.ssl_bump, sslServerBump->request.getRaw(), nullptr);
        acl_checklist->al = http ? http->al : nullptr;


        acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpNone));
        acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpClientFirst));
        acl_checklist->banAction(allow_t(ACCESS_ALLOWED, Ssl::bumpServerFirst));
        const char *log_uri = http ? http->log_uri : nullptr;
        acl_checklist->syncAle(sslServerBump->request.getRaw(), log_uri);
        acl_checklist->nonBlockingCheck(httpsSslBumpStep2AccessCheckDone, this);
        return;
    }


    Security::ContextPointer unConfiguredCTX(Ssl::createSSLContext(port->secure.signingCa.cert, port->secure.signingCa.pkey, port->secure));
    fd_table[clientConnection->fd].dynamicTlsContext = unConfiguredCTX;

    if (!httpsCreate(this, unConfiguredCTX))
        return;

    switchedToHttps_ = true;

    auto ssl = fd_table[clientConnection->fd].ssl.get();
    BIO *b = SSL_get_rbio(ssl);
    Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(BIO_get_data(b));
    bio->setReadBufData(inBuf);
    bio->hold(true);


    if (tlsAttemptHandshake(this, nullptr) < 0) {
        debugs(83, 2, "TLS handshake failed.");
        HttpRequest::Pointer request(http ? http->request : nullptr);
        if (!clientTunnelOnError(this, context, request, HttpRequestMethod(), ERR_SECURE_ACCEPT_FAIL))
            clientConnection->close();
        return;
    }


    inBuf.clear();

    debugs(83, 5, "Peek and splice at step2 done. Start forwarding the request!!! ");
    FwdState::Start(clientConnection, sslServerBump->entry, sslServerBump->request.getRaw(), http ? http->al : NULL);
}
