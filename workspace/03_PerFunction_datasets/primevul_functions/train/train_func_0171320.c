int subselect_hash_sj_engine::exec()
{
  Item_in_subselect *item_in= (Item_in_subselect *) item;
  SELECT_LEX *save_select= thd->lex->current_select;
  subselect_partial_match_engine *pm_engine= NULL;
  int res= 0;

  DBUG_ENTER("subselect_hash_sj_engine::exec");


  thd->lex->current_select= materialize_engine->select_lex;

  DBUG_ASSERT(materialize_join->optimization_state == JOIN::OPTIMIZATION_DONE &&
              !is_materialized);
  materialize_join->exec();
  if ((res= MY_TEST(materialize_join->error || thd->is_fatal_error ||
                    thd->is_error())))
    goto err;


  is_materialized= TRUE;


  tmp_table->file->info(HA_STATUS_VARIABLE);
  if (!tmp_table->file->stats.records)
  {

    item_in->reset();
    item_in->make_const();
    item_in->set_first_execution();
    thd->lex->current_select= save_select;
    DBUG_RETURN(FALSE);
  }


  strategy= get_strategy_using_schema();

  strategy= get_strategy_using_data();
  if (strategy == PARTIAL_MATCH)
  {
    uint count_pm_keys;
    MY_BITMAP *nn_key_parts= NULL;
    uint count_non_null_columns= 0;
    bool has_covering_null_row;
    bool has_covering_null_columns;
    select_materialize_with_stats *result_sink=
      (select_materialize_with_stats *) result;
    uint field_count= tmp_table->s->fields;

    if (count_partial_match_columns < field_count)
    {
      nn_key_parts= &non_null_key_parts;
      count_non_null_columns= bitmap_bits_set(nn_key_parts);
    }
    has_covering_null_row= (result_sink->get_max_nulls_in_row() == field_count);
    has_covering_null_columns= (count_non_null_columns +
                                count_null_only_columns == field_count);

    if (has_covering_null_row && has_covering_null_columns)
    {


      DBUG_ASSERT(tmp_table->file->stats.records == 1);
      item_in->value= 0;
      item_in->null_value= 1;
      item_in->make_const();
      item_in->set_first_execution();
      thd->lex->current_select= save_select;
      DBUG_RETURN(FALSE);
    }

    if (has_covering_null_row)
    {
      DBUG_ASSERT(count_partial_match_columns == field_count);
      count_pm_keys= 0;
    }
    else if (has_covering_null_columns)
      count_pm_keys= 1;
    else
      count_pm_keys= count_partial_match_columns - count_null_only_columns +
                     (nn_key_parts ? 1 : 0);

    choose_partial_match_strategy(MY_TEST(nn_key_parts),
                                  has_covering_null_row,
                                  &partial_match_key_parts);
    DBUG_ASSERT(strategy == PARTIAL_MATCH_MERGE ||
                strategy == PARTIAL_MATCH_SCAN);
    if (strategy == PARTIAL_MATCH_MERGE)
    {
      pm_engine=
        new subselect_rowid_merge_engine((subselect_uniquesubquery_engine*)
                                         lookup_engine, tmp_table,
                                         count_pm_keys,
                                         has_covering_null_row,
                                         has_covering_null_columns,
                                         count_columns_with_nulls,
                                         item, result,
                                         semi_join_conds->argument_list());
      if (!pm_engine ||
          pm_engine->prepare(thd) ||
          ((subselect_rowid_merge_engine*) pm_engine)->
            init(nn_key_parts, &partial_match_key_parts))
      {


        delete pm_engine;
        pm_engine= NULL;
        strategy= PARTIAL_MATCH_SCAN;
      }
    }

    if (strategy == PARTIAL_MATCH_SCAN)
    {
      if (!(pm_engine=
            new subselect_table_scan_engine((subselect_uniquesubquery_engine*)
                                            lookup_engine, tmp_table,
                                            item, result,
                                            semi_join_conds->argument_list(),
                                            has_covering_null_row,
                                            has_covering_null_columns,
                                            count_columns_with_nulls)) ||
          pm_engine->prepare(thd))
      {

        res= 1;
        goto err;
      }
    }
  }

  if (pm_engine)
    lookup_engine= pm_engine;
  item_in->change_engine(lookup_engine);

err:
  thd->lex->current_select= save_select;
  DBUG_RETURN(res);
}
