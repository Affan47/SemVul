bool subselect_hash_sj_engine::init(List<Item> *tmp_columns, uint subquery_id)
{
  THD *thd= get_thd();
  select_union *result_sink;

  ulonglong tmp_create_options= thd->variables.option_bits | TMP_TABLE_ALL_COLUMNS;


  DBUG_ENTER("subselect_hash_sj_engine::init");

  if (my_bitmap_init_memroot(&non_null_key_parts, tmp_columns->elements,
                            thd->mem_root) ||
      my_bitmap_init_memroot(&partial_match_key_parts, tmp_columns->elements,
                            thd->mem_root))
    DBUG_RETURN(TRUE);


  if (!(result_sink= new (thd->mem_root) select_materialize_with_stats(thd)))
    DBUG_RETURN(TRUE);

  char buf[32];
  uint len= my_snprintf(buf, sizeof(buf), "<subquery%d>", subquery_id);
  char *name;
  if (!(name= (char*)thd->alloc(len + 1)))
    DBUG_RETURN(TRUE);
  memcpy(name, buf, len+1);

  result_sink->get_tmp_table_param()->materialized_subquery= true;
  if (item->substype() == Item_subselect::IN_SUBS &&
      ((Item_in_subselect*)item)->is_jtbm_merged)
  {
    result_sink->get_tmp_table_param()->force_not_null_cols= true;
  }
  if (result_sink->create_result_table(thd, tmp_columns, TRUE,
                                       tmp_create_options,
				       name, TRUE, TRUE))
    DBUG_RETURN(TRUE);

  tmp_table= result_sink->table;
  result= result_sink;


  if (tmp_table->s->keys == 0)
  {

    DBUG_ASSERT(0);
    DBUG_ASSERT(
      tmp_table->s->uniques ||
      tmp_table->key_info->key_length >= tmp_table->file->max_key_length() ||
      tmp_table->key_info->user_defined_key_parts >
      tmp_table->file->max_key_parts());
    free_tmp_table(thd, tmp_table);
    tmp_table= NULL;
    delete result;
    result= NULL;
    DBUG_RETURN(TRUE);
  }


  DBUG_ASSERT(tmp_table->s->keys == 1 &&
              ((Item_in_subselect *) item)->left_expr->cols() ==
              tmp_table->key_info->user_defined_key_parts);

  if (make_semi_join_conds() ||

      !(lookup_engine= make_unique_engine()))
    DBUG_RETURN(TRUE);


  if (semi_join_conds && !semi_join_conds->fixed &&
      semi_join_conds->fix_fields(thd, (Item**)&semi_join_conds))
    DBUG_RETURN(TRUE);

  materialize_join= materialize_engine->join;
  materialize_join->change_result(result, NULL);

  DBUG_RETURN(FALSE);
}
