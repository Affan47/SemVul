UntrustedCacheMalloc::UntrustedCacheMalloc() : lock_(true) {
  if (is_destroyed_) {
    return;
  }


  free_list_ = absl::make_unique<FreeList>();
  free_list_->buffers.reset(reinterpret_cast<void **>(
      primitives::TrustedPrimitives::UntrustedLocalAlloc(sizeof(void *) *
                                                         kFreeListCapacity)));
  free_list_->count = 0;
}
