sanei_umax_pp_read (long len, int window, int dpi, int last,
                    unsigned char *buffer)
{
  int read = 0;
  int bytes;

  DBG (3, "sanei_umax_pp_read\n");
  if (lock_parport () == UMAX1220P_BUSY)
    return UMAX1220P_BUSY;


  while (read < len)
    {
      bytes =
        sanei_umax_pp_readBlock (len - read, window, dpi, last,
                                 buffer + read);
      if (bytes == 0)
        {
          sanei_umax_pp_endSession ();
          return UMAX1220P_READ_FAILED;
        }
      read += bytes;
    }
  unlock_parport ();
  return UMAX1220P_OK;
}
