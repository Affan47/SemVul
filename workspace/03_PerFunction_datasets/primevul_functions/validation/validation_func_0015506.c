ConnStateData::switchToHttps(HttpRequest *request, Ssl::BumpMode bumpServerMode)
{
    assert(!switchedToHttps_);


    const auto insideConnectTunnel = receivedFirstByte_;
    debugs(33, 5, (insideConnectTunnel ? "post-CONNECT " : "raw TLS ") << clientConnection);

    tlsConnectHostOrIp = request->url.hostOrIp();
    tlsConnectPort = request->url.port();
    resetSslCommonName(request->url.host());


    flags.readMore = true;


    transferProtocol.protocol = AnyP::PROTO_HTTPS;


    if (bumpServerMode == Ssl::bumpServerFirst && !sslServerBump) {
        request->flags.sslPeek = true;
        sslServerBump = new Ssl::ServerBump(request);
    } else if (bumpServerMode == Ssl::bumpPeek || bumpServerMode == Ssl::bumpStare) {
        request->flags.sslPeek = true;
        sslServerBump = new Ssl::ServerBump(request, NULL, bumpServerMode);
    }


    typedef CommCbMemFunT<ConnStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(33, 5,
                                      TimeoutDialer, this, ConnStateData::requestTimeout);
    commSetConnTimeout(clientConnection, Config.Timeout.request_start_timeout, timeoutCall);


    receivedFirstByte_ = false;

    parsingTlsHandshake = true;


    if (insideConnectTunnel)
        preservingClientData_ = shouldPreserveClientData();

    readSomeData();
}
