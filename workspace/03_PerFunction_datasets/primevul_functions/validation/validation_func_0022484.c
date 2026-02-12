bool instantiate_tmp_table(TABLE *table, KEY *keyinfo,
                           TMP_ENGINE_COLUMNDEF *start_recinfo,
                           TMP_ENGINE_COLUMNDEF **recinfo,
                           ulonglong options)
{
  if (table->s->db_type() == TMP_ENGINE_HTON)
  {


    MEM_CHECK_DEFINED(table->record[0], table->s->reclength);
    if (create_internal_tmp_table(table, keyinfo, start_recinfo, recinfo,
                                  options))
      return TRUE;
    MEM_CHECK_DEFINED(table->record[0], table->s->reclength);
  }
  if (open_tmp_table(table))
    return TRUE;

  return FALSE;
}
