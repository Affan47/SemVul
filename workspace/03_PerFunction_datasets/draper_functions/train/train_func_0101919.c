gl841_bulk_read_data (Genesys_Device * dev, uint8_t addr,
			      uint8_t * data, size_t len)
{
  SANE_Status status;
  size_t size, target;
  uint8_t outdata[8], *buffer;

  DBG (DBG_io, "gl841_bulk_read_data: requesting %lu bytes\n",
       (u_long) len);

  if (len == 0)
      return SANE_STATUS_GOOD;

  status =
    sanei_usb_control_msg (dev->dn, REQUEST_TYPE_OUT, REQUEST_REGISTER,
			   VALUE_SET_REGISTER, INDEX, 1, &addr);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "gl841_bulk_read_data failed while setting register: %s\n",
	   sane_strstatus (status));
      return status;
    }

  outdata[0] = BULK_IN;
  outdata[1] = BULK_RAM;
  outdata[2] = VALUE_BUFFER & 0xff;
  outdata[3] = (VALUE_BUFFER >> 8) & 0xff;
  outdata[4] = (len & 0xff);
  outdata[5] = ((len >> 8) & 0xff);
  outdata[6] = ((len >> 16) & 0xff);
  outdata[7] = ((len >> 24) & 0xff);

  status =
    sanei_usb_control_msg (dev->dn, REQUEST_TYPE_OUT, REQUEST_BUFFER,
			   VALUE_BUFFER, INDEX, sizeof (outdata), outdata);
  if (status != SANE_STATUS_GOOD)
    {
      DBG (DBG_error,
	   "gl841_bulk_read_data failed while writing command: %s\n",
	   sane_strstatus (status));
      return status;
    }

  target = len;
  buffer = data;
  while (target)
    {
      if (target > BULKIN_MAXSIZE)
	size = BULKIN_MAXSIZE;
      else
	size = target;

      DBG (DBG_io2,
	   "gl841_bulk_read_data: trying to read %lu bytes of data\n",
	   (u_long) size);

      status = sanei_usb_read_bulk (dev->dn, data, &size);

      if (status != SANE_STATUS_GOOD)
	{
	  DBG (DBG_error,
	       "gl841_bulk_read_data failed while reading bulk data: %s\n",
	       sane_strstatus (status));
	  return status;
	}

      DBG (DBG_io2,
	   "gl841_bulk_read_data read %lu bytes, %lu remaining\n",
	   (u_long) size, (u_long) (target - size));

      target -= size;
      data += size;
    }


  if (DBG_LEVEL >= DBG_data && dev->binary!=NULL)
    {
      fwrite(buffer, len, 1, dev->binary);
    }
  DBGCOMPLETED;
  return SANE_STATUS_GOOD;
}
