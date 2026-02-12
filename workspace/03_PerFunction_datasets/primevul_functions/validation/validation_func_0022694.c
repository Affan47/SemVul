ha_rows JOIN_TAB::get_examined_rows()
{
  double examined_rows;
  SQL_SELECT *sel= filesort? filesort->select : this->select;

  if (sel && sel->quick && use_quick != 2)
    examined_rows= (double)sel->quick->records;
  else if (type == JT_NEXT || type == JT_ALL ||
           type == JT_HASH || type ==JT_HASH_NEXT)
  {
    if (limit)
    {


      examined_rows= (double)limit;
    }
    else
    {
      if (table->is_filled_at_execution())
        examined_rows= (double)records;
      else
      {


        examined_rows= (double)table->stat_records();
      }
    }
  }
  else
    examined_rows= records_read;

  if (examined_rows >= (double) HA_ROWS_MAX)
    return HA_ROWS_MAX;
  return (ha_rows) examined_rows;
}
