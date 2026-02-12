void ha_maria::update_create_info(HA_CREATE_INFO *create_info)
{
  ha_maria::info(HA_STATUS_AUTO | HA_STATUS_CONST);
  if (!(create_info->used_fields & HA_CREATE_USED_AUTO))
  {
    create_info->auto_increment_value= stats.auto_increment_value;
  }
  create_info->data_file_name= data_file_name;
  create_info->index_file_name= index_file_name;


  if (create_info->row_type != ROW_TYPE_DEFAULT &&
      !(thd_sql_command(ha_thd()) == SQLCOM_ALTER_TABLE))
    create_info->row_type= get_row_type();


  if (create_info->page_checksum == HA_CHOICE_UNDEF)
    create_info->page_checksum=
      (file->s->options & HA_OPTION_PAGE_CHECKSUM) ? HA_CHOICE_YES :
      HA_CHOICE_NO;
}
