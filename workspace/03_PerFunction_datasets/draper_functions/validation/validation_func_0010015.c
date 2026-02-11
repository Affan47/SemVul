Alloc(size_t size, size_t *actual_size,
                                 size_t alignment) {
  for (int i = 0; i < kMaxAllocators; i++) {
    if (!failed_[i] && allocs_[i] != NULL) {
      void* result = allocs_[i]->Alloc(size, actual_size, alignment);
      if (result != NULL) {
        return result;
      }
      failed_[i] = true;
    }
  }


  for (int i = 0; i < kMaxAllocators; i++) {
    failed_[i] = false;
  }
  return NULL;
}
