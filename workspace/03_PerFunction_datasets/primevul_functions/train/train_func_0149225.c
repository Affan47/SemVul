build_cert_sequence (const unsigned char *buffer, size_t buflen,
                     const unsigned char *sha1hash, const char *keyidstr,
                     size_t *r_length)
{
  size_t len[8], needed, n;
  unsigned char *p, *certseq;
  size_t certseqlen;
  int i;

  assert (strlen (keyidstr) == 8);


  needed = compute_tag_length (buflen);
  needed += buflen;


  len[6] = needed;
  needed += compute_tag_length (needed);


  needed += 2 + DIM (oid_x509Certificate_for_pkcs_12);


  len[4] = needed;
  needed += compute_tag_length (needed);


  len[3] = needed;
  needed += compute_tag_length (needed);


  if (sha1hash)
    needed += DIM (data_attrtemplate) + 20;


  needed += 2 + DIM (oid_pkcs_12_CertBag);


  len[1] = needed;
  needed += compute_tag_length (needed);


  len[0] = needed;
  needed += compute_tag_length (needed);


  p = certseq = gcry_malloc (needed + 8 );
  if (!certseq)
    {
      log_error ("error allocating buffer\n");
      return NULL;
    }


  p = store_tag_length (p, TAG_SEQUENCE, len[0]);


  p = store_tag_length (p, TAG_SEQUENCE, len[1]);


  p = store_tag_length (p, TAG_OBJECT_ID, DIM (oid_pkcs_12_CertBag));
  memcpy (p, oid_pkcs_12_CertBag, DIM (oid_pkcs_12_CertBag));
  p += DIM (oid_pkcs_12_CertBag);


  p = store_tag_length (p, 0xa0, len[3]);


  p = store_tag_length (p, TAG_SEQUENCE, len[4]);


  p = store_tag_length (p, TAG_OBJECT_ID,
                        DIM (oid_x509Certificate_for_pkcs_12));
  memcpy (p, oid_x509Certificate_for_pkcs_12,
          DIM (oid_x509Certificate_for_pkcs_12));
  p += DIM (oid_x509Certificate_for_pkcs_12);


  p = store_tag_length (p, 0xa0, len[6]);


  p = store_tag_length (p, TAG_OCTET_STRING, buflen);
  memcpy (p, buffer, buflen);
  p += buflen;


  if (sha1hash)
    {
      memcpy (p, data_attrtemplate, DIM (data_attrtemplate));
      for (i=0; i < 8; i++)
        p[DATA_ATTRTEMPLATE_KEYID_OFF+2*i+1] = keyidstr[i];
      p += DIM (data_attrtemplate);
      memcpy (p, sha1hash, 20);
      p += 20;
    }

  certseqlen = p - certseq;
  if (needed != certseqlen)
    log_debug ("length mismatch: %lu, %lu\n",
               (unsigned long)needed, (unsigned long)certseqlen);


  n = 8 - certseqlen % 8;
  for (i=0; i < n; i++, certseqlen++)
    *p++ = n;

  *r_length = certseqlen;
  return certseq;
}
