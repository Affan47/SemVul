stv680_init (void)
{
  Stv680_Vidcam *dev;

  DBG (DBG_proc, "stv680_init: enter\n");


  dev = malloc (sizeof (Stv680_Vidcam));
  if (dev == NULL)
    {
      return NULL;
    }
  memset (dev, 0, sizeof (Stv680_Vidcam));


  dev->windoww_size = 0x20;
  dev->windoww = malloc (dev->windoww_size);
  if (dev->windoww == NULL)
    {
      free (dev);
      return NULL;
    }


  dev->windowr_size = 0x20;
  dev->windowr = malloc (dev->windowr_size);
  if (dev->windowr == NULL)
    {
      free (dev);
      free (dev->windoww);
      return NULL;
    }

  dev->fd = -1;

  DBG (DBG_proc, "stv680_init: exit\n");

  return (dev);
}
