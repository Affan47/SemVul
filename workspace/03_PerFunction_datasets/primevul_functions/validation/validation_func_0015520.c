ConnStateData::getSslContextDone(Security::ContextPointer &ctx)
{
    if (port->secure.generateHostCertificates && !ctx) {
        debugs(33, 2, "Failed to generate TLS context for " << tlsConnectHostOrIp);
    }


    if (!ctx) {
        if (!port->secure.staticContext) {
            debugs(83, DBG_IMPORTANT, "Closing " << clientConnection->remote << " as lacking TLS context");
            clientConnection->close();
            return;
        } else {
            debugs(33, 5, "Using static TLS context.");
            ctx = port->secure.staticContext;
        }
    }

    if (!httpsCreate(this, ctx))
        return;


    typedef CommCbMemFunT<ConnStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall = JobCallback(33, 5, TimeoutDialer,
                                     this, ConnStateData::requestTimeout);
    commSetConnTimeout(clientConnection, Config.Timeout.request, timeoutCall);

    switchedToHttps_ = true;

    auto ssl = fd_table[clientConnection->fd].ssl.get();
    BIO *b = SSL_get_rbio(ssl);
    Ssl::ClientBio *bio = static_cast<Ssl::ClientBio *>(BIO_get_data(b));
    bio->setReadBufData(inBuf);
    inBuf.clear();
    clientNegotiateSSL(clientConnection->fd, this);
}
