static void network_init_gcrypt (void)
{
  gcry_error_t err;


  if (gcry_control (GCRYCTL_ANY_INITIALIZATION_P))
    return;


# if GCRYPT_VERSION_NUMBER < 0x010600
  err = gcry_control (GCRYCTL_SET_THREAD_CBS, &gcry_threads_pthread);
  if (err)
  {
    ERROR ("network plugin: gcry_control (GCRYCTL_SET_THREAD_CBS) failed: %s", gcry_strerror (err));
    abort ();
  }
# endif

  gcry_check_version (NULL);

  err = gcry_control (GCRYCTL_INIT_SECMEM, 32768);
  if (err)
  {
    ERROR ("network plugin: gcry_control (GCRYCTL_SET_THREAD_CBS) failed: %s", gcry_strerror (err));
    abort ();
  }

  gcry_control (GCRYCTL_INITIALIZATION_FINISHED);
}
