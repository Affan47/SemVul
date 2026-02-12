ConnStateData::ConnStateData(const MasterXaction::Pointer &xact) :
    AsyncJob("ConnStateData"),
    Server(xact),
    bodyParser(nullptr),
#if USE_OPENSSL
    sslBumpMode(Ssl::bumpEnd),
    tlsParser(Security::HandshakeParser::fromClient),
#endif
    needProxyProtocolHeader_(false),
#if USE_OPENSSL
    switchedToHttps_(false),
    parsingTlsHandshake(false),
    parsedBumpedRequestCount(0),
    tlsConnectPort(0),
    sslServerBump(NULL),
    signAlgorithm(Ssl::algSignTrusted),
#endif
    stoppedSending_(NULL),
    stoppedReceiving_(NULL)
{
    flags.readMore = true;
    flags.swanSang = false;

    pinning.host = NULL;
    pinning.port = -1;
    pinning.pinned = false;
    pinning.auth = false;
    pinning.zeroReply = false;
    pinning.peer = NULL;


    log_addr = xact->tcpClient->remote;
    log_addr.applyMask(Config.Addrs.client_netmask);


    registerRunner();
}
