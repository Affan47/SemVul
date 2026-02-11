flush(bool force)
{
    init();

    if ( force || totalSizeOfLRU > maxSize + maxSize/4) {
        for ( int i = MAX_LRU_LISTS-1; i >= 0 && totalSizeOfLRU > maxSize; --i )
            while ( totalSizeOfLRU > maxSize && m_LRULists[i].m_tail )
                removeCacheEntry( m_LRULists[i].m_tail );

#ifdef CACHE_DEBUG
        statistics();
#endif
    }

    QMutableLinkedListIterator<CachedObject*> it(*freeList);
    while ( it.hasNext() ) {
        CachedObject* p = it.next();
        if ( p->canDelete() ) {
            it.remove();
            delete p;
        }
    }
}
