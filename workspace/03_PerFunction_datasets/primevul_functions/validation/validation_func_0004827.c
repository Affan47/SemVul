void UntrustedCacheMalloc::Free(void *buffer) {
  if (is_destroyed_ || GetSwitchedHeapNext()) {
    primitives::TrustedPrimitives::UntrustedLocalFree(buffer);
    return;
  }
  LockGuard spin_lock(&lock_);


  if (busy_buffers_.find(buffer) == busy_buffers_.end()) {
    PushToFreeList(buffer);
    return;
  }
  busy_buffers_.erase(buffer);
  buffer_pool_.push(buffer);
}
