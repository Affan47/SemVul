ConnStateData::clientParseRequests()
{
    bool parsed_req = false;

    debugs(33, 5, HERE << clientConnection << ": attempting to parse");


    while (!inBuf.isEmpty() && !bodyPipe && flags.readMore) {


        if (pinning.pinned && !pinning.readHandler) {
            debugs(33, 3, clientConnection << " waits for busy " << pinning.serverConnection);
            break;
        }


        if (concurrentRequestQueueFilled())
            break;


        if (needProxyProtocolHeader_) {
            if (!parseProxyProtocolHeader())
                break;


            whenClientIpKnown();


            assert(!preservingClientData_);
        }

        if (Http::StreamPointer context = parseOneRequest()) {
            debugs(33, 5, clientConnection << ": done parsing a request");

            AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "clientLifetimeTimeout",
                                             CommTimeoutCbPtrFun(clientLifetimeTimeout, context->http));
            commSetConnTimeout(clientConnection, Config.Timeout.lifetime, timeoutCall);

            context->registerWithConn();

#if USE_OPENSSL
            if (switchedToHttps())
                parsedBumpedRequestCount++;
#endif

            processParsedRequest(context);

            parsed_req = true;

            if (context->mayUseConnection()) {
                debugs(33, 3, HERE << "Not parsing new requests, as this request may need the connection");
                break;
            }
        } else {
            debugs(33, 5, clientConnection << ": not enough request data: " <<
                   inBuf.length() << " < " << Config.maxRequestHeaderSize);
            Must(inBuf.length() < Config.maxRequestHeaderSize);
            break;
        }
    }


    return parsed_req;
}
