resp_new (char *head)
{
  char *hdr;
  int count, size;

  struct response *resp = xnew0 (struct response);
  resp->data = head;

  if (*head == '\0')
    {


      return resp;
    }


  size = count = 0;
  hdr = head;
  while (1)
    {
      DO_REALLOC (resp->headers, size, count + 1, const char *);
      resp->headers[count++] = hdr;


      if (!hdr[0] || (hdr[0] == '\r' && hdr[1] == '\n') || hdr[0] == '\n')
        break;


      for (;;)
        {
          char *end = strchr (hdr, '\n');

          if (!end)
            {
              hdr += strlen (hdr);
              break;
            }

          hdr = end + 1;

          if (*hdr != ' ' && *hdr != '\t')
            break;


          *end = ' ';
          if (end > head && end[-1] == '\r')
            end[-1] = ' ';
        }
    }
  DO_REALLOC (resp->headers, size, count + 1, const char *);
  resp->headers[count] = NULL;

  return resp;
}
