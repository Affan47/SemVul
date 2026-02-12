void calc_group_buffer(TMP_TABLE_PARAM *param, ORDER *group)
{
  uint key_length=0, parts=0, null_parts=0;

  for (; group ; group=group->next)
  {
    Item *group_item= *group->item;
    Field *field= group_item->get_tmp_table_field();
    if (field)
    {
      enum_field_types type;
      if ((type= field->type()) == MYSQL_TYPE_BLOB)
	key_length+=MAX_BLOB_WIDTH;
      else if (type == MYSQL_TYPE_VARCHAR || type == MYSQL_TYPE_VAR_STRING)
        key_length+= field->field_length + HA_KEY_BLOB_LENGTH;
      else if (type == MYSQL_TYPE_BIT)
      {

        key_length+= 8;
      }
      else
	key_length+= field->pack_length();
    }
    else
    {
      switch (group_item->cmp_type()) {
      case REAL_RESULT:
        key_length+= sizeof(double);
        break;
      case INT_RESULT:
        key_length+= sizeof(longlong);
        break;
      case DECIMAL_RESULT:
        key_length+= my_decimal_get_binary_size(group_item->max_length -
                                                (group_item->decimals ? 1 : 0),
                                                group_item->decimals);
        break;
      case TIME_RESULT:
      {


        key_length+= 8;
        break;
      }
      case STRING_RESULT:
      {
        enum enum_field_types type= group_item->field_type();
        if (type == MYSQL_TYPE_BLOB)
          key_length+= MAX_BLOB_WIDTH;
        else
        {


          key_length+= group_item->max_length + HA_KEY_BLOB_LENGTH;
        }
        break;
      }
      default:

        DBUG_ASSERT(0);
        my_error(ER_OUT_OF_RESOURCES, MYF(ME_FATAL));
      }
    }
    parts++;
    if (group_item->maybe_null)
      null_parts++;
  }
  param->group_length= key_length + null_parts;
  param->group_parts= parts;
  param->group_null_parts= null_parts;
}
