bool compare_record(const TABLE *table)
{
  DBUG_ASSERT(records_are_comparable(table));

  if (table->file->ha_table_flags() & HA_PARTIAL_COLUMN_READ ||
      table->s->has_update_default_function)
  {


    for (Field **ptr= table->field ; *ptr != NULL; ptr++)
    {
      Field *field= *ptr;
      if (field->has_explicit_value() && !field->vcol_info)
      {
        if (field->real_maybe_null())
        {
          uchar null_byte_index= (uchar)(field->null_ptr - table->record[0]);

          if (((table->record[0][null_byte_index]) & field->null_bit) !=
              ((table->record[1][null_byte_index]) & field->null_bit))
            return TRUE;
        }
        if (field->cmp_binary_offset(table->s->rec_buff_length))
          return TRUE;
      }
    }
    return FALSE;
  }


  if (table->s->can_cmp_whole_record)
    return cmp_record(table,record[1]);

  if (memcmp(table->null_flags,
	     table->null_flags+table->s->rec_buff_length,
	     table->s->null_bytes_for_compare))
    return TRUE;

  for (Field **ptr= table->field ; *ptr ; ptr++)
  {
    Field *field= *ptr;
    if (field->has_explicit_value() && !field->vcol_info &&
	field->cmp_binary_offset(table->s->rec_buff_length))
      return TRUE;
  }
  return FALSE;
}
