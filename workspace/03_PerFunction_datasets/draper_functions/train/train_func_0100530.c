_openssl_dynlock_lock_cb(int mode, struct CRYPTO_dynlock_value *v,
                         const char *file, int line)
{
  (void)file;
  (void)line;
  if (mode & CRYPTO_LOCK)
    tor_mutex_acquire(v->lock);
  else
    tor_mutex_release(v->lock);
}
