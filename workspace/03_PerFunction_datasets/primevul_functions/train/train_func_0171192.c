bool subselect_rowid_merge_engine::partial_match()
{
  Ordered_key *min_key;
  rownum_t min_row_num;
  Ordered_key *cur_key;
  rownum_t cur_row_num;
  uint count_nulls_in_search_key= 0;
  uint max_null_in_any_row=
    ((select_materialize_with_stats *) result)->get_max_nulls_in_row();
  bool res= FALSE;


  DBUG_ASSERT(!non_null_key || (non_null_key && merge_keys[0] == non_null_key));

  DBUG_ASSERT(!pq.elements);


  if (tmp_table->file->ha_rnd_init_with_error(0))
  {
    res= FALSE;
    goto end;
  }


  if (non_null_key && !non_null_key->lookup())
  {
    res= FALSE;
    goto end;
  }


  if (has_covering_null_columns)
  {
    res= TRUE;
    goto end;
  }

  if (non_null_key)
    queue_insert(&pq, (uchar *) non_null_key);


  bitmap_clear_all(&matching_outer_cols);
  for (uint i= MY_TEST(non_null_key); i < merge_keys_count; i++)
  {
    DBUG_ASSERT(merge_keys[i]->get_column_count() == 1);
    if (merge_keys[i]->get_search_key(0)->null_value)
    {
      ++count_nulls_in_search_key;
      bitmap_set_bit(&matching_outer_cols, merge_keys[i]->get_keyid());
    }
    else if (merge_keys[i]->lookup())
      queue_insert(&pq, (uchar *) merge_keys[i]);
  }


  if (count_nulls_in_search_key == merge_keys_count - MY_TEST(non_null_key))
  {
    res= TRUE;
    goto end;
  }


  if (count_nulls_in_search_key && !pq.elements)
  {
    DBUG_ASSERT(!non_null_key);


    res= exists_complementing_null_row(&matching_outer_cols);
    goto end;
  }


  if (!count_nulls_in_search_key &&
      (!pq.elements ||
       (pq.elements == 1 && non_null_key &&
        max_null_in_any_row < merge_keys_count-1)))
  {
    if (!pq.elements)
    {
      DBUG_ASSERT(!non_null_key);


      DBUG_ASSERT(max_null_in_any_row != tmp_table->s->fields);
    }
    res= FALSE;
    goto end;
  }

  DBUG_ASSERT(pq.elements);

  min_key= (Ordered_key*) queue_remove_top(&pq);
  min_row_num= min_key->current();
  bitmap_set_bit(&matching_keys, min_key->get_keyid());
  bitmap_union(&matching_keys, &matching_outer_cols);
  if (min_key->next_same())
    queue_insert(&pq, (uchar *) min_key);

  if (pq.elements == 0)
  {


    res= test_null_row(min_row_num);
    goto end;
  }

  while (TRUE)
  {
    cur_key= (Ordered_key*) queue_remove_top(&pq);
    cur_row_num= cur_key->current();

    if (cur_row_num == min_row_num)
      bitmap_set_bit(&matching_keys, cur_key->get_keyid());
    else
    {

      DBUG_ASSERT(cur_row_num > min_row_num);
      if (test_null_row(min_row_num))
      {
        res= TRUE;
        goto end;
      }
      else
      {
        min_key= cur_key;
        min_row_num= cur_row_num;
        bitmap_clear_all(&matching_keys);
        bitmap_set_bit(&matching_keys, min_key->get_keyid());
        bitmap_union(&matching_keys, &matching_outer_cols);
      }
    }

    if (cur_key->next_same())
      queue_insert(&pq, (uchar *) cur_key);

    if (pq.elements == 0)
    {

      res= test_null_row(min_row_num);
      goto end;
    }
  }


  DBUG_ASSERT(FALSE);

end:
  if (!has_covering_null_columns)
    bitmap_clear_all(&matching_keys);
  queue_remove_all(&pq);
  tmp_table->file->ha_rnd_end();
  return res;
}
