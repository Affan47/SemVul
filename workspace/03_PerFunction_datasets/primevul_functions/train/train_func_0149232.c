create_final (struct buffer_s *sequences, const char *pw, size_t *r_length)
{
  int i;
  size_t needed = 0;
  size_t len[8], n;
  unsigned char *macstart;
  size_t maclen;
  unsigned char *result, *p;
  size_t resultlen;
  char salt[8];
  unsigned char keybuf[20];
  gcry_md_hd_t md;
  int rc;
  int with_mac = 1;


  for (i=0; sequences[i].buffer; i++)
    needed += sequences[i].length;


  len[6] = needed;
  n = compute_tag_length (needed);
  needed += n;


  len[5] = needed;
  n = compute_tag_length (needed);
  needed += n;


  len[4] = needed;
  n = compute_tag_length (needed);
  needed += n;


  needed += 2 + DIM (oid_data);


  len[2] = needed;
  n = compute_tag_length (needed);
  needed += n;


  needed += 3;


  if (with_mac)
    needed += DIM (data_mactemplate);
  len[0] = needed;
  n = compute_tag_length (needed);
  needed += n;


  result = gcry_malloc (needed);
  if (!result)
    {
      log_error ("error allocating buffer\n");
      return NULL;
    }
  p = result;


  p = store_tag_length (p, TAG_SEQUENCE, len[0]);


  *p++ = TAG_INTEGER;
  *p++ = 1;
  *p++ = 3;


  p = store_tag_length (p, TAG_SEQUENCE, len[2]);


  p = store_tag_length (p, TAG_OBJECT_ID, DIM (oid_data));
  memcpy (p, oid_data, DIM (oid_data));
  p += DIM (oid_data);


  p = store_tag_length (p, 0xa0, len[4]);


  p = store_tag_length (p, TAG_OCTET_STRING, len[5]);


  macstart = p;
  p = store_tag_length (p, TAG_SEQUENCE, len[6]);


  for (i=0; sequences[i].buffer; i++)
    {
      memcpy (p, sequences[i].buffer, sequences[i].length);
      p += sequences[i].length;
    }

  if (with_mac)
    {

      maclen = p - macstart;
      gcry_randomize (salt, 8, GCRY_STRONG_RANDOM);
      if (string_to_key (3, salt, 8, 2048, pw, 20, keybuf))
        {
          gcry_free (result);
          return NULL;
        }
      rc = gcry_md_open (&md, GCRY_MD_SHA1, GCRY_MD_FLAG_HMAC);
      if (rc)
        {
          log_error ("gcry_md_open failed: %s\n", gpg_strerror (rc));
          gcry_free (result);
          return NULL;
        }
      rc = gcry_md_setkey (md, keybuf, 20);
      if (rc)
        {
          log_error ("gcry_md_setkey failed: %s\n", gpg_strerror (rc));
          gcry_md_close (md);
          gcry_free (result);
          return NULL;
        }
      gcry_md_write (md, macstart, maclen);


      memcpy (p, data_mactemplate, DIM (data_mactemplate));
      memcpy (p + DATA_MACTEMPLATE_SALT_OFF, salt, 8);
      memcpy (p + DATA_MACTEMPLATE_MAC_OFF, gcry_md_read (md, 0), 20);
      p += DIM (data_mactemplate);
      gcry_md_close (md);
    }


  resultlen = p - result;
  if (needed != resultlen)
    log_debug ("length mismatch: %lu, %lu\n",
               (unsigned long)needed, (unsigned long)resultlen);

  *r_length = resultlen;
  return result;
}
