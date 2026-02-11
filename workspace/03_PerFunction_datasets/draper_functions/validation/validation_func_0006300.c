attach_one_device (SANE_String_Const devname)
{
  Mustek_Usb_Device *dev;
  SANE_Status status;

  RIE (attach (devname, &dev, SANE_FALSE));

  if (dev)
    {


      if (new_dev_len >= new_dev_alloced)
	{
	  new_dev_alloced += 4;
	  if (new_dev)
	    new_dev =
	      realloc (new_dev, new_dev_alloced * sizeof (new_dev[0]));
	  else
	    new_dev = malloc (new_dev_alloced * sizeof (new_dev[0]));
	  if (!new_dev)
	    {
	      DBG (1, "attach_one_device: out of memory\n");
	      return SANE_STATUS_NO_MEM;
	    }
	}
      new_dev[new_dev_len++] = dev;
    }
  return SANE_STATUS_GOOD;
}
