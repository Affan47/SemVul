syncnodes(void *targ){
  if(g_runmode == RM_RDONLY) return NULL;
  if(pthread_mutex_lock(&g_backlock) != 0) return NULL;
  if(!rwlock_lock(g_runlock, FALSE)){
    log_print(LL_ERROR, "locking failed");
    pthread_mutex_unlock(&g_backlock);
    return NULL;
  }
  if(!rwlock_lock(g_mgrlock, TRUE)){
    rwlock_unlock(g_runlock);
    pthread_mutex_unlock(&g_backlock);
    log_print(LL_ERROR, "locking failed");
    return NULL;
  }
  umgr_sync(g_umgr);
  nmgr_sync(g_nmgr, TRUE);
  if(!dpsync(g_metadb)) log_print(LL_ERROR, "synchronizing the meda database failed");
  if(!rwlock_unlock(g_mgrlock)) log_print(LL_ERROR, "unlocking failed");
  if(!rwlock_unlock(g_runlock)) log_print(LL_ERROR, "unlocking failed");
  if(pthread_mutex_unlock(&g_backlock) != 0) log_print(LL_ERROR, "unlocking failed");
  return NULL;
}
