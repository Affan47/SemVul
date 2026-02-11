wait_ready (int fd)
{
  struct
  {
    Byte bytes[2];
    Byte scan[2];
  } result;

  size_t size = sizeof (result);
  SANE_Status status;

  struct {
    Byte cmd;
    Byte lun;
    Byte data_type;
    Byte re1[3];
    Byte tr_len[3];
    Byte ctrl;
  } cmd;

  memset (&cmd, 0, sizeof (cmd));

  cmd.cmd = 0x28;
  cmd.data_type = 0x80;

  set_size (cmd.tr_len, 3, sizeof (result));

  while (1)
    {
      status = sanei_scsi_cmd (fd, &cmd, sizeof (cmd),
			       &result, &size);

      if (status != SANE_STATUS_GOOD || size != sizeof (result))
	{


	  break;
	}
      else
	{


	  int left = get_size (result.scan, 2);

	  DBG (1, "wait_ready() : %d left...\n", left);

	  if (!left)
	    break;

	  else if (left < 200)
	    usleep (left * 5000);
	  else
	    sleep (left / 200);
	}
    }

  return;
}
