_gnutls_cert_get_issuer_dn (gnutls_cert * cert, gnutls_datum_t * odn)
{
  ASN1_TYPE dn;
  int len, result;
  int start, end;

  if ((result = asn1_create_element
       (_gnutls_get_pkix (), "PKIX1.Certificate", &dn)) != ASN1_SUCCESS)
    {
      gnutls_assert ();
      return _gnutls_asn2err (result);
    }

  result = asn1_der_decoding (&dn, cert->raw.data, cert->raw.size, NULL);
  if (result != ASN1_SUCCESS)
    {

      gnutls_assert ();
      asn1_delete_structure (&dn);
      return _gnutls_asn2err (result);
    }

  result = asn1_der_decoding_startEnd (dn, cert->raw.data, cert->raw.size,
                                       "tbsCertificate.issuer", &start, &end);

  if (result != ASN1_SUCCESS)
    {

      gnutls_assert ();
      asn1_delete_structure (&dn);
      return _gnutls_asn2err (result);
    }
  asn1_delete_structure (&dn);

  len = end - start + 1;

  odn->size = len;
  odn->data = &cert->raw.data[start];

  return 0;
}
