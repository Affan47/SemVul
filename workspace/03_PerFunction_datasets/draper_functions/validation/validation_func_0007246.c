stop_keylogfile()
{
  if ( keylogfilefd ) fclose(keylogfilefd);
  keylogfilefd = NULL;
  keylogfile_flag = 0;
}
