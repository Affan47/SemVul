void read_user_name(char *name)
{
  char *str=getenv("USER");
  strmake(name,str ? str : "ODBC", USERNAME_LENGTH);
}
