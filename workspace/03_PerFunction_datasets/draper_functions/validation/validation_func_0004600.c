MmapHook(const void* result,
                               const void* start, size_t size,
                               int prot, int flags,
                               int fd, off_t offset) {


  RAW_VLOG(10, "MMap = 0x%" PRIxPTR " of %" PRIuS " at %" PRIu64 " "
              "prot %d flags %d fd %d offs %" PRId64,
              reinterpret_cast<uintptr_t>(result), size,
              reinterpret_cast<uint64>(start), prot, flags, fd,
              static_cast<int64>(offset));
  if (result != reinterpret_cast<void*>(MAP_FAILED)  &&  size != 0) {
    RecordRegionAddition(result, size);
  }
}
