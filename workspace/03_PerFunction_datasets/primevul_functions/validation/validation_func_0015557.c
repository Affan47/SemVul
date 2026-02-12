copyOneHeaderFromClientsideRequestToUpstreamRequest(const HttpHeaderEntry *e, const String strConnection, const HttpRequest * request, HttpHeader * hdr_out, const int we_do_ranges, const Http::StateFlags &flags)
{
    debugs(11, 5, "httpBuildRequestHeader: " << e->name << ": " << e->value );

    switch (e->id) {


    case Http::HdrType::PROXY_AUTHORIZATION:


        if (!flags.originpeer && flags.proxying && request->peer_login &&
                (strcmp(request->peer_login, "PASS") == 0 ||
                 strcmp(request->peer_login, "PROXYPASS") == 0 ||
                 strcmp(request->peer_login, "PASSTHRU") == 0)) {
            hdr_out->addEntry(e->clone());
        }
        break;


    case Http::HdrType::CONNECTION:
    case Http::HdrType::TE:
    case Http::HdrType::KEEP_ALIVE:
    case Http::HdrType::PROXY_AUTHENTICATE:
    case Http::HdrType::TRAILER:
    case Http::HdrType::UPGRADE:
    case Http::HdrType::TRANSFER_ENCODING:
        break;


    case Http::HdrType::AUTHORIZATION:


        if (!flags.originpeer) {
            hdr_out->addEntry(e->clone());
        } else {


            if (request->peer_login &&
                    (strcmp(request->peer_login, "PASS") == 0 ||
                     strcmp(request->peer_login, "PASSTHRU") == 0 ||
                     strcmp(request->peer_login, "PROXYPASS") == 0)) {
                hdr_out->addEntry(e->clone());
            }
        }

        break;

    case Http::HdrType::HOST:


        if (request->peer_domain)
            hdr_out->putStr(Http::HdrType::HOST, request->peer_domain);
        else if (request->flags.redirected && !Config.onoff.redir_rewrites_host)
            hdr_out->addEntry(e->clone());
        else {
            SBuf authority = request->url.authority();
            hdr_out->putStr(Http::HdrType::HOST, authority.c_str());
        }

        break;

    case Http::HdrType::IF_MODIFIED_SINCE:


        if (hdr_out->has(Http::HdrType::IF_MODIFIED_SINCE))
            break;
        else if (Config.onoff.cache_miss_revalidate || !request->flags.cachable || request->flags.auth)
            hdr_out->addEntry(e->clone());
        break;

    case Http::HdrType::IF_NONE_MATCH:


        if (hdr_out->hasListMember(Http::HdrType::IF_MATCH, "*", ',') || Config.onoff.cache_miss_revalidate || !request->flags.cachable || request->flags.auth)
            hdr_out->addEntry(e->clone());
        break;

    case Http::HdrType::MAX_FORWARDS:


        if (request->method == Http::METHOD_TRACE || request->method == Http::METHOD_OPTIONS) {
            const int64_t hops = e->getInt64();

            if (hops > 0)
                hdr_out->putInt64(Http::HdrType::MAX_FORWARDS, hops - 1);
        }

        break;

    case Http::HdrType::VIA:


        if (!Config.onoff.via)
            hdr_out->addEntry(e->clone());

        break;

    case Http::HdrType::RANGE:

    case Http::HdrType::IF_RANGE:

    case Http::HdrType::REQUEST_RANGE:


        if (!we_do_ranges)
            hdr_out->addEntry(e->clone());

        break;

    case Http::HdrType::PROXY_CONNECTION:
        break;

    case Http::HdrType::CONTENT_LENGTH:


        if (!flags.chunked_request)
            hdr_out->addEntry(e->clone());
        break;

    case Http::HdrType::X_FORWARDED_FOR:

    case Http::HdrType::CACHE_CONTROL:


        break;

    case Http::HdrType::FRONT_END_HTTPS:


        if (!flags.front_end_https)
            hdr_out->addEntry(e->clone());

        break;

    default:


        if (strConnection.size()>0 && strListIsMember(&strConnection, e->name.termedBuf(), ',')) {
            debugs(11, 2, "'" << e->name << "' header cropped by Connection: definition");
            return;
        }

        hdr_out->addEntry(e->clone());
    }
}
