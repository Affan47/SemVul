is_comments(const char *sql, char *nextc)
{
  if (sql[0] == '/' && sql[1] == '*')
  {
    int i = 2;
    *nextc = '*';
    return i;
  }
  return 0;
}
