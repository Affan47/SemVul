enum_field_types odbc_temporal_literal_type(const LEX_STRING *type_str) const
  {


    if (collation.repertoire == MY_REPERTOIRE_ASCII &&
        str_value.length() < MAX_DATE_STRING_REP_LENGTH * 4)
    {
      if (type_str->length == 1)
      {
        if (type_str->str[0] == 'd')
          return MYSQL_TYPE_DATE;
        else if (type_str->str[0] == 't')
          return MYSQL_TYPE_TIME;
      }
      else if (type_str->length == 2)
      {
        if (type_str->str[0] == 't' && type_str->str[1] == 's')
          return MYSQL_TYPE_DATETIME;
      }
    }
    return MYSQL_TYPE_STRING;
  }
