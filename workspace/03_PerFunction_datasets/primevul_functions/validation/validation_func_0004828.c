UntrustedCacheMalloc::~UntrustedCacheMalloc() {
  while (!buffer_pool_.empty()) {
    PushToFreeList(buffer_pool_.top());
    buffer_pool_.pop();
  }


  if (free_list_->count > 0) {
    primitives::DeAllocateUntrustedBuffers(free_list_->buffers.get(),
                                           free_list_->count);
  }
  is_destroyed_ = true;
}
