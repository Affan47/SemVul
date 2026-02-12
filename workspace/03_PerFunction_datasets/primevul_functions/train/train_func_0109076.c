static int stmt_fetch_row(MYSQL_STMT *stmt, uchar *row)
{
  MYSQL_BIND  *my_bind, *end;
  MYSQL_FIELD *field;
  uchar *null_ptr, bit;
  int truncation_count= 0;


  DBUG_ASSERT(stmt->field_count);
  DBUG_ASSERT(row);

  if (!stmt->bind_result_done)
  {

    return 0;
  }

  null_ptr= row;
  row+= (stmt->field_count+9)/8;
  bit= 4;


  for (my_bind= stmt->bind, end= my_bind + stmt->field_count,
         field= stmt->fields ;
       my_bind < end ;
       my_bind++, field++)
  {
    *my_bind->error= 0;
    if (*null_ptr & bit)
    {


      my_bind->row_ptr= NULL;
      *my_bind->is_null= 1;
    }
    else
    {
      *my_bind->is_null= 0;
      my_bind->row_ptr= row;
      (*my_bind->fetch_result)(my_bind, field, &row);
      truncation_count+= *my_bind->error;
    }
    if (!((bit<<=1) & 255))
    {
      bit= 1;
      null_ptr++;
    }
  }
  if (truncation_count && (stmt->bind_result_done & REPORT_DATA_TRUNCATION))
    return MYSQL_DATA_TRUNCATED;
  return 0;
}
