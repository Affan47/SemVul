HttpStateData::processReplyHeader()
{


    Ctx ctx = ctx_enter(entry->mem_obj->urlXXX());

    debugs(11, 3, "processReplyHeader: key '" << entry->getMD5Text() << "'");

    assert(!flags.headers_parsed);

    if (!inBuf.length()) {
        ctx_exit(ctx);
        return;
    }


    {
        if (hp == NULL)
            hp = new Http1::ResponseParser;

        bool parsedOk = hp->parse(inBuf);


        inBuf = hp->remaining();

        if (hp->needsMoreData()) {
            if (eof) {


                inBuf.append("\r\n\r\n", 4);

                parsedOk = hp->parse(inBuf);

                inBuf = hp->remaining();
            } else {
                debugs(33, 5, "Incomplete response, waiting for end of response headers");
                ctx_exit(ctx);
                return;
            }
        }

        if (!parsedOk) {


            debugs(11, 3, "Non-HTTP-compliant header:\n---------\n" << inBuf << "\n----------");
            flags.headers_parsed = true;
            HttpReply *newrep = new HttpReply;
            newrep->sline.set(Http::ProtocolVersion(), hp->parseStatusCode);
            setVirginReply(newrep);
            ctx_exit(ctx);
            return;
        }
    }


    debugs(11, 2, "HTTP Server " << serverConnection);
    debugs(11, 2, "HTTP Server RESPONSE:\n---------\n" <<
           hp->messageProtocol() << " " << hp->messageStatus() << " " << hp->reasonPhrase() << "\n" <<
           hp->mimeHeader() <<
           "----------");


    payloadSeen = inBuf.length();

    HttpReply *newrep = new HttpReply;


    newrep->sline.set(Http::ProtocolVersion(1,1), hp->messageStatus() );
    newrep->sline.protocol = newrep->sline.version.protocol = hp->messageProtocol().protocol;
    newrep->sline.version.major = hp->messageProtocol().major;
    newrep->sline.version.minor = hp->messageProtocol().minor;


    if (!newrep->parseHeader(*hp)) {

        newrep->sline.set(Http::ProtocolVersion(), Http::scInvalidHeader);
        newrep->sline.version.protocol = hp->messageProtocol().protocol;
        newrep->sline.version.major = hp->messageProtocol().major;
        newrep->sline.version.minor = hp->messageProtocol().minor;
        debugs(11, 2, "error parsing response headers mime block");
    }


    hp = NULL;

    newrep->sources |= request->url.getScheme() == AnyP::PROTO_HTTPS ? HttpMsg::srcHttps : HttpMsg::srcHttp;

    newrep->removeStaleWarnings();

    if (newrep->sline.protocol == AnyP::PROTO_HTTP && newrep->sline.status() >= 100 && newrep->sline.status() < 200) {
        handle1xx(newrep);
        ctx_exit(ctx);
        return;
    }

    flags.chunked = false;
    if (newrep->sline.protocol == AnyP::PROTO_HTTP && newrep->header.chunked()) {
        flags.chunked = true;
        httpChunkDecoder = new Http1::TeChunkedParser;
    }

    if (!peerSupportsConnectionPinning())
        request->flags.connectionAuthDisabled = true;

    HttpReply *vrep = setVirginReply(newrep);
    flags.headers_parsed = true;

    keepaliveAccounting(vrep);

    checkDateSkew(vrep);

    processSurrogateControl (vrep);

    request->hier.peer_reply_status = newrep->sline.status();

    ctx_exit(ctx);
}
