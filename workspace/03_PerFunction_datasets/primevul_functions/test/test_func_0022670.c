uint get_table_def_key(const TABLE_LIST *table_list, const char **key)
{


  DBUG_ASSERT(!strcmp(table_list->get_db_name(),
                      table_list->mdl_request.key.db_name()) &&
              !strcmp(table_list->get_table_name(),
                      table_list->mdl_request.key.name()));

  *key= (const char*)table_list->mdl_request.key.ptr() + 1;
  return table_list->mdl_request.key.length() - 1;
}
