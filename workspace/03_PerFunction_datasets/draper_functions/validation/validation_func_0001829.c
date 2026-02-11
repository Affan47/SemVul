ares_parse_srv_reply (const unsigned char *abuf, int alen,
                      struct ares_srv_reply **srv_out)
{
  unsigned int qdcount, ancount, i;
  const unsigned char *aptr, *vptr;
  int status, rr_type, rr_class, rr_len;
  long len;
  char *hostname = NULL, *rr_name = NULL;
  struct ares_srv_reply *srv_head = NULL;
  struct ares_srv_reply *srv_last = NULL;
  struct ares_srv_reply *srv_curr;


  *srv_out = NULL;


  if (alen < HFIXEDSZ)
    return ARES_EBADRESP;


  qdcount = DNS_HEADER_QDCOUNT (abuf);
  ancount = DNS_HEADER_ANCOUNT (abuf);
  if (qdcount != 1)
    return ARES_EBADRESP;
  if (ancount == 0)
    return ARES_ENODATA;


  aptr = abuf + HFIXEDSZ;
  status = ares_expand_name (aptr, abuf, alen, &hostname, &len);
  if (status != ARES_SUCCESS)
    return status;

  if (aptr + len + QFIXEDSZ > abuf + alen)
    {
      free (hostname);
      return ARES_EBADRESP;
    }
  aptr += len + QFIXEDSZ;


  for (i = 0; i < ancount; i++)
    {

      status = ares_expand_name (aptr, abuf, alen, &rr_name, &len);
      if (status != ARES_SUCCESS)
        {
          break;
        }
      aptr += len;
      if (aptr + RRFIXEDSZ > abuf + alen)
        {
          status = ARES_EBADRESP;
          break;
        }
      rr_type = DNS_RR_TYPE (aptr);
      rr_class = DNS_RR_CLASS (aptr);
      rr_len = DNS_RR_LEN (aptr);
      aptr += RRFIXEDSZ;


      if (rr_class == C_IN && rr_type == T_SRV)
        {

          if (rr_len < 6)
            {
              status = ARES_EBADRESP;
              break;
            }


          srv_curr = ares_malloc_data(ARES_DATATYPE_SRV_REPLY);
          if (!srv_curr)
            {
              status = ARES_ENOMEM;
              break;
            }
          if (srv_last)
            {
              srv_last->next = srv_curr;
            }
          else
            {
              srv_head = srv_curr;
            }
          srv_last = srv_curr;

          vptr = aptr;
          srv_curr->priority = DNS__16BIT(vptr);
          vptr += sizeof(unsigned short);
          srv_curr->weight = DNS__16BIT(vptr);
          vptr += sizeof(unsigned short);
          srv_curr->port = DNS__16BIT(vptr);
          vptr += sizeof(unsigned short);

          status = ares_expand_name (vptr, abuf, alen, &srv_curr->host, &len);
          if (status != ARES_SUCCESS)
            break;
        }


      free (rr_name);
      rr_name = NULL;


      aptr += rr_len;
    }

  if (hostname)
    free (hostname);
  if (rr_name)
    free (rr_name);


  if (status != ARES_SUCCESS)
    {
      if (srv_head)
        ares_free_data (srv_head);
      return status;
    }


  *srv_out = srv_head;

  return ARES_SUCCESS;
}
