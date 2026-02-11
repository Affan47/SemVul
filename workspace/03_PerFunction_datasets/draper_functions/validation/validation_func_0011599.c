my_create(const char *FileName, int CreateFlags, int access_flags,
	       myf MyFlags)
{
  int fd, rc;
  DBUG_ENTER("my_create");
  DBUG_PRINT("my",("Name: '%s' CreateFlags: %d  AccessFlags: %d  MyFlags: %d",
		   FileName, CreateFlags, access_flags, MyFlags));
#if defined(_WIN32)
  fd= my_win_open(FileName, access_flags | O_CREAT);
#else
  fd= open((char *) FileName, access_flags | O_CREAT,
	    CreateFlags ? CreateFlags : my_umask);
#endif

  if ((MyFlags & MY_SYNC_DIR) && (fd >=0) &&
      my_sync_dir_by_file(FileName, MyFlags))
  {
    my_close(fd, MyFlags);
    fd= -1;
  }

  rc= my_register_filename(fd, FileName, FILE_BY_CREATE,
                           EE_CANTCREATEFILE, MyFlags);


  if (unlikely(fd >= 0 && rc < 0))
  {
    int tmp= my_errno;
    my_close(fd, MyFlags);
    my_delete(FileName, MyFlags);
    my_errno= tmp;
  }

  DBUG_RETURN(rc);
}
