Item *ha_maria::idx_cond_push(uint keyno_arg, Item* idx_cond_arg)
{


  const KEY *key= &table_share->key_info[keyno_arg];

  for (uint k= 0; k < key->user_defined_key_parts; ++k)
  {
    const KEY_PART_INFO *key_part= &key->key_part[k];
    if (key_part->key_part_flag & HA_BLOB_PART)
    {

      return idx_cond_arg;
    }
  }

  pushed_idx_cond_keyno= keyno_arg;
  pushed_idx_cond= idx_cond_arg;
  in_range_check_pushed_down= TRUE;
  if (active_index == pushed_idx_cond_keyno)
    ma_set_index_cond_func(file, handler_index_cond_check, this);
  return NULL;
}
