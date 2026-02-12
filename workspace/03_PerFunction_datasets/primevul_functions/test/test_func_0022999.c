void ha_maria::get_auto_increment(ulonglong offset, ulonglong increment,
                                  ulonglong nb_desired_values,
                                  ulonglong *first_value,
                                  ulonglong *nb_reserved_values)
{
  ulonglong nr;
  int error;
  uchar key[MARIA_MAX_KEY_BUFF];

  if (!table->s->next_number_key_offset)
  {
    ha_maria::info(HA_STATUS_AUTO);
    *first_value= stats.auto_increment_value;

    *nb_reserved_values= ULONGLONG_MAX;
    return;
  }


  maria_flush_bulk_insert(file, table->s->next_number_index);

  (void) extra(HA_EXTRA_KEYREAD);
  key_copy(key, table->record[0],
           table->key_info + table->s->next_number_index,
           table->s->next_number_key_offset);
  error= maria_rkey(file, table->record[1], (int) table->s->next_number_index,
                    key, make_prev_keypart_map(table->s->next_number_keypart),
                    HA_READ_PREFIX_LAST);
  if (error)
    nr= 1;
  else
  {

    nr= ((ulonglong) table->next_number_field->
         val_int_offset(table->s->rec_buff_length) + 1);
  }
  extra(HA_EXTRA_NO_KEYREAD);
  *first_value= nr;


  *nb_reserved_values= 1;
}
