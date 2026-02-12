void *UntrustedCacheMalloc::Malloc(size_t size) {


  if (is_destroyed_ || (size > kPoolEntrySize) || GetSwitchedHeapNext()) {
    return primitives::TrustedPrimitives::UntrustedLocalAlloc(size);
  }
  return GetBuffer();
}
