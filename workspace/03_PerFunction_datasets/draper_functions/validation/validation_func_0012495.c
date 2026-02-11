GWEN_Mutex_Lock(GWEN_MUTEX *mtx) {
  int rv;

  rv=pthread_mutex_lock(&(mtx->mutex));
  if (rv) {
    DBG_INFO(GWEN_LOGDOMAIN,
	     "pthread_mutex_lock: %s", strerror(rv));
    return GWEN_ERROR_IO;
  }

  return 0;
}
