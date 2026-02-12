HttpStateData::reusableReply(HttpStateData::ReuseDecision &decision)
{
    HttpReply const *rep = finalReply();
    HttpHeader const *hdr = &rep->header;
    const char *v;
#if USE_HTTP_VIOLATIONS

    const RefreshPattern *R = NULL;


#define REFRESH_OVERRIDE(flag) \
    ((R = (R ? R : refreshLimits(entry->mem_obj->storeId()))) , \
    (R && R->flags.flag))
#else
#define REFRESH_OVERRIDE(flag) 0
#endif

    if (EBIT_TEST(entry->flags, RELEASE_REQUEST))
        return decision.make(ReuseDecision::doNotCacheButShare, "the entry has been released");


    if (sawDateGoBack)
        return decision.make(ReuseDecision::reuseNot, "the response has an older date header");


    if (surrogateNoStore)
        return decision.make(ReuseDecision::reuseNot, "Surrogate-Control:no-store");


    if (!ignoreCacheControl) {


        if (request && request->cache_control && request->cache_control->hasNoStore() &&
                !REFRESH_OVERRIDE(ignore_no_store))
            return decision.make(ReuseDecision::reuseNot,
                                 "client request Cache-Control:no-store");


        if (rep->cache_control && rep->cache_control->hasNoCacheWithParameters()) {


            return decision.make(ReuseDecision::reuseNot,
                                 "server reply Cache-Control:no-cache has parameters");
        }


        if (rep->cache_control && rep->cache_control->hasNoStore() &&
                !REFRESH_OVERRIDE(ignore_no_store))
            return decision.make(ReuseDecision::reuseNot,
                                 "server reply Cache-Control:no-store");


        if (rep->cache_control &&
                rep->cache_control->hasPrivate() &&
                !REFRESH_OVERRIDE(ignore_private)) {


            return decision.make(ReuseDecision::reuseNot,
                                 "server reply Cache-Control:private");
        }
    }


    if (request && (request->flags.auth || request->flags.authSent)) {
        if (!rep->cache_control)
            return decision.make(ReuseDecision::reuseNot,
                                 "authenticated and server reply missing Cache-Control");

        if (ignoreCacheControl)
            return decision.make(ReuseDecision::reuseNot,
                                 "authenticated and ignoring Cache-Control");

        bool mayStore = false;

        if (rep->cache_control->hasPublic()) {
            debugs(22, 3, HERE << "Authenticated but server reply Cache-Control:public");
            mayStore = true;


        } else if (rep->cache_control->hasMustRevalidate()) {
            debugs(22, 3, HERE << "Authenticated but server reply Cache-Control:must-revalidate");
            mayStore = true;

#if USE_HTTP_VIOLATIONS


        } else if (rep->cache_control->hasNoCacheWithoutParameters()) {
            debugs(22, 3, HERE << "Authenticated but server reply Cache-Control:no-cache (equivalent to must-revalidate)");
            mayStore = true;
#endif


        } else if (rep->cache_control->hasSMaxAge()) {
            debugs(22, 3, HERE << "Authenticated but server reply Cache-Control:s-maxage");
            mayStore = true;
        }

        if (!mayStore)
            return decision.make(ReuseDecision::reuseNot, "authenticated transaction");


    }


    if ((v = hdr->getStr(Http::HdrType::CONTENT_TYPE)))
        if (!strncasecmp(v, "multipart/x-mixed-replace", 25))
            return decision.make(ReuseDecision::reuseNot, "Content-Type:multipart/x-mixed-replace");


    static const char *shareableError = "shareable error status code";
    static const char *nonShareableError = "non-shareable error status code";
    ReuseDecision::Answers statusAnswer = ReuseDecision::reuseNot;
    const char *statusReason = nonShareableError;

    switch (rep->sline.status()) {


    case Http::scOkay:

    case Http::scNonAuthoritativeInformation:

    case Http::scMultipleChoices:

    case Http::scMovedPermanently:
    case Http::scPermanentRedirect:

    case Http::scGone:


        if (refreshIsCachable(entry) || REFRESH_OVERRIDE(store_stale))
            decision.make(ReuseDecision::cachePositively, "refresh check returned cacheable");
        else
            decision.make(ReuseDecision::doNotCacheButShare, "refresh check returned non-cacheable");
        break;


    case Http::scFound:
    case Http::scTemporaryRedirect:
        if (rep->date <= 0)
            decision.make(ReuseDecision::doNotCacheButShare, "Date is missing/invalid");
        else if (rep->expires > rep->date)
            decision.make(ReuseDecision::cachePositively, "Expires > Date");
        else
            decision.make(ReuseDecision::doNotCacheButShare, "Expires <= Date");
        break;


    case Http::scNoContent:
    case Http::scUseProxy:
    case Http::scForbidden:
    case Http::scNotFound:
    case Http::scMethodNotAllowed:
    case Http::scUriTooLong:
    case Http::scInternalServerError:
    case Http::scNotImplemented:
    case Http::scBadGateway:
    case Http::scServiceUnavailable:
    case Http::scGatewayTimeout:
    case Http::scMisdirectedRequest:
        statusAnswer = ReuseDecision::doNotCacheButShare;
        statusReason = shareableError;


    case Http::scBadRequest:
#if USE_HTTP_VIOLATIONS
        if (Config.negativeTtl > 0)
            decision.make(ReuseDecision::cacheNegatively, "Config.negativeTtl > 0");
        else
#endif
            decision.make(statusAnswer, statusReason);
        break;


    case Http::scSeeOther:
    case Http::scNotModified:
    case Http::scUnauthorized:
    case Http::scProxyAuthenticationRequired:
    case Http::scPaymentRequired:
    case Http::scInsufficientStorage:

        decision.make(ReuseDecision::doNotCacheButShare, shareableError);
        break;

    case Http::scPartialContent:
    case Http::scNotAcceptable:
    case Http::scRequestTimeout:
    case Http::scConflict:
    case Http::scLengthRequired:
    case Http::scPreconditionFailed:
    case Http::scPayloadTooLarge:
    case Http::scUnsupportedMediaType:
    case Http::scUnprocessableEntity:
    case Http::scLocked:
    case Http::scFailedDependency:
    case Http::scRequestedRangeNotSatisfied:
    case Http::scExpectationFailed:
    case Http::scInvalidHeader:
    case Http::scHeaderTooLarge:
        decision.make(ReuseDecision::reuseNot, nonShareableError);
        break;

    default:

        decision.make(ReuseDecision::reuseNot, "unknown status code");
        break;
    }

    return decision.answer;
}
