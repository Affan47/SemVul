handler::check_if_supported_inplace_alter(TABLE *altered_table,
                                          Alter_inplace_info *ha_alter_info)
{
  DBUG_ENTER("handler::check_if_supported_inplace_alter");

  HA_CREATE_INFO *create_info= ha_alter_info->create_info;

  if (altered_table->versioned(VERS_TIMESTAMP))
    DBUG_RETURN(HA_ALTER_INPLACE_NOT_SUPPORTED);

  alter_table_operations inplace_offline_operations=
    ALTER_COLUMN_TYPE_CHANGE_BY_ENGINE |
    ALTER_COLUMN_NAME |
    ALTER_RENAME_COLUMN |
    ALTER_CHANGE_COLUMN_DEFAULT |
    ALTER_COLUMN_DEFAULT |
    ALTER_COLUMN_OPTION |
    ALTER_CHANGE_CREATE_OPTION |
    ALTER_DROP_CHECK_CONSTRAINT |
    ALTER_PARTITIONED |
    ALTER_VIRTUAL_GCOL_EXPR |
    ALTER_RENAME;


  if (ha_alter_info->handler_flags & ~inplace_offline_operations)
    DBUG_RETURN(HA_ALTER_INPLACE_NOT_SUPPORTED);


  if (create_info->used_fields & (HA_CREATE_USED_CHARSET |
                                  HA_CREATE_USED_DEFAULT_CHARSET |
                                  HA_CREATE_USED_PACK_KEYS |
                                  HA_CREATE_USED_CHECKSUM |
                                  HA_CREATE_USED_MAX_ROWS) ||
      (table->s->row_type != create_info->row_type))
    DBUG_RETURN(HA_ALTER_INPLACE_NOT_SUPPORTED);

  uint table_changes= (ha_alter_info->handler_flags &
                       ALTER_COLUMN_TYPE_CHANGE_BY_ENGINE) ?
    IS_EQUAL_PACK_LENGTH : IS_EQUAL_YES;
  if (table->file->check_if_incompatible_data(create_info, table_changes)
      == COMPATIBLE_DATA_YES)
    DBUG_RETURN(HA_ALTER_INPLACE_NO_LOCK);

  DBUG_RETURN(HA_ALTER_INPLACE_NOT_SUPPORTED);
}
