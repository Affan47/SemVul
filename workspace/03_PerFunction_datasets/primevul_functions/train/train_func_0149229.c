build_key_bag (unsigned char *buffer, size_t buflen, char *salt,
               const unsigned char *sha1hash, const char *keyidstr,
               size_t *r_length)
{
  size_t len[11], needed;
  unsigned char *p, *keybag;
  size_t keybaglen;


  needed = compute_tag_length (buflen);
  needed += buflen;


  needed += DIM (data_3desiter2048);


  len[8] = needed;
  needed += compute_tag_length (needed);


  len[7] = needed;
  needed += compute_tag_length (needed);


  if (sha1hash)
    needed += DIM (data_attrtemplate) + 20;


  needed += 2 + DIM (oid_pkcs_12_pkcs_8ShroudedKeyBag);


  len[5] = needed;
  needed += compute_tag_length ( needed);
  len[4] = needed;
  needed += compute_tag_length (needed);


  len[3] = needed;
  needed += compute_tag_length (needed);


  len[2] = needed;
  needed += compute_tag_length (needed);


  needed += 2 + DIM (oid_data);


  len[0] = needed;
  needed += compute_tag_length (needed);


  p = keybag = gcry_malloc (needed);
  if (!keybag)
    {
      log_error ("error allocating buffer\n");
      return NULL;
    }


  p = store_tag_length (p, TAG_SEQUENCE, len[0]);


  p = store_tag_length (p, TAG_OBJECT_ID, DIM (oid_data));
  memcpy (p, oid_data, DIM (oid_data));
  p += DIM (oid_data);


  p = store_tag_length (p, 0xa0, len[2]);


  p = store_tag_length (p, TAG_OCTET_STRING, len[3]);


  p = store_tag_length (p, TAG_SEQUENCE, len[4]);
  p = store_tag_length (p, TAG_SEQUENCE, len[5]);


  p = store_tag_length (p, TAG_OBJECT_ID,
                        DIM (oid_pkcs_12_pkcs_8ShroudedKeyBag));
  memcpy (p, oid_pkcs_12_pkcs_8ShroudedKeyBag,
          DIM (oid_pkcs_12_pkcs_8ShroudedKeyBag));
  p += DIM (oid_pkcs_12_pkcs_8ShroudedKeyBag);


  p = store_tag_length (p, 0xa0, len[7]);


  p = store_tag_length (p, TAG_SEQUENCE, len[8]);


  memcpy (p, data_3desiter2048, DIM (data_3desiter2048));
  memcpy (p + DATA_3DESITER2048_SALT_OFF, salt, 8);
  p += DIM (data_3desiter2048);


  p = store_tag_length (p, TAG_OCTET_STRING, buflen);
  memcpy (p, buffer, buflen);
  p += buflen;


  if (sha1hash)
    {
      int i;

      memcpy (p, data_attrtemplate, DIM (data_attrtemplate));
      for (i=0; i < 8; i++)
        p[DATA_ATTRTEMPLATE_KEYID_OFF+2*i+1] = keyidstr[i];
      p += DIM (data_attrtemplate);
      memcpy (p, sha1hash, 20);
      p += 20;
    }


  keybaglen = p - keybag;
  if (needed != keybaglen)
    log_debug ("length mismatch: %lu, %lu\n",
               (unsigned long)needed, (unsigned long)keybaglen);

  *r_length = keybaglen;
  return keybag;
}
