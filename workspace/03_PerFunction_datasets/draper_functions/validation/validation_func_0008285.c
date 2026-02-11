EXTRACTOR_IPC_channel_send_ (struct EXTRACTOR_Channel *channel,
			     const void *data,
			     size_t size)
{
  const char *cdata = data;
  size_t off = 0;
  ssize_t ret;

  while (off < size)
    {
      ret = write (channel->cpipe_in, &cdata[off], size - off);
      if (ret <= 0)
	{
	  if (-1 == ret)
	    LOG_STRERROR ("write");
	  return -1;
	}
      off += ret;
    }
  return size;
}
