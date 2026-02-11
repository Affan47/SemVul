pwd_put_values (SRP_PWD_ENTRY * entry, char *str)
{
  char *p;
  int len, ret;
  opaque *verifier;
  size_t verifier_size;
  int indx;

  p = strrchr (str, ':');
  if (p == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_SRP_PWD_PARSING_ERROR;
    }

  *p = '\0';
  p++;

  indx = atoi (p);
  if (indx == 0)
    {
      gnutls_assert ();
      return GNUTLS_E_SRP_PWD_PARSING_ERROR;
    }


  p = strrchr (str, ':');
  if (p == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_SRP_PWD_PARSING_ERROR;
    }

  *p = '\0';
  p++;

  len = strlen (p);

  entry->salt.size = _gnutls_sbase64_decode (p, len, &entry->salt.data);

  if (entry->salt.size <= 0)
    {
      gnutls_assert ();
      return GNUTLS_E_SRP_PWD_PARSING_ERROR;
    }


  p = strrchr (str, ':');
  if (p == NULL)
    {
      _gnutls_free_datum (&entry->salt);
      return GNUTLS_E_SRP_PWD_PARSING_ERROR;
    }

  *p = '\0';
  p++;

  len = strlen (p);
  ret = _gnutls_sbase64_decode (p, len, &verifier);
  if (ret <= 0)
    {
      gnutls_assert ();
      _gnutls_free_datum (&entry->salt);
      return GNUTLS_E_SRP_PWD_PARSING_ERROR;
    }

  verifier_size = ret;
  entry->v.data = verifier;
  entry->v.size = verifier_size;


  *p = '\0';

  entry->username = gnutls_strdup (str);
  if (entry->username == NULL)
    {
      _gnutls_free_datum (&entry->salt);
      _gnutls_free_datum (&entry->v);
      gnutls_assert ();
      return GNUTLS_E_MEMORY_ERROR;
    }

  return indx;
}
