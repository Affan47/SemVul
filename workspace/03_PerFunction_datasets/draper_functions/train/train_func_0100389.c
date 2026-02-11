cleanUnreachable()
{

#if (GNASH_GC_DEBUG > 1)
    log_debug("GC: sweep scan started");
#endif

    size_t deleted = 0;

    for (ResList::iterator i = _resList.begin(), e = _resList.end(); i != e;) {
        const GcResource* res = *i;
        if (!res->isReachable()) {

#if GNASH_GC_DEBUG > 1
            log_debug("GC: recycling object %p (%s)", res, typeName(*res));
#endif
            ++deleted;
            delete res;
            i = _resList.erase(i);
        }
        else {
            res->clearReachable();
            ++i;
        }
    }

    _resListSize -= deleted;

#ifdef GNASH_GC_DEBUG
    log_debug("GC: recycled %d unreachable resources - %d left",
            deleted, _resListSize);
#endif

    return deleted;
}
