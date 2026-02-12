static bool get_range_limit_read_cost(const JOIN_TAB *tab,
                                      const TABLE *table,
                                      uint keynr,
                                      ha_rows rows_limit,
                                      double *read_time)
{
  bool res= false;


  if (table->quick_keys.is_set(keynr))
  {


    double best_rows= (double)table->quick_rows[keynr];
    double best_cost= (double)table->quick_costs[keynr];


    if (tab)
    {
      key_part_map map= 1;
      uint kp;

      for (kp=0; kp < MAX_REF_PARTS; map=map << 1, kp++)
      {
        if (!(table->const_key_parts[keynr] & map))
          break;
      }

      if (kp > 0)
      {
        ha_rows ref_rows;


        if (kp == table->quick_key_parts[keynr])
          ref_rows= table->quick_rows[keynr];
        else
          ref_rows= (ha_rows) table->key_info[keynr].actual_rec_per_key(kp-1);

        if (ref_rows > 0)
        {
          double tmp= (double)ref_rows;

          set_if_smaller(tmp, (double) tab->join->thd->variables.max_seeks_for_key);
          if (table->covering_keys.is_set(keynr))
            tmp= table->file->keyread_time(keynr, 1, (ha_rows) tmp);
          else
            tmp= table->file->read_time(keynr, 1,
                                        (ha_rows) MY_MIN(tmp,tab->worst_seeks));
          if (tmp < best_cost)
          {
            best_cost= tmp;
            best_rows= (double)ref_rows;
          }
        }
      }
    }

    if (best_rows > rows_limit)
    {


      best_cost *= rows_limit / best_rows;
    }
    *read_time= best_cost;
    res= true;
  }
  return res;
}
