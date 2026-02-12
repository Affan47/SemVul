prev_record_reads(const POSITION *positions, uint idx, table_map found_ref)
{
  double found=1.0;
  const POSITION *pos_end= positions - 1;
  for (const POSITION *pos= positions + idx - 1; pos != pos_end; pos--)
  {
    if (pos->table->table->map & found_ref)
    {
      found_ref|= pos->ref_depend_map;


      if (pos->records_read)
      {
        found= COST_MULT(found, pos->records_read);
        found*= pos->cond_selectivity;
      }
     }
  }
  return found;
}
