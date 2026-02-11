eina_chained_mempool_shutdown(void *data)
{
   Chained_Mempool *mp;

   mp = (Chained_Mempool *)data;

   while (mp->first)
     {
        Chained_Pool *p = (Chained_Pool *)mp->first;

#ifdef DEBUG
        if (p->usage > 0)
           INF("Bad news we are destroying not an empty mempool [%s]\n",
               mp->name);

#endif

        mp->first = eina_inlist_remove(mp->first, mp->first);
        mp->root = eina_rbtree_inline_remove(mp->root, EINA_RBTREE_GET(p),
                                             _eina_chained_mp_pool_cmp, NULL);
        _eina_chained_mp_pool_free(p);
     }

#ifdef DEBUG
   if (mp->root)
     INF("Bad news, list of pool and rbtree are out of sync for %p !", mp);
#endif

#ifndef NVALGRIND
   VALGRIND_DESTROY_MEMPOOL(mp);
#endif

   eina_lock_free(&mp->mutex);

#ifdef EFL_DEBUG_THREADS
   assert(pthread_equal(mp->self, pthread_self()));
#endif

   free(mp);
}
