static void update_stmt_fields(MYSQL_STMT *stmt)
{
  MYSQL_FIELD *field= stmt->mysql->fields;
  MYSQL_FIELD *field_end= field + stmt->field_count;
  MYSQL_FIELD *stmt_field= stmt->fields;
  MYSQL_BIND *my_bind= stmt->bind_result_done ? stmt->bind : 0;

  if (stmt->field_count != stmt->mysql->field_count)
  {


    set_stmt_error(stmt, CR_NEW_STMT_METADATA, unknown_sqlstate, NULL);
    return;
  }

  for (; field < field_end; ++field, ++stmt_field)
  {
    stmt_field->charsetnr= field->charsetnr;
    stmt_field->length   = field->length;
    stmt_field->type     = field->type;
    stmt_field->flags    = field->flags;
    stmt_field->decimals = field->decimals;
    if (my_bind)
    {

      (void) setup_one_fetch_function(my_bind++, stmt_field);
    }
  }
}
