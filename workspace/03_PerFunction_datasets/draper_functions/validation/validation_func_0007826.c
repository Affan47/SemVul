startCaching() {
    cacheStateLock.lock();


    if (cacheState == CACHE_STATE_ACTIVE) {
        cacheStateLock.unlock();
        stopCaching();
    }
    else {
        cacheStateLock.unlock();
    }


    threadSend(START);


    while ( mCache->size() - mCache->free() < preCacheSize
            && mCache->size() - mCache->free() < f_length_byte) {
        usleep(1000);
    }
}
