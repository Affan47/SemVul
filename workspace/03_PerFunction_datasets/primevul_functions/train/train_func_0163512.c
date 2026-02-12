item *do_item_alloc(char *key, const size_t nkey, const unsigned int flags,
                    const rel_time_t exptime, const int nbytes) {
    int i;
    uint8_t nsuffix;
    item *it = NULL;
    char suffix[40];

    if (nbytes < 2)
        return 0;

    size_t ntotal = item_make_header(nkey + 1, flags, nbytes, suffix, &nsuffix);
    if (settings.use_cas) {
        ntotal += sizeof(uint64_t);
    }

    unsigned int id = slabs_clsid(ntotal);
    if (id == 0)
        return 0;


    for (i = 0; i < 10; i++) {
        uint64_t total_bytes;

        if (!settings.lru_segmented) {
            lru_pull_tail(id, COLD_LRU, 0, 0, 0);
        }
        it = slabs_alloc(ntotal, id, &total_bytes, 0);

        if (settings.temp_lru)
            total_bytes -= temp_lru_size(id);

        if (it == NULL) {
            if (settings.lru_segmented) {
                if (lru_pull_tail(id, COLD_LRU, total_bytes, LRU_PULL_EVICT, 0) <= 0) {
                    lru_pull_tail(id, HOT_LRU, total_bytes, 0, 0);
                }
            } else {
                if (lru_pull_tail(id, COLD_LRU, 0, LRU_PULL_EVICT, 0) <= 0)
                    break;
            }
        } else {
            break;
        }
    }

    if (i > 0) {
        pthread_mutex_lock(&lru_locks[id]);
        itemstats[id].direct_reclaims += i;
        pthread_mutex_unlock(&lru_locks[id]);
    }

    if (it == NULL) {
        pthread_mutex_lock(&lru_locks[id]);
        itemstats[id].outofmemory++;
        pthread_mutex_unlock(&lru_locks[id]);
        return NULL;
    }

    assert(it->slabs_clsid == 0);


    it->next = it->prev = 0;


    if (settings.lru_segmented) {
        if (settings.temp_lru &&
                exptime - current_time <= settings.temporary_ttl) {
            id |= TEMP_LRU;
        } else {
            id |= HOT_LRU;
        }
    } else {

        id |= COLD_LRU;
    }
    it->slabs_clsid = id;

    DEBUG_REFCNT(it, '*');
    it->it_flags |= settings.use_cas ? ITEM_CAS : 0;
    it->nkey = nkey;
    it->nbytes = nbytes;
    memcpy(ITEM_key(it), key, nkey);
    it->exptime = exptime;
    if (settings.inline_ascii_response) {
        memcpy(ITEM_suffix(it), suffix, (size_t)nsuffix);
    } else {
        memcpy(ITEM_suffix(it), &flags, sizeof(flags));
    }
    it->nsuffix = nsuffix;


    if (it->it_flags & ITEM_CHUNKED) {
        item_chunk *chunk = (item_chunk *) ITEM_data(it);

        chunk->next = (item_chunk *) it->h_next;
        chunk->prev = 0;
        chunk->head = it;

        chunk->next->prev = chunk;
        chunk->size = chunk->next->size - ((char *)chunk - (char *)it);
        chunk->used = 0;
        assert(chunk->size > 0);
    }
    it->h_next = 0;

    return it;
}
