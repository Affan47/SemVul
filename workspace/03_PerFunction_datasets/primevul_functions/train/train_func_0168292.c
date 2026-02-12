get_ftp_greeting (int csock, ccon *con)
{
  uerr_t err = 0;


  err = ftp_greeting (csock);
  if (err != FTPOK)
    {
      logputs (LOG_NOTQUIET, "Error in server response. Closing.\n");
      fd_close (csock);
      con->csock = -1;
    }

  return err;
}
