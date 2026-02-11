outstring ARGS1((outmsg),
CONST char *outmsg)
{
  if ( quiet_flag || !outmsg ) return;
  if ( broken_pipe_flag )
  { broken_pipe_flag = 0; kb_error(1349,"Broken pipe.\n",RECOVERABLE); }

  if ( outfd == NULL ) outfd = stdout;

  if ( logfile_flag && (outfd==stdout) )
      fprintf(logfilefd,outmsg);

#if defined(MAC_APP) || defined(WIN32S) || defined(MAC_CW)
  if ( outfd == stdout )
     write_to_console(outmsg);
  else
     fputs(outmsg,outfd);
#else
  fputs(outmsg,outfd);
  fflush(outfd);
#endif
}
