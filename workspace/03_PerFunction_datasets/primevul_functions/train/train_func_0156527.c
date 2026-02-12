MagickExport void *AcquireCriticalMemory(const size_t size)
{
  void
    *memory;


  memory=AcquireMagickMemory(size);
  if (memory == (void *) NULL)
    ThrowFatalException(ResourceLimitFatalError,"MemoryAllocationFailed");
  return(memory);
}
