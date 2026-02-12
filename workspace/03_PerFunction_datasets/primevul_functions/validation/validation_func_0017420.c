mysql_kill(MYSQL *mysql,ulong pid)
{
  char buff[12];
  int4store(buff,pid);

  return(ma_simple_command(mysql, COM_PROCESS_KILL,buff,4,0,0));
}
