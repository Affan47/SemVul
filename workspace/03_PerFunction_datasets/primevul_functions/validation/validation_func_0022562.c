double matching_candidates_in_table(JOIN_TAB *s, bool with_found_constraint,
                                     uint use_cond_selectivity)
{
  ha_rows records;
  double dbl_records;

  if (use_cond_selectivity > 1)
  {
    TABLE *table= s->table;
    double sel= table->cond_selectivity;
    double table_records= (double)table->stat_records();
    dbl_records= table_records * sel;
    return dbl_records;
  }

  records = s->found_records;


  if (with_found_constraint)
    records-= records/4;


  if (s->table->quick_condition_rows != s->found_records)
    records= s->table->quick_condition_rows;

  dbl_records= (double)records;
  return dbl_records;
}
