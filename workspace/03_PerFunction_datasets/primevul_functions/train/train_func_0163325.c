int rfc822_write_address (char *buf, size_t buflen, ADDRESS *addr, int display)
{
  char *pbuf = buf;
  size_t len = mutt_strlen (buf);

  buflen--;

  if (len > 0)
  {
    if (len > buflen)
      return pbuf - buf;

    pbuf += len;
    buflen -= len;
    if (!buflen)
      goto done;
    *pbuf++ = ',';
    buflen--;
    if (!buflen)
      goto done;
    *pbuf++ = ' ';
    buflen--;
  }

  for (; addr && buflen > 0; addr = addr->next)
  {


    rfc822_write_address_single (pbuf, buflen + 1, addr, display);


    len = mutt_strlen (pbuf);
    pbuf += len;
    buflen -= len;


    if (addr->next && addr->next->mailbox && !addr->group)
    {
      if (!buflen)
	goto done;
      *pbuf++ = ',';
      buflen--;
      if (!buflen)
	goto done;
      *pbuf++ = ' ';
      buflen--;
    }
  }
done:
  *pbuf = 0;
  return pbuf - buf;
}
