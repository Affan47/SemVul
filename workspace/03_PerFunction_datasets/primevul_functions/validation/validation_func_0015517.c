HttpStateData::httpBuildRequestHeader(HttpRequest * request,
                                      StoreEntry * entry,
                                      const AccessLogEntryPointer &al,
                                      HttpHeader * hdr_out,
                                      const Http::StateFlags &flags)
{

#define BBUF_SZ (MAX_URL+32)
    LOCAL_ARRAY(char, bbuf, BBUF_SZ);
    LOCAL_ARRAY(char, ntoabuf, MAX_IPSTRLEN);
    const HttpHeader *hdr_in = &request->header;
    const HttpHeaderEntry *e = NULL;
    HttpHeaderPos pos = HttpHeaderInitPos;
    assert (hdr_out->owner == hoRequest);


    if (request->lastmod > -1)
        hdr_out->putTime(Http::HdrType::IF_MODIFIED_SINCE, request->lastmod);


    if (request->etag.size() > 0) {
        hdr_out->addEntry(new HttpHeaderEntry(Http::HdrType::IF_NONE_MATCH, NULL,
                                              request->etag.termedBuf()));
    }

    bool we_do_ranges = decideIfWeDoRanges (request);

    String strConnection (hdr_in->getList(Http::HdrType::CONNECTION));

    while ((e = hdr_in->getEntry(&pos)))
        copyOneHeaderFromClientsideRequestToUpstreamRequest(e, strConnection, request, hdr_out, we_do_ranges, flags);


    if (!we_do_ranges && request->multipartRangeRequest()) {

        request->flags.cachable = false;

        request->ignoreRange("want to request the whole object");
        request->flags.isRanged = false;
    }

    hdr_out->addVia(request->http_ver, hdr_in);

    if (request->flags.accelerated) {

        String strSurrogate(hdr_in->getList(Http::HdrType::SURROGATE_CAPABILITY));
#if USE_SQUID_ESI
        snprintf(bbuf, BBUF_SZ, "%s=\"Surrogate/1.0 ESI/1.0\"", Config.Accel.surrogate_id);
#else
        snprintf(bbuf, BBUF_SZ, "%s=\"Surrogate/1.0\"", Config.Accel.surrogate_id);
#endif
        strListAdd(&strSurrogate, bbuf, ',');
        hdr_out->putStr(Http::HdrType::SURROGATE_CAPABILITY, strSurrogate.termedBuf());
    }


    if (strcmp(opt_forwarded_for, "delete") != 0) {

        String strFwd = hdr_in->getList(Http::HdrType::X_FORWARDED_FOR);


        if (!strFwd.canGrowBy(strFwd.size())) {


            strFwd = "error";

            static int warnedCount = 0;
            if (warnedCount++ < 100) {
                const SBuf url(entry ? SBuf(entry->url()) : request->effectiveRequestUri());
                debugs(11, DBG_IMPORTANT, "Warning: likely forwarding loop with " << url);
            }
        }

        if (strcmp(opt_forwarded_for, "on") == 0) {

            if ( request->client_addr.isNoAddr() )
                strListAdd(&strFwd, "unknown", ',');
            else
                strListAdd(&strFwd, request->client_addr.toStr(ntoabuf, MAX_IPSTRLEN), ',');
        } else if (strcmp(opt_forwarded_for, "off") == 0) {

            strListAdd(&strFwd, "unknown", ',');
        } else if (strcmp(opt_forwarded_for, "transparent") == 0) {

        } else if (strcmp(opt_forwarded_for, "truncate") == 0) {

            if ( request->client_addr.isNoAddr() )
                strFwd = "unknown";
            else
                strFwd = request->client_addr.toStr(ntoabuf, MAX_IPSTRLEN);
        }
        if (strFwd.size() > 0)
            hdr_out->putStr(Http::HdrType::X_FORWARDED_FOR, strFwd.termedBuf());
    }


    if (!hdr_out->has(Http::HdrType::HOST)) {
        if (request->peer_domain) {
            hdr_out->putStr(Http::HdrType::HOST, request->peer_domain);
        } else {
            SBuf authority = request->url.authority();
            hdr_out->putStr(Http::HdrType::HOST, authority.c_str());
        }
    }


    if (!hdr_out->has(Http::HdrType::AUTHORIZATION)) {
        if (!request->flags.proxying && !request->url.userInfo().isEmpty()) {
            static char result[base64_encode_len(MAX_URL*2)];
            struct base64_encode_ctx ctx;
            base64_encode_init(&ctx);
            size_t blen = base64_encode_update(&ctx, result, request->url.userInfo().length(), reinterpret_cast<const uint8_t*>(request->url.userInfo().rawContent()));
            blen += base64_encode_final(&ctx, result+blen);
            result[blen] = '\0';
            if (blen)
                httpHeaderPutStrf(hdr_out, Http::HdrType::AUTHORIZATION, "Basic %.*s", (int)blen, result);
        }
    }


    httpFixupAuthentication(request, hdr_in, hdr_out, flags);


    {
        HttpHdrCc *cc = hdr_in->getCc();

        if (!cc)
            cc = new HttpHdrCc();

#if 0

        if (request->flags.nocache)
            EBIT_SET(cc->mask, HttpHdrCcType::CC_NO_CACHE);
#endif


        if (!cc->hasMaxAge() && !cc->hasNoCache()) {

            SBuf tmp(request->effectiveRequestUri());
            cc->maxAge(getMaxAge(entry ? entry->url() : tmp.c_str()));
        }


        if (flags.only_if_cached)
            cc->onlyIfCached(true);

        hdr_out->putCc(cc);

        delete cc;
    }


    hdr_out->putStr(Http::HdrType::CONNECTION, flags.keepalive ? "keep-alive" : "close");


    if (flags.front_end_https) {
        if (flags.front_end_https == 1 || request->url.getScheme() == AnyP::PROTO_HTTPS)
            hdr_out->putStr(Http::HdrType::FRONT_END_HTTPS, "On");
    }

    if (flags.chunked_request) {


        hdr_out->putStr(Http::HdrType::TRANSFER_ENCODING, "chunked");
    }


    httpHdrMangleList(hdr_out, request, al, ROR_REQUEST);

    strConnection.clean();
}
