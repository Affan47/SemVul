HttpStateData::handleMoreRequestBodyAvailable()
{
    if (eof || !Comm::IsConnOpen(serverConnection)) {


        debugs(11, DBG_IMPORTANT, HERE << "Transaction aborted while reading HTTP body");
        return;
    }

    assert(requestBodySource != NULL);

    if (requestBodySource->buf().hasContent()) {


        if (flags.headers_parsed && !flags.abuse_detected) {
            flags.abuse_detected = true;
            debugs(11, DBG_IMPORTANT, "http handleMoreRequestBodyAvailable: Likely proxy abuse detected '" << request->client_addr << "' -> '" << entry->url() << "'" );

            if (virginReply()->sline.status() == Http::scInvalidHeader) {
                closeServer();
                mustStop("HttpStateData::handleMoreRequestBodyAvailable");
                return;
            }
        }
    }

    HttpStateData::handleMoreRequestBodyAvailable();
}
