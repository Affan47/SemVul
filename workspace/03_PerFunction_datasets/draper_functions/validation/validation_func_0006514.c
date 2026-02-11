pooldeinit(struct memorypool *pool)
#else
void pooldeinit(pool)
struct memorypool *pool;
#endif

{
  while (pool->firstblock != (void **) NULL) {
    pool->nowblock = (void **) *(pool->firstblock);
    trifree((void *) pool->firstblock);
    pool->firstblock = pool->nowblock;
  }
}
