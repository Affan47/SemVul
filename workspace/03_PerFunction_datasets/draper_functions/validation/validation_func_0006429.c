pie_get_halftones (Pie_Device * dev, int sfd)
{
  int i;
  size_t size;
  SANE_Status status;
  unsigned char *data;
  unsigned char buffer[128];

  DBG (DBG_proc, "get_halftones\n");

  for (i = 0; i < dev->inquiry_halftones; i++)
    {
      size = 6;

      set_write_length (swrite.cmd, size);

      memcpy (buffer, swrite.cmd, swrite.size);

      data = buffer + swrite.size;
      memset (data, 0, size);

      set_command (data, READ_HALFTONE);
      set_data_length (data, 2);
      data[4] = i;

      status = sanei_scsi_cmd (sfd, buffer, swrite.size + size, NULL, NULL);
      if (status)
	{
	  DBG (DBG_error,
	       "pie_get_halftones: write command returned status %s\n",
	       sane_strstatus (status));
	}
      else
	{

	  memset (buffer, '\0', sizeof buffer);

	  size = 128;
	  set_read_length (sread.cmd, size);

	  DBG (DBG_info, "doing read\n");
	  status = sanei_scsi_cmd (sfd, sread.cmd, sread.size, buffer, &size);
	  if (status)
	    {
	      DBG (DBG_error,
		   "pie_get_halftones: read command returned status %s\n",
		   sane_strstatus (status));
	    }
	  else
	    {
	      unsigned char *s;

	      s = buffer + 8 + buffer[6] * buffer[7];

	      DBG (DBG_info, "halftone %d: %s\n", i, s);

	      dev->halftone_list[i] = strdup ((char *)s);
	    }
	}
    }
  dev->halftone_list[i] = NULL;
}
