disable_optional_stuff (gnutls_x509_crt_t cert)
{

  asn1_write_value (cert->cert, "tbsCertificate.issuerUniqueID", NULL, 0);

  asn1_write_value (cert->cert, "tbsCertificate.subjectUniqueID", NULL, 0);

  if (cert->use_extensions == 0)
    {
      _gnutls_x509_log ("Disabling X.509 extensions.\n");
      asn1_write_value (cert->cert, "tbsCertificate.extensions", NULL, 0);
    }

  return;
}
