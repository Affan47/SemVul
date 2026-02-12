void TABLE_LIST::print(THD *thd, table_map eliminated_tables, String *str,
                       enum_query_type query_type)
{
  if (nested_join)
  {
    str->append('(');
    print_join(thd, eliminated_tables, str, &nested_join->join_list, query_type);
    str->append(')');
  }
  else if (jtbm_subselect)
  {
    if (jtbm_subselect->engine->engine_type() ==
          subselect_engine::SINGLE_SELECT_ENGINE)
    {


      str->append(STRING_WITH_LEN(" <materialize> ("));
      jtbm_subselect->engine->print(str, query_type);
      str->append(')');
    }
    else
    {
      str->append(STRING_WITH_LEN(" <materialize> ("));
      subselect_hash_sj_engine *hash_engine;
      hash_engine= (subselect_hash_sj_engine*)jtbm_subselect->engine;
      hash_engine->materialize_engine->print(str, query_type);
      str->append(')');
    }
  }
  else
  {
    const char *cmp_name;
    if (view_name.str)
    {


      if (!(belong_to_view &&
            belong_to_view->compact_view_format))
      {
        append_identifier(thd, str, view_db.str, view_db.length);
        str->append('.');
      }
      append_identifier(thd, str, view_name.str, view_name.length);
      cmp_name= view_name.str;
    }
    else if (derived)
    {
      if (!is_with_table())
      {

        str->append('(');
        derived->print(str, query_type);
        str->append(')');
        cmp_name= "";
      }
      else
      {
        append_identifier(thd, str, table_name, table_name_length);
        cmp_name= table_name;
      }
    }
    else
    {


      if (!(belong_to_view &&
            belong_to_view->compact_view_format))
      {
        append_identifier(thd, str, db, db_length);
        str->append('.');
      }
      if (schema_table)
      {
        append_identifier(thd, str, schema_table_name,
                          strlen(schema_table_name));
        cmp_name= schema_table_name;
      }
      else
      {
        append_identifier(thd, str, table_name, table_name_length);
        cmp_name= table_name;
      }
#ifdef WITH_PARTITION_STORAGE_ENGINE
      if (partition_names && partition_names->elements)
      {
        int i, num_parts= partition_names->elements;
        List_iterator<String> name_it(*(partition_names));
        str->append(STRING_WITH_LEN(" PARTITION ("));
        for (i= 1; i <= num_parts; i++)
        {
          String *name= name_it++;
          append_identifier(thd, str, name->c_ptr(), name->length());
          if (i != num_parts)
            str->append(',');
        }
        str->append(')');
      }
#endif
    }
    if (my_strcasecmp(table_alias_charset, cmp_name, alias))
    {
      char t_alias_buff[MAX_ALIAS_NAME];
      const char *t_alias= alias;

      str->append(' ');
      if (lower_case_table_names == 1)
      {
        if (alias && alias[0])
        {
          strmov(t_alias_buff, alias);
          my_casedn_str(files_charset_info, t_alias_buff);
          t_alias= t_alias_buff;
        }
      }

      append_identifier(thd, str, t_alias, strlen(t_alias));
    }

    if (index_hints)
    {
      List_iterator<Index_hint> it(*index_hints);
      Index_hint *hint;

      while ((hint= it++))
      {
        str->append (STRING_WITH_LEN(" "));
        hint->print (thd, str);
      }
    }
  }
}
