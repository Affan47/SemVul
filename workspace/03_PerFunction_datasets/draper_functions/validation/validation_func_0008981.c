fusion_dbg_shcalloc( FusionSHMPoolShared *pool,
                     const char *file, int line,
                     const char *func, size_t __nmemb, size_t __size)
{
     D_MAGIC_ASSERT( pool, FusionSHMPoolShared );
     D_ASSERT( __nmemb > 0 );
     D_ASSERT( __size > 0 );

     if (pool->debug)
          return direct_calloc( file, line, func, __nmemb, __size );

     return calloc( __nmemb, __size );
}
