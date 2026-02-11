do_free_with_callback(void* ptr, void (*invalid_free_fn)(void*)) {
  ThreadCache* heap = NULL;
  if (LIKELY(ThreadCache::IsFastPathAllowed())) {
    heap = ThreadCache::GetCacheWhichMustBePresent();
    do_free_helper(ptr, invalid_free_fn, heap, true);
  } else {
    heap = ThreadCache::GetCacheIfPresent();
    do_free_helper(ptr, invalid_free_fn, heap, false);
  }
}
