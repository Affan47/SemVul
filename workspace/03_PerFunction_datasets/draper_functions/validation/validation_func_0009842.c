_gnutls_x509_gtime2utcTime (time_t gtime, char *str_time, int str_time_size)
{
  size_t ret;
  struct tm _tm;

  if (!gmtime_r (&gtime, &_tm))
    {
      gnutls_assert ();
      return GNUTLS_E_INTERNAL_ERROR;
    }

  ret = strftime (str_time, str_time_size, "%y%m%d%H%M%SZ", &_tm);
  if (!ret)
    {
      gnutls_assert ();
      return GNUTLS_E_SHORT_MEMORY_BUFFER;
    }


  return 0;

}
