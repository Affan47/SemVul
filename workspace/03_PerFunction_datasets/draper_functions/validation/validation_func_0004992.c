reply(EpmdVars *g,int fd,char *buf,int len)
{
  int val;

  if (len < 0)
    {
      dbg_printf(g,0,"Invalid length in write %d",len);
      return -1;
    }

  if (g->delay_write)
    sleep(g->delay_write);

  val = write(fd,buf,len);
  if (val < 0)
    dbg_perror(g,"error in write");
  else if (val != len)
    dbg_printf(g,0,"could only send %d bytes out of %d to fd %d",val,len,fd);

  dbg_print_buf(g,buf,len);

  return val;
}
