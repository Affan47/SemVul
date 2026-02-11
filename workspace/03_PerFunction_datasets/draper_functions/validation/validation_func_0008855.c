mxml_fd_write(mxml_fdbuf_t *buf)
{
  int		bytes;
  unsigned char	*ptr;


  if (!buf)
    return (-1);


  if (buf->current == buf->buffer)
    return (0);


  for (ptr = buf->buffer; ptr < buf->current; ptr += bytes)
    if ((bytes = write(buf->fd, ptr, buf->current - ptr)) < 0)
      return (-1);


  buf->current = buf->buffer;

  return (0);
}
