bool Ordered_key::next_same()
{
  DBUG_ASSERT(key_buff_elements);

  if (cur_key_idx < key_buff_elements - 1)
  {


    if (!cmp_keys_by_row_data(key_buff[cur_key_idx], key_buff[cur_key_idx + 1]))
    {
      ++cur_key_idx;
      return TRUE;
    }
  }
  return FALSE;
}
