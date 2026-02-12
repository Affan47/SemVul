static int audit_null_notify(MYSQL_THD thd,
                             mysql_event_class_t event_class,
                             const void *event)
{
  char buffer[2000]= { 0, };
  int buffer_data= 0;
  unsigned long event_subclass= (unsigned long)*(int *)event;
  const char *order_str= (const char *)THDVAR(thd, event_order_check);
  int event_order_started= (int)THDVAR(thd, event_order_started);
  int exact_check= (int)THDVAR(thd, event_order_check_exact);
  LEX_CSTRING event_name= event_to_str(event_class, event_subclass);
  LEX_CSTRING event_token= get_token(&order_str);
  LEX_CSTRING event_data= get_token(&order_str);
  LEX_CSTRING event_command= get_token(&order_str);
  my_bool consume_event= TRUE;


  number_of_calls++;

  if (event_class == MYSQL_AUDIT_GENERAL_CLASS)
  {
    const struct mysql_event_general *event_general=
                                    (const struct mysql_event_general *)event;

    switch (event_general->event_subclass)
    {
    case MYSQL_AUDIT_GENERAL_LOG:
      number_of_calls_general_log++;
      break;
    case MYSQL_AUDIT_GENERAL_ERROR:
      number_of_calls_general_error++;
      break;
    case MYSQL_AUDIT_GENERAL_RESULT:
      number_of_calls_general_result++;
      break;
    case MYSQL_AUDIT_GENERAL_STATUS:
      number_of_calls_general_status++;
      break;
    default:
      break;
    }
  }
  else if (event_class == MYSQL_AUDIT_CONNECTION_CLASS)
  {
    const struct mysql_event_connection *event_connection=
                                (const struct mysql_event_connection *) event;

    switch (event_connection->event_subclass)
    {
    case MYSQL_AUDIT_CONNECTION_CONNECT:
      number_of_calls_connection_connect++;
      break;
    case MYSQL_AUDIT_CONNECTION_DISCONNECT:
      number_of_calls_connection_disconnect++;
      break;
    case MYSQL_AUDIT_CONNECTION_CHANGE_USER:
      number_of_calls_connection_change_user++;
      break;
    case MYSQL_AUDIT_CONNECTION_PRE_AUTHENTICATE:
      number_of_calls_connection_pre_authenticate++;
        break;
    default:
      break;
    }
  }
  else if (event_class == MYSQL_AUDIT_PARSE_CLASS)
  {
    const struct mysql_event_parse *event_parse =
                                      (const struct mysql_event_parse *)event;

    switch (event_parse->event_subclass)
    {
    case MYSQL_AUDIT_PARSE_PREPARSE:
      number_of_calls_parse_preparse++;
      break;
    case MYSQL_AUDIT_PARSE_POSTPARSE:
      number_of_calls_parse_postparse++;
      break;
    default:
      break;
    }
  }


  else if (event_class == MYSQL_AUDIT_SERVER_STARTUP_CLASS)
  {


    number_of_calls_server_startup++;
  }
  else if (event_class == MYSQL_AUDIT_SERVER_SHUTDOWN_CLASS)
  {


    number_of_calls_server_shutdown++;
  }
  else if (event_class == MYSQL_AUDIT_COMMAND_CLASS)
  {
    const struct mysql_event_command *event_command=
                                    (const struct mysql_event_command *)event;

    buffer_data= sprintf(buffer, "command_id=\"%d\"", event_command->command_id);

    switch (event_command->event_subclass)
    {
    case MYSQL_AUDIT_COMMAND_START:
      number_of_calls_command_start++;
      break;
    case MYSQL_AUDIT_COMMAND_END:
      number_of_calls_command_end++;
      break;
    default:
      break;
    }
  }
  else if (event_class == MYSQL_AUDIT_QUERY_CLASS)
  {
    const struct mysql_event_query *event_query=
                                      (const struct mysql_event_query *)event;

    buffer_data= sprintf(buffer, "sql_command_id=\"%d\"",
                         (int) event_query->sql_command_id);

    switch (event_query->event_subclass)
    {
    case MYSQL_AUDIT_QUERY_START:
      number_of_calls_query_start++;
      break;
    case MYSQL_AUDIT_QUERY_NESTED_START:
      number_of_calls_query_nested_start++;
      break;
    case MYSQL_AUDIT_QUERY_STATUS_END:
      number_of_calls_query_status_end++;
      break;
    case MYSQL_AUDIT_QUERY_NESTED_STATUS_END:
      number_of_calls_query_nested_status_end++;
      break;
    default:
      break;
    }
  }
  else if (event_class == MYSQL_AUDIT_TABLE_ACCESS_CLASS)
  {
    const struct mysql_event_table_access *event_table=
                               (const struct mysql_event_table_access *)event;

    buffer_data= sprintf(buffer, "db=\"%s\" table=\"%s\"",
                         event_table->table_database.str,
                         event_table->table_name.str);

    switch (event_table->event_subclass)
    {
    case MYSQL_AUDIT_TABLE_ACCESS_INSERT:
      number_of_calls_table_access_insert++;
      break;
    case MYSQL_AUDIT_TABLE_ACCESS_DELETE:
      number_of_calls_table_access_delete++;
      break;
    case MYSQL_AUDIT_TABLE_ACCESS_UPDATE:
      number_of_calls_table_access_update++;
      break;
    case MYSQL_AUDIT_TABLE_ACCESS_READ:
      number_of_calls_table_access_read++;
      break;
    default:
      break;
    }
  }
  else if (event_class == MYSQL_AUDIT_GLOBAL_VARIABLE_CLASS)
  {
    const struct mysql_event_global_variable *event_gvar =
                            (const struct mysql_event_global_variable *)event;


    buffer_data= sprintf(buffer, "name=\"%.*s\"",
                         MY_MIN((int) event_gvar->variable_name.length,
                                (int) (sizeof(buffer) - 8)),
                          event_gvar->variable_name.str);

    buffer_data+= sprintf(buffer + buffer_data, " value=\"%.*s\"",
                         MY_MIN((int) event_gvar->variable_value.length,
                                (int) (sizeof(buffer) - 16)),
                          event_gvar->variable_value.str);
    buffer[buffer_data]= '\0';

    switch (event_gvar->event_subclass)
    {
    case MYSQL_AUDIT_GLOBAL_VARIABLE_GET:
      number_of_calls_global_variable_get++;
      break;
    case MYSQL_AUDIT_GLOBAL_VARIABLE_SET:
      number_of_calls_global_variable_set++;
      break;
    default:
      break;
    }
  }

  process_event_record(thd, event_name, buffer, buffer_data);

  if (my_charset_latin1.coll->strnncoll(&my_charset_latin1,
                                        (const uchar *)event_name.str,
                                        event_name.length,
                                        (const uchar *)event_token.str,
                                        event_token.length, 0))
  {

    event_command.str= NULL;
    event_command.length= 0;

    if (exact_check == 1 && event_order_started == 1)
    {
      if (!(event_class == MYSQL_AUDIT_GENERAL_CLASS &&
            event_subclass == MYSQL_AUDIT_GENERAL_ERROR))
      {
        strxnmov(buffer, sizeof(buffer), event_name.str, " instead of ",
                 event_token.str, NullS);
        my_message(ER_AUDIT_API_ABORT, buffer, MYF(0));
      }

      THDVAR(thd, event_order_started)= 0;
      THDVAR(thd, event_order_check)= 0;

      return 1;
    }
  }
  else
  {
    LEX_CSTRING ignore= { C_STRING_WITH_LEN("<IGNORE>") };


    if (my_charset_latin1.coll->strnncoll(&my_charset_latin1,
                                          (const uchar *)event_data.str,
                                          event_data.length,
                                          (const uchar *) ignore.str,
                                          ignore.length, 0) &&
        my_charset_latin1.coll->strnncoll(&my_charset_latin1,
                                          (const uchar *) event_data.str,
                                          event_data.length,
                                          (const uchar *)buffer,
                                          (size_t)buffer_data, 0))
    {
      if (exact_check == 1 && event_order_started == 1)
      {
        char invalid_data_buffer[sizeof(buffer)]= { 0, };
        LEX_CSTRING status= { C_STRING_WITH_LEN("EVENT-ORDER-INVALID-DATA") };
        LEX_CSTRING order_cstr;

        lex_cstring_set(&order_cstr,
                        (const char *)THDVAR(thd, event_order_check));

        memmove((char *)order_cstr.str,
                (void *)status.str, status.length + 1);

        strxnmov(invalid_data_buffer, sizeof(invalid_data_buffer),
                 "Invalid data for '", event_name.str, "' -> ", buffer, NullS);
        my_message(ER_AUDIT_API_ABORT, invalid_data_buffer, MYF(0));

        THDVAR(thd, event_order_started)= 0;
        THDVAR(thd, event_order_check)= (char *)order_cstr.str;

        return 1;
      }


      event_command.str= NULL;
      event_command.length= 0;
    }
    else
    {
      LEX_CSTRING order_cstr;
      ulong consume= THDVAR(thd, event_order_check_consume_ignore_count);
      lex_cstring_set(&order_cstr,
                      (const char *)THDVAR(thd, event_order_check));

      THDVAR(thd, event_order_started)= 1;

      if (consume)
      {


        THDVAR(thd, event_order_check_consume_ignore_count)= consume - 1;
        consume_event= FALSE;
      }
      else
      {

        memmove((char*)order_cstr.str, (void*)order_str,
          order_cstr.length - (order_str - order_cstr.str) + 1);


        lex_cstring_set(&order_cstr, order_cstr.str);

        if (order_cstr.length == 0)
        {
          LEX_CSTRING status = { C_STRING_WITH_LEN("EVENT-ORDER-OK") };

          memmove((char *)order_cstr.str,
                  (void *)status.str, status.length + 1);


          THDVAR(thd, event_order_started)= 0;
        }
      }
    }
  }

  return process_command(thd, event_command, consume_event);
}
