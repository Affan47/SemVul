ConnStateData::parseTlsHandshake()
{
    Must(parsingTlsHandshake);

    assert(!inBuf.isEmpty());
    receivedFirstByte();
    fd_note(clientConnection->fd, "Parsing TLS handshake");

    bool unsupportedProtocol = false;
    try {
        if (!tlsParser.parseHello(inBuf)) {

            readSomeData();
            return;
        }
    }
    catch (const std::exception &ex) {
        debugs(83, 2, "error on FD " << clientConnection->fd << ": " << ex.what());
        unsupportedProtocol = true;
    }

    parsingTlsHandshake = false;


    preservedClientData = inBuf;


    Security::TlsDetails::Pointer const &details = tlsParser.details;
    clientConnection->tlsNegotiations()->retrieveParsedInfo(details);
    if (details && !details->serverName.isEmpty()) {
        resetSslCommonName(details->serverName.c_str());
        tlsClientSni_ = details->serverName;
    }


    Comm::ResetSelect(clientConnection->fd);

    if (unsupportedProtocol) {
        Http::StreamPointer context = pipeline.front();
        Must(context && context->http);
        HttpRequest::Pointer request = context->http->request;
        debugs(83, 5, "Got something other than TLS Client Hello. Cannot SslBump.");
        sslBumpMode = Ssl::bumpSplice;
        context->http->al->ssl.bumpMode = Ssl::bumpSplice;
        if (!clientTunnelOnError(this, context, request, HttpRequestMethod(), ERR_PROTOCOL_UNKNOWN))
            clientConnection->close();
        return;
    }

    if (!sslServerBump || sslServerBump->act.step1 == Ssl::bumpClientFirst) {
        getSslContextStart();
        return;
    } else if (sslServerBump->act.step1 == Ssl::bumpServerFirst) {

        FwdState::fwdStart(clientConnection, sslServerBump->entry, sslServerBump->request.getRaw());
    } else {
        Must(sslServerBump->act.step1 == Ssl::bumpPeek || sslServerBump->act.step1 == Ssl::bumpStare);
        startPeekAndSplice();
    }
}
