gnutls_x509_crq_get_basic_constraints (gnutls_x509_crq_t crq,
                                       unsigned int *critical,
                                       int *ca, int *pathlen)
{
  int result;
  int tmp_ca;
  opaque buf[256];
  size_t buf_size = sizeof (buf);

  if (crq == NULL)
    {
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  result = gnutls_x509_crq_get_extension_by_oid (crq, "2.5.29.19", 0,
                                                 buf, &buf_size, critical);
  if (result < 0)
    {
      gnutls_assert ();
      return result;
    }

  result =
    _gnutls_x509_ext_extract_basicConstraints (&tmp_ca,
                                               pathlen, buf, buf_size);
  if (ca)
    *ca = tmp_ca;

  if (result < 0)
    {
      gnutls_assert ();
      return result;
    }

  return tmp_ca;
}
