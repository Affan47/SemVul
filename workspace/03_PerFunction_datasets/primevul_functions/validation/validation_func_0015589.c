HttpStateData::haveParsedReplyHeaders()
{
    Client::haveParsedReplyHeaders();

    Ctx ctx = ctx_enter(entry->mem_obj->urlXXX());
    HttpReply *rep = finalReply();
    const Http::StatusCode statusCode = rep->sline.status();

    entry->timestampsSet();


    debugs(11, 3, "HTTP CODE: " << statusCode);

    if (StoreEntry *oldEntry = findPreviouslyCachedEntry(entry)) {
        oldEntry->lock("HttpStateData::haveParsedReplyHeaders");
        sawDateGoBack = rep->olderThan(oldEntry->getReply());
        oldEntry->unlock("HttpStateData::haveParsedReplyHeaders");
    }

    if (neighbors_do_private_keys && !sawDateGoBack)
        httpMaybeRemovePublic(entry, rep->sline.status());

    bool varyFailure = false;
    if (rep->header.has(Http::HdrType::VARY)
#if X_ACCELERATOR_VARY
            || rep->header.has(Http::HdrType::HDR_X_ACCELERATOR_VARY)
#endif
       ) {
        const SBuf vary(httpMakeVaryMark(request, rep));

        if (vary.isEmpty()) {


            entry->makePrivate(false);
            if (fwd->reforwardableStatus(rep->sline.status()))
                EBIT_SET(entry->flags, ENTRY_FWD_HDR_WAIT);
            varyFailure = true;
        } else {
            entry->mem_obj->vary_headers = vary;


            static const SBuf asterisk("*");
            if (vary == asterisk)
                EBIT_SET(entry->flags, ENTRY_REVALIDATE_ALWAYS);
        }
    }

    if (!varyFailure) {


        if (fwd->reforwardableStatus(rep->sline.status()))
            EBIT_SET(entry->flags, ENTRY_FWD_HDR_WAIT);

        ReuseDecision decision(entry, statusCode);

        switch (reusableReply(decision)) {

        case ReuseDecision::reuseNot:
            entry->makePrivate(false);
            break;

        case ReuseDecision::cachePositively:
            if (!entry->makePublic()) {
                decision.make(ReuseDecision::doNotCacheButShare, "public key creation error");
                entry->makePrivate(true);
            }
            break;

        case ReuseDecision::cacheNegatively:
            if (!entry->cacheNegatively()) {
                decision.make(ReuseDecision::doNotCacheButShare, "public key creation error");
                entry->makePrivate(true);
            }
            break;

        case ReuseDecision::doNotCacheButShare:
            entry->makePrivate(true);
            break;

        default:
            assert(0);
            break;
        }
        debugs(11, 3, "decided: " << decision);
    }

    if (!ignoreCacheControl) {
        if (rep->cache_control) {


            const bool ccMustRevalidate = (rep->cache_control->hasProxyRevalidate() || rep->cache_control->hasMustRevalidate());


            const bool ccNoCacheNoParams = rep->cache_control->hasNoCacheWithoutParameters();


            const bool ccSMaxAge = rep->cache_control->hasSMaxAge();


            const bool ccPrivate = rep->cache_control->hasPrivate();

            if (ccNoCacheNoParams || ccPrivate)
                EBIT_SET(entry->flags, ENTRY_REVALIDATE_ALWAYS);
            else if (ccMustRevalidate || ccSMaxAge)
                EBIT_SET(entry->flags, ENTRY_REVALIDATE_STALE);
        }
#if USE_HTTP_VIOLATIONS
        else {


            if (rep->header.has(Http::HdrType::PRAGMA) &&
                    rep->header.hasListMember(Http::HdrType::PRAGMA,"no-cache",','))
                EBIT_SET(entry->flags, ENTRY_REVALIDATE_ALWAYS);
        }
#endif
    }

#if HEADERS_LOG
    headersLog(1, 0, request->method, rep);

#endif

    ctx_exit(ctx);
}
