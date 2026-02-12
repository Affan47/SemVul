static void reinit_result_set_metadata(MYSQL_STMT *stmt)
{

  if (stmt->field_count == 0)
  {


    stmt->field_count= stmt->mysql->field_count;

    alloc_stmt_fields(stmt);
  }
  else
  {


    update_stmt_fields(stmt);
  }
}
