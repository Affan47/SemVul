static CURLUcode hostname_check(struct Curl_URL *u, char *hostname)
{
  size_t len;
  size_t hlen = strlen(hostname);

  if(hostname[0] == '[') {
    const char *l = "0123456789abcdefABCDEF:.";
    if(hlen < 4)
      return CURLUE_BAD_IPV6;
    hostname++;
    hlen -= 2;

    if(hostname[hlen] != ']')
      return CURLUE_BAD_IPV6;


    len = strspn(hostname, l);
    if(hlen != len) {
      hlen = len;
      if(hostname[len] == '%') {

        char zoneid[16];
        int i = 0;
        char *h = &hostname[len + 1];

        if(!strncmp(h, "25", 2) && h[2] && (h[2] != ']'))
          h += 2;
        while(*h && (*h != ']') && (i < 15))
          zoneid[i++] = *h++;
        if(!i || (']' != *h))

          return CURLUE_MALFORMED_INPUT;
        zoneid[i] = 0;
        u->zoneid = strdup(zoneid);
        if(!u->zoneid)
          return CURLUE_OUT_OF_MEMORY;
        hostname[len] = ']';
        hostname[len + 1] = 0;
      }
      else
        return CURLUE_BAD_IPV6;

    }
#ifdef ENABLE_IPV6
    {
      char dest[16];
      char norm[MAX_IPADR_LEN];
      hostname[hlen] = 0;
      if(1 != Curl_inet_pton(AF_INET6, hostname, dest))
        return CURLUE_BAD_IPV6;


      if(Curl_inet_ntop(AF_INET6, dest, norm, sizeof(norm)) &&
         (strlen(norm) < hlen)) {
        strcpy(hostname, norm);
        hlen = strlen(norm);
        hostname[hlen + 1] = 0;
      }
      hostname[hlen] = ']';
    }
#endif
  }
  else {

    len = strcspn(hostname, " \r\n\t/:#?!@");
    if(hlen != len)

      return CURLUE_BAD_HOSTNAME;
  }
  if(!hostname[0])
    return CURLUE_NO_HOST;
  return CURLUE_OK;
}
