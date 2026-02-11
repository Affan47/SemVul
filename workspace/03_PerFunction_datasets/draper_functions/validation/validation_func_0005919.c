_gss_encapsulate_token_prefix (const char *prefix, size_t prefixlen,
			       const char *in, size_t inlen,
			       const char *oid, OM_uint32 oidlen,
			       void **out, size_t * outlen)
{
  size_t oidlenlen;
  size_t asn1len, asn1lenlen;
  unsigned char *p;

  if (prefix == NULL)
    prefixlen = 0;

  _gss_asn1_length_der (oidlen, NULL, &oidlenlen);
  asn1len = 1 + oidlenlen + oidlen + prefixlen + inlen;
  _gss_asn1_length_der (asn1len, NULL, &asn1lenlen);

  *outlen = 1 + asn1lenlen + asn1len;
  p = *out = malloc (*outlen);
  if (!p)
    return -1;

  *p++ = '\x60';
  _gss_asn1_length_der (asn1len, p, &asn1lenlen);
  p += asn1lenlen;
  *p++ = '\x06';
  _gss_asn1_length_der (oidlen, p, &oidlenlen);
  p += oidlenlen;
  memcpy (p, oid, oidlen);
  p += oidlen;
  if (prefixlen > 0)
    {
      memcpy (p, prefix, prefixlen);
      p += prefixlen;
    }
  memcpy (p, in, inlen);

  return 0;
}
