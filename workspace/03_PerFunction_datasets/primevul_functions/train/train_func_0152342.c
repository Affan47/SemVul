_dbus_atomic_set_nonzero (DBusAtomic *atomic)
{
#if DBUS_USE_SYNC

  __sync_or_and_fetch (&atomic->value, 1);
#else
  pthread_mutex_lock (&atomic_mutex);
  atomic->value = 1;
  pthread_mutex_unlock (&atomic_mutex);
#endif
}
