void subselect_hash_sj_engine::cleanup()
{
  enum_engine_type lookup_engine_type= lookup_engine->engine_type();
  is_materialized= FALSE;
  bitmap_clear_all(&non_null_key_parts);
  bitmap_clear_all(&partial_match_key_parts);
  count_partial_match_columns= 0;
  count_null_only_columns= 0;
  strategy= UNDEFINED;
  materialize_engine->cleanup();


  ((Item_in_subselect *) item)->engine= materialize_engine;
  if (lookup_engine_type == TABLE_SCAN_ENGINE ||
      lookup_engine_type == ROWID_MERGE_ENGINE)
  {
    subselect_engine *inner_lookup_engine;
    inner_lookup_engine=
      ((subselect_partial_match_engine*) lookup_engine)->lookup_engine;


    delete lookup_engine;
    lookup_engine= inner_lookup_engine;
  }
  DBUG_ASSERT(lookup_engine->engine_type() == UNIQUESUBQUERY_ENGINE);
  lookup_engine->cleanup();
  result->cleanup();
  DBUG_ASSERT(tmp_table);
  free_tmp_table(thd, tmp_table);
  tmp_table= NULL;
}
