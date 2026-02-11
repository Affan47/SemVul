pfs_malloc(size_t size, myf flags)
{
  DBUG_ASSERT(! pfs_initialized);
  DBUG_ASSERT(size > 0);

  void *ptr= malloc(size);
  if (likely(ptr != NULL))
    pfs_allocated_memory+= size;
  if (likely((ptr != NULL) && (flags & MY_ZEROFILL)))
    memset(ptr, 0, size);
  return ptr;
}
