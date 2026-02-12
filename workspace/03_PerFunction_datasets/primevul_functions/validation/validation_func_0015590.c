varyEvaluateMatch(StoreEntry * entry, HttpRequest * request)
{
    SBuf vary(request->vary_headers);
    int has_vary = entry->getReply()->header.has(Http::HdrType::VARY);
#if X_ACCELERATOR_VARY

    has_vary |=
        entry->getReply()->header.has(Http::HdrType::HDR_X_ACCELERATOR_VARY);
#endif

    if (!has_vary || entry->mem_obj->vary_headers.isEmpty()) {
        if (!vary.isEmpty()) {

            debugs(33, DBG_IMPORTANT, "varyEvaluateMatch: Oops. Not a Vary object on second attempt, '" <<
                   entry->mem_obj->urlXXX() << "' '" << vary << "'");
            request->vary_headers.clear();
            return VARY_CANCEL;
        }

        if (!has_vary) {

            return VARY_NONE;
        }


        vary = httpMakeVaryMark(request, entry->getReply());

        if (!vary.isEmpty()) {
            request->vary_headers = vary;
            return VARY_OTHER;
        } else {


            return VARY_CANCEL;
        }
    } else {
        if (vary.isEmpty()) {
            vary = httpMakeVaryMark(request, entry->getReply());

            if (!vary.isEmpty())
                request->vary_headers = vary;
        }

        if (vary.isEmpty()) {


            return VARY_CANCEL;
        } else if (vary.cmp(entry->mem_obj->vary_headers) == 0) {
            return VARY_MATCH;
        } else {


            debugs(33, DBG_IMPORTANT, "varyEvaluateMatch: Oops. Not a Vary match on second attempt, '" <<
                   entry->mem_obj->urlXXX() << "' '" << vary << "'");
            return VARY_CANCEL;
        }
    }
}
