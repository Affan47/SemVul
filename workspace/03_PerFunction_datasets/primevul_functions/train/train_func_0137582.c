void InstanceKlass::mask_for(const methodHandle& method, int bci,
  InterpreterOopMap* entry_for) {


  OopMapCache* oop_map_cache = Atomic::load_acquire(&_oop_map_cache);
  if (oop_map_cache == NULL) {
    MutexLocker x(OopMapCacheAlloc_lock);

    if ((oop_map_cache = _oop_map_cache) == NULL) {
      oop_map_cache = new OopMapCache();

      Atomic::release_store(&_oop_map_cache, oop_map_cache);
    }
  }

  oop_map_cache->lookup(method, bci, entry_for);
}
