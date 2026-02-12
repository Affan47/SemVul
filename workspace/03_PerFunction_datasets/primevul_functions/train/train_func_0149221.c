build_cert_bag (unsigned char *buffer, size_t buflen, char *salt,
                size_t *r_length)
{
  size_t len[9], needed;
  unsigned char *p, *certbag;
  size_t certbaglen;


  needed = compute_tag_length (buflen);
  needed += buflen;


  needed += DIM (data_rc2iter2048);


  needed += 2 + DIM (oid_data);


  len[5] = needed;
  needed += compute_tag_length ( needed);


  needed += 3;


  len[3] = needed;
  needed += compute_tag_length (needed);


  len[2] = needed;
  needed += compute_tag_length (needed);


  needed += 2 + DIM (oid_encryptedData);


  len[0] = needed;
  needed += compute_tag_length (needed);


  p = certbag = gcry_malloc (needed);
  if (!certbag)
    {
      log_error ("error allocating buffer\n");
      return NULL;
    }


  p = store_tag_length (p, TAG_SEQUENCE, len[0]);


  p = store_tag_length (p, TAG_OBJECT_ID, DIM (oid_encryptedData));
  memcpy (p, oid_encryptedData, DIM (oid_encryptedData));
  p += DIM (oid_encryptedData);


  p = store_tag_length (p, 0xa0, len[2]);


  p = store_tag_length (p, TAG_SEQUENCE, len[3]);


  *p++ = TAG_INTEGER;
  *p++ = 1;
  *p++ = 0;


  p = store_tag_length (p, TAG_SEQUENCE, len[5]);


  p = store_tag_length (p, TAG_OBJECT_ID, DIM (oid_data));
  memcpy (p, oid_data, DIM (oid_data));
  p += DIM (oid_data);


  memcpy (p, data_rc2iter2048, DIM (data_rc2iter2048));
  memcpy (p + DATA_RC2ITER2048_SALT_OFF, salt, 8);
  p += DIM (data_rc2iter2048);


  p = store_tag_length (p, 0x80, buflen);
  memcpy (p, buffer, buflen);
  p += buflen;
  certbaglen = p - certbag;

  if (needed != certbaglen)
    log_debug ("length mismatch: %lu, %lu\n",
               (unsigned long)needed, (unsigned long)certbaglen);

  *r_length = certbaglen;
  return certbag;
}
