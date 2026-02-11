get_unique_file_id(void)
{
  int new_fuid;


  new_fuid = vt_env_funique();

  if( new_fuid == -1 )
  {
    new_fuid = 0;
  }
  else if( new_fuid == 0 )
  {
    int  fd;
    int8_t tmp_len;
    struct flock fl;
    char lock_filename[300];
    char tmp[16] = "";
    uint8_t do_unlock = 1;

    VT_SUSPEND_IO_TRACING(VT_CURRENT_THREAD);


    snprintf(lock_filename, sizeof(lock_filename)-1, "%s/%s.lock",
             vt_env_gdir(), vt_env_fprefix());


    if( (fd = open(lock_filename, (O_RDWR | O_CREAT),
                   (S_IRUSR | S_IWUSR))) == -1 )
      vt_error_msg("Cannot open file %s: %s", lock_filename, strerror(errno));


    fl.l_type = F_WRLCK; fl.l_whence = SEEK_SET; fl.l_start = 0; fl.l_len = 0;
    if( fcntl(fd, F_SETLKW, &fl) == -1 )
    {
      do_unlock = 0;
      vt_warning("Cannot lock file %s: %s", lock_filename, strerror(errno));
    }


    if( read(fd, tmp, 15) == -1 )
      vt_error_msg("Cannot read file %s: %s", lock_filename, strerror(errno));


    tmp[15] = '\0';

    if( tmp[0] == '\0' )
      new_fuid = 0;
    else
      new_fuid = atoi(tmp) + 1;


    lseek(fd, 0, SEEK_SET);
    snprintf(tmp, sizeof(tmp)-1, "%u\n", new_fuid);
    tmp_len = strlen( tmp );
    if( tmp_len > write(fd, tmp, tmp_len) )
      vt_error_msg("Failed to write to file %s: %s", lock_filename,
                   strerror(errno));


    if( do_unlock )
    {
      fl.l_type = F_UNLCK;
      if (fcntl(fd, F_SETLK, &fl) == -1)
        vt_error_msg("Cannot unlock file %s: %s",
                     lock_filename, strerror(errno));
    }


    close(fd);

    VT_RESUME_IO_TRACING(VT_CURRENT_THREAD);
  }

  return new_fuid;
}
