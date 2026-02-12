my_bool ha_maria::register_query_cache_table(THD *thd, const char *table_name,
					     uint table_name_len,
					     qc_engine_callback
					     *engine_callback,
					     ulonglong *engine_data)
{
  ulonglong actual_data_file_length;
  ulonglong current_data_file_length;
  DBUG_ENTER("ha_maria::register_query_cache_table");


  *engine_callback= 0;


  *engine_data= 0;

  if (file->s->now_transactional && file->s->have_versioning)
    DBUG_RETURN(file->trn->trid >= file->s->state.last_change_trn);


  actual_data_file_length= file->s->state.state.data_file_length;
  current_data_file_length= file->state->data_file_length;


  DBUG_RETURN(!(file->s->non_transactional_concurrent_insert &&
                current_data_file_length != actual_data_file_length));
}
