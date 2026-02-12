static void test_status()
{
  DBUG_ENTER("test_status");
  myheader("test_status");

  if (!mysql_stat(mysql))
  {
    myerror("mysql_stat failed");
    die(__FILE__, __LINE__, "mysql_stat failed");
  }
  DBUG_VOID_RETURN;
}
