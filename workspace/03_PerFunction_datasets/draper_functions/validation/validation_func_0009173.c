_cache_load( netsnmp_cache *cache )
{
    int ret = -1;


    if (cache->valid &&
        (! (cache->flags & NETSNMP_CACHE_DONT_FREE_BEFORE_LOAD)))
        _cache_free(cache);

    if ( cache->load_cache)
        ret = cache->load_cache(cache, cache->magic);
    if (ret < 0) {
        DEBUGMSGT(("helper:cache_handler", " load failed (%d)\n", ret));
        cache->valid = 0;
        return ret;
    }
    cache->valid = 1;
    cache->expired = 0;


    if ((!cache_outstanding_valid) &&
        (! (cache->flags & NETSNMP_CACHE_DONT_FREE_EXPIRED))) {
        snmp_alarm_register(CACHE_RELEASE_FREQUENCY,
                            0, release_cached_resources, NULL);
        cache_outstanding_valid = 1;
    }
    if (cache->timestamp)
        atime_setMarker(cache->timestamp);
    else
        cache->timestamp = atime_newMarker();
    DEBUGMSGT(("helper:cache_handler", " loaded (%d)\n", cache->timeout));

    return ret;
}
