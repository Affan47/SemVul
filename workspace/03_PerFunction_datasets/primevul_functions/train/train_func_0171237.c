subselect_rowid_merge_engine::init(MY_BITMAP *non_null_key_parts,
                                   MY_BITMAP *partial_match_key_parts)
{
  THD *thd= get_thd();

  uint rowid_length= tmp_table->file->ref_length;
  ha_rows row_count= tmp_table->file->stats.records;
  rownum_t cur_rownum= 0;
  select_materialize_with_stats *result_sink=
    (select_materialize_with_stats *) result;
  uint cur_keyid= 0;
  Item_in_subselect *item_in= (Item_in_subselect*) item;
  int error;

  if (merge_keys_count == 0)
  {
    DBUG_ASSERT(bitmap_bits_set(partial_match_key_parts) == 0 ||
                has_covering_null_row);

    return FALSE;
  }


  DBUG_ASSERT(!has_covering_null_columns ||
              (has_covering_null_columns &&
               merge_keys_count == 1 && non_null_key_parts));


  if (!(merge_keys= (Ordered_key**) thd->alloc(merge_keys_count *
                                               sizeof(Ordered_key*))) ||
      !(null_bitmaps= (MY_BITMAP**) thd->alloc(merge_keys_count *
                                               sizeof(MY_BITMAP*))) ||
      !(row_num_to_rowid= (uchar*) my_malloc((size_t)(row_count * rowid_length),
        MYF(MY_WME | MY_THREAD_SPECIFIC))))
    return TRUE;


  if (non_null_key_parts)
  {
    non_null_key= new Ordered_key(cur_keyid, tmp_table, item_in->left_expr,
                                  0, 0, 0, row_num_to_rowid);
    if (non_null_key->init(non_null_key_parts))
      return TRUE;
    merge_keys[cur_keyid]= non_null_key;
    merge_keys[cur_keyid]->first();
    ++cur_keyid;
  }


  if (!has_covering_null_columns)
  {
    if (my_bitmap_init_memroot(&matching_keys, merge_keys_count, thd->mem_root) ||
        my_bitmap_init_memroot(&matching_outer_cols, merge_keys_count, thd->mem_root))
      return TRUE;


    for (uint i= 0; i < partial_match_key_parts->n_bits; i++)
    {

      if (!bitmap_is_set(partial_match_key_parts, i) ||
          result_sink->get_null_count_of_col(i) == row_count)
        continue;

      merge_keys[cur_keyid]= new Ordered_key(
                                     cur_keyid, tmp_table,
                                     item_in->left_expr->element_index(i),
                                     result_sink->get_null_count_of_col(i),
                                     result_sink->get_min_null_of_col(i),
                                     result_sink->get_max_null_of_col(i),
                                     row_num_to_rowid);
      if (merge_keys[cur_keyid]->init(i))
        return TRUE;
      merge_keys[cur_keyid]->first();
      ++cur_keyid;
    }
  }
  DBUG_ASSERT(cur_keyid == merge_keys_count);


  if (tmp_table->file->ha_rnd_init_with_error(1))
    return TRUE;
  tmp_table->file->extra_opt(HA_EXTRA_CACHE,
                             current_thd->variables.read_buff_size);
  tmp_table->null_row= 0;
  while (TRUE)
  {
    error= tmp_table->file->ha_rnd_next(tmp_table->record[0]);
    if (error == HA_ERR_RECORD_DELETED)
    {

      continue;
    }


    DBUG_ASSERT(!error || error == HA_ERR_END_OF_FILE);
    if (error == HA_ERR_END_OF_FILE)
    {
      DBUG_ASSERT(cur_rownum == tmp_table->file->stats.records);
      break;
    }


    tmp_table->file->position(tmp_table->record[0]);
    memcpy(row_num_to_rowid + cur_rownum * rowid_length,
           tmp_table->file->ref, rowid_length);


    if (non_null_key)
    {

      non_null_key->add_key(cur_rownum);
    }

    for (uint i= (non_null_key ? 1 : 0); i < merge_keys_count; i++)
    {


      if (merge_keys[i]->get_field(0)->is_null())
        merge_keys[i]->set_null(cur_rownum);
      else
        merge_keys[i]->add_key(cur_rownum);
    }
    ++cur_rownum;
  }

  tmp_table->file->ha_rnd_end();


  my_qsort(merge_keys, merge_keys_count, sizeof(Ordered_key*),
           (qsort_cmp) cmp_keys_by_null_selectivity);


  for (uint i= 0; i < merge_keys_count; i++)
    if (merge_keys[i]->sort_keys())
      return TRUE;

  if (init_queue(&pq, merge_keys_count, 0, FALSE,
                 subselect_rowid_merge_engine::cmp_keys_by_cur_rownum, NULL,
                 0, 0))
    return TRUE;

  return FALSE;
}
