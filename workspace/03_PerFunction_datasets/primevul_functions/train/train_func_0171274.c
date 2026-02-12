double Ordered_key::null_selectivity()
{

  DBUG_ASSERT(tbl->file->stats.records);
  return (1 - (double) null_count / (double) tbl->file->stats.records);
}
