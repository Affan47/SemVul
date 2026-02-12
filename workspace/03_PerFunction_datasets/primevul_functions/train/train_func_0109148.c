mysql_stmt_param_metadata(MYSQL_STMT *stmt)
{
  DBUG_ENTER("mysql_stmt_param_metadata");

  if (!stmt->param_count)
    DBUG_RETURN(0);


  DBUG_RETURN(0);
}
