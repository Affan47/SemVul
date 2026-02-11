ssl_util_thr_lock(int mode, int type, const char *file, int line) {
  apr_status_t status;

  if (type < lock_num_locks) {
    if (mode & CRYPTO_LOCK) {
      if ((status = apr_thread_mutex_lock(lock_cs[type])) != APR_SUCCESS) {
	fprintf(stderr, "Fatal error could not lock");
	exit(status);
      }
    }
    else {
      if ((status = apr_thread_mutex_unlock(lock_cs[type])) != APR_SUCCESS) {
	fprintf(stderr, "Fatal error could not unlock");
	exit(status);
      }
    }
  }
}
