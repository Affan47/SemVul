Event_job_data::construct_sp_sql(THD *thd, String *sp_sql)
{
  LEX_STRING buffer;
  const uint STATIC_SQL_LENGTH= 44;

  DBUG_ENTER("Event_job_data::construct_sp_sql");


  buffer.length= STATIC_SQL_LENGTH + name.length + body.length;
  if (! (buffer.str= (char*) thd->alloc(buffer.length)))
    DBUG_RETURN(TRUE);

  sp_sql->set(buffer.str, buffer.length, system_charset_info);
  sp_sql->length(0);


  sp_sql->append(C_STRING_WITH_LEN("CREATE "));
  sp_sql->append(C_STRING_WITH_LEN("PROCEDURE "));


  append_identifier(thd, sp_sql, name.str, name.length);


  sp_sql->append(C_STRING_WITH_LEN("() SQL SECURITY INVOKER "));

  sp_sql->append(body.str, body.length);

  DBUG_RETURN(thd->is_fatal_error);
}
