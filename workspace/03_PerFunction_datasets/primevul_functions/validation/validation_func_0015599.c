HttpStateData::HttpStateData(FwdState *theFwdState) :
    AsyncJob("HttpStateData"),
    Client(theFwdState),
    lastChunk(0),
    httpChunkDecoder(NULL),
    payloadSeen(0),
    payloadTruncated(0),
    sawDateGoBack(false)
{
    debugs(11,5,HERE << "HttpStateData " << this << " created");
    ignoreCacheControl = false;
    surrogateNoStore = false;
    serverConnection = fwd->serverConnection();

    if (fwd->serverConnection() != NULL)
        _peer = cbdataReference(fwd->serverConnection()->getPeer());

    if (_peer) {
        request->flags.proxying = true;


        if (_peer->options.proxy_only)
            entry->releaseRequest(true);

#if USE_DELAY_POOLS
        entry->setNoDelay(_peer->options.no_delay);
#endif
    }


    typedef CommCbMemFunT<HttpStateData, CommCloseCbParams> Dialer;
    closeHandler = JobCallback(9, 5, Dialer, this, HttpStateData::httpStateConnClosed);
    comm_add_close_handler(serverConnection->fd, closeHandler);
}
