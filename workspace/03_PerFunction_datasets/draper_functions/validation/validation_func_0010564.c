send_errmsg(char const *fmt,...)
{
  va_list ap;

  va_start(ap,fmt);


  if(!cwirc_sem_P(sharedmem->semid,SEM_IO_PROCESS_MSG))
  {
    vsprintf(sharedmem->io_process_msg,fmt,ap);


    cwirc_sem_V(sharedmem->semid,SEM_IO_PROCESS_MSG);
  }

  va_end(ap);
}
