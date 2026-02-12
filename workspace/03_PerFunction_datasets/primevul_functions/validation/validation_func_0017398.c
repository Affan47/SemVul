void read_user_name(char *name)
{
  char *str=getenv("USERNAME");
  ma_strmake(name,str ? str : "ODBC", USERNAME_LENGTH);
}
