void handler::get_auto_increment(ulonglong offset, ulonglong increment,
                                 ulonglong nb_desired_values,
                                 ulonglong *first_value,
                                 ulonglong *nb_reserved_values)
{
  ulonglong nr;
  int error;
  MY_BITMAP *old_read_set;
  bool rnd_inited= (inited ==  RND);

  if (rnd_inited && ha_rnd_end())
    return;

  old_read_set= table->prepare_for_keyread(table->s->next_number_index);

  if (ha_index_init(table->s->next_number_index, 1))
  {

    DBUG_ASSERT(0);
    (void) extra(HA_EXTRA_NO_KEYREAD);
    *first_value= ULONGLONG_MAX;
    if (rnd_inited && ha_rnd_init_with_error(0))
    {

    }
    return;
  }

  if (table->s->next_number_keypart == 0)
  {
    error= ha_index_last(table->record[1]);


    *nb_reserved_values= ULONGLONG_MAX;
  }
  else
  {
    uchar key[MAX_KEY_LENGTH];
    key_copy(key, table->record[0],
             table->key_info + table->s->next_number_index,
             table->s->next_number_key_offset);
    error= ha_index_read_map(table->record[1], key,
                             make_prev_keypart_map(table->s->
                                                   next_number_keypart),
                             HA_READ_PREFIX_LAST);


    *nb_reserved_values= 1;
  }

  if (unlikely(error))
  {
    if (error == HA_ERR_END_OF_FILE || error == HA_ERR_KEY_NOT_FOUND)
      ;
    else
      print_error(error, MYF(0));
    nr= 1;
  }
  else
    nr= ((ulonglong) table->next_number_field->
         val_int_offset(table->s->rec_buff_length)+1);
  ha_index_end();
  table->restore_column_maps_after_keyread(old_read_set);
  *first_value= nr;
  if (rnd_inited && ha_rnd_init_with_error(0))
  {

  }
  return;
}
