HeaderLookupTable_t::initCache()
{
    idCache.resize(TOTAL_KEYWORDS);
    for (int j = MIN_HASH_VALUE; j <= MAX_HASH_VALUE; ++j) {
        if (HttpHeaderDefinitionsTable[j].name[0] != '\0') {
            idCache[static_cast<int>(HttpHeaderDefinitionsTable[j].id)] =
                & HttpHeaderDefinitionsTable[j];
        }
    }

    for (auto e : idCache) {
        assert(e->name);
    }
}
