st_to_st2 (gnutls_retr2_st * st2, gnutls_retr_st * st)
{
  st2->cert_type = st->type;
  if (st->type == GNUTLS_CRT_OPENPGP)
    {
      st2->key_type = GNUTLS_PRIVKEY_OPENPGP;
    }
  else
    {
      st2->key_type = GNUTLS_PRIVKEY_X509;
    }
  st2->ncerts = st->ncerts;
  st2->deinit_all = st->deinit_all;

  switch (st2->cert_type)
    {
    case GNUTLS_CRT_OPENPGP:
      st2->cert.pgp = st->cert.pgp;
      st2->key.pgp = st->key.pgp;
      break;
    case GNUTLS_CRT_X509:
      st2->cert.x509 = st->cert.x509;
      st2->key.x509 = st->key.x509;
      break;
    default:
      return;
    }

}
