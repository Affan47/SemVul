_gnutls_x509_verify_certificate (const gnutls_x509_crt_t * certificate_list,
				 int clist_size,
				 const gnutls_x509_crt_t * trusted_cas,
				 int tcas_size,
				 const gnutls_x509_crl_t * CRLs,
				 int crls_size, unsigned int flags)
{
  int i = 0, ret;
  unsigned int status = 0, output;

  if (clist_size > 1)
    {


      if (gnutls_x509_crt_check_issuer (certificate_list[clist_size - 1],
				    certificate_list[clist_size - 1]) > 0)
	{
	  clist_size--;
	}
    }


  if (clist_size > 1 && !(flags & GNUTLS_VERIFY_DO_NOT_ALLOW_SAME))
    {
      for (i = 1; i < clist_size; i++)
	{
	  int j;

	  for (j = 0; j < tcas_size; j++)
	    {
	      if (check_if_same_cert (certificate_list[i],
				      trusted_cas[j]) == 0)
		{
		  clist_size = i;
		  break;
		}
	    }

	}
    }


  ret = _gnutls_verify_certificate2 (certificate_list[clist_size - 1],
				     trusted_cas, tcas_size, flags, &output);
  if (ret == 0)
    {


      gnutls_assert ();
      status |= output;
      status |= GNUTLS_CERT_INVALID;
      return status;
    }


#ifdef ENABLE_PKI
  for (i = 0; i < clist_size; i++)
    {
      ret = gnutls_x509_crt_check_revocation (certificate_list[i],
					      CRLs, crls_size);
      if (ret == 1)
	{
	  status |= GNUTLS_CERT_REVOKED;
	  status |= GNUTLS_CERT_INVALID;
	  return status;
	}
    }
#endif


  for (i = clist_size - 1; i > 0; i--)
    {
      if (i - 1 < 0)
	break;


      if (!(flags & GNUTLS_VERIFY_ALLOW_ANY_X509_V1_CA_CRT))
	flags &= ~(GNUTLS_VERIFY_ALLOW_X509_V1_CA_CRT);
      if ((ret =
	   _gnutls_verify_certificate2 (certificate_list[i - 1],
					&certificate_list[i], 1, flags,
					NULL)) == 0)
	{
	  status |= GNUTLS_CERT_INVALID;
	  return status;
	}
    }

  return 0;
}
