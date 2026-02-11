deleteThread (OSThread_t id) {
    threadLock.lock() ;
    ThreadMap::iterator t = threads.find (id) ;
    if (t != threads.end()) {
        delete t->second ;
    }
    threads.erase (id) ;
    numThreads-- ;
    threadLock.unlock() ;
}
