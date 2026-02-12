static inline void *AcquireCriticalMemory(const size_t size)
{
  register void
    *memory;


  memory=AcquireMagickMemory(size);
  if (memory == (void *) NULL)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
  return(memory);
}
