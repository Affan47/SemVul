HttpStateData::continueAfterParsingHeader()
{
    if (flags.handling1xx) {
        debugs(11, 5, HERE << "wait for 1xx handling");
        Must(!flags.headers_parsed);
        return false;
    }

    if (!flags.headers_parsed && !eof) {
        debugs(11, 9, "needs more at " << inBuf.length());
        flags.do_next_read = true;


        maybeReadVirginBody();
        return false;
    }


    err_type error = ERR_NONE;

    if (flags.headers_parsed) {

        if (HttpReply *vrep = virginReply()) {
            const Http::StatusCode s = vrep->sline.status();
            const AnyP::ProtocolVersion &v = vrep->sline.version;
            if (s == Http::scInvalidHeader && v != Http::ProtocolVersion(0,9)) {
                debugs(11, DBG_IMPORTANT, "WARNING: HTTP: Invalid Response: Bad header encountered from " << entry->url() << " AKA " << request->url);
                error = ERR_INVALID_RESP;
            } else if (s == Http::scHeaderTooLarge) {
                fwd->dontRetry(true);
                error = ERR_TOO_BIG;
            } else if (vrep->header.conflictingContentLength()) {
                fwd->dontRetry(true);
                error = ERR_INVALID_RESP;
            } else if (vrep->header.unsupportedTe()) {
                fwd->dontRetry(true);
                error = ERR_INVALID_RESP;
            } else {
                return true;
            }
        } else {

            debugs(11, DBG_IMPORTANT, "WARNING: HTTP: Invalid Response: No reply at all for " << entry->url() << " AKA " << request->url);
            error = ERR_INVALID_RESP;
        }
    } else {
        assert(eof);
        if (inBuf.length()) {
            error = ERR_INVALID_RESP;
            debugs(11, DBG_IMPORTANT, "WARNING: HTTP: Invalid Response: Headers did not parse at all for " << entry->url() << " AKA " << request->url);
        } else {
            error = ERR_ZERO_SIZE_OBJECT;
            debugs(11, (request->flags.accelerated?DBG_IMPORTANT:2), "WARNING: HTTP: Invalid Response: No object data received for " << entry->url() << " AKA " << request->url);
        }
    }

    assert(error != ERR_NONE);
    entry->reset();
    fwd->fail(new ErrorState(error, Http::scBadGateway, fwd->request));
    flags.do_next_read = false;
    closeServer();
    mustStop("HttpStateData::continueAfterParsingHeader");
    return false;
}
