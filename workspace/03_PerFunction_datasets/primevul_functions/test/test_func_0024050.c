test_if_cheaper_ordering(const JOIN_TAB *tab, ORDER *order, TABLE *table,
                         key_map usable_keys,  int ref_key,
                         ha_rows select_limit_arg,
                         int *new_key, int *new_key_direction,
                         ha_rows *new_select_limit, uint *new_used_key_parts,
                         uint *saved_best_key_parts)
{
  DBUG_ENTER("test_if_cheaper_ordering");


  ha_rows best_select_limit= HA_POS_ERROR;
  JOIN *join= tab ? tab->join : NULL;
  uint nr;
  key_map keys;
  uint best_key_parts= 0;
  int best_key_direction= 0;
  ha_rows best_records= 0;
  double read_time;
  int best_key= -1;
  bool is_best_covering= FALSE;
  double fanout= 1;
  ha_rows table_records= table->stat_records();
  bool group= join && join->group && order == join->group_list;
  ha_rows refkey_rows_estimate= table->quick_condition_rows;
  const bool has_limit= (select_limit_arg != HA_POS_ERROR);


  if (select_limit_arg >= table_records)
  {
    keys= *table->file->keys_to_use_for_scanning();
    keys.merge(table->covering_keys);


    if (table->force_index)
      keys.merge(group ? table->keys_in_use_for_group_by :
                         table->keys_in_use_for_order_by);
    keys.intersect(usable_keys);
  }
  else
    keys= usable_keys;

  if (join)
  {
    uint tablenr= (uint)(tab - join->join_tab);
    read_time= join->best_positions[tablenr].read_time;
    for (uint i= tablenr+1; i < join->table_count; i++)
      fanout*= join->best_positions[i].records_read;
  }
  else
    read_time= table->file->scan_time();


  read_time += COST_EPS;


  if (ref_key >= 0 && ref_key != MAX_KEY && tab->type == JT_REF)
  {
    if (table->quick_keys.is_set(ref_key))
      refkey_rows_estimate= table->quick_rows[ref_key];
    else
    {
      const KEY *ref_keyinfo= table->key_info + ref_key;
      refkey_rows_estimate= ref_keyinfo->rec_per_key[tab->ref.key_parts - 1];
    }
    set_if_bigger(refkey_rows_estimate, 1);
  }

  for (nr=0; nr < table->s->keys ; nr++)
  {
    int direction;
    ha_rows select_limit= select_limit_arg;
    uint used_key_parts= 0;

    if (keys.is_set(nr) &&
        (direction= test_if_order_by_key(join, order, table, nr,
                                         &used_key_parts)))
    {


      DBUG_ASSERT (ref_key != (int) nr);

      bool is_covering= (table->covering_keys.is_set(nr) ||
                         (table->file->index_flags(nr, 0, 1) &
                          HA_CLUSTERED_INDEX));


      if (is_covering ||
          select_limit != HA_POS_ERROR ||
          (ref_key < 0 && (group || table->force_index)))
      {
        double rec_per_key;
        double index_scan_time;
        KEY *keyinfo= table->key_info+nr;
        if (select_limit == HA_POS_ERROR)
          select_limit= table_records;
        if (group)
        {


          uint used_index_parts= keyinfo->user_defined_key_parts;
          uint used_pk_parts= 0;
          if (used_key_parts > used_index_parts)
            used_pk_parts= used_key_parts-used_index_parts;
          rec_per_key= used_key_parts ?
	               keyinfo->actual_rec_per_key(used_key_parts-1) : 1;

          if (used_pk_parts)
	  {
            KEY *pkinfo=tab->table->key_info+table->s->primary_key;


            if (used_key_parts == pkinfo->user_defined_key_parts ||
                pkinfo->rec_per_key[0] == 0)
              rec_per_key= 1;
            if (rec_per_key > 1)
	    {
              rec_per_key*= pkinfo->actual_rec_per_key(used_pk_parts-1);
              rec_per_key/= pkinfo->actual_rec_per_key(0);


               for(uint i= 1; i < used_pk_parts; i++)
	      {
	        if (pkinfo->key_part[i].field->key_start.is_set(nr))
	        {


                  DBUG_ASSERT(pkinfo->actual_rec_per_key(i));
                  rec_per_key*= pkinfo->actual_rec_per_key(i-1);
                  rec_per_key/= pkinfo->actual_rec_per_key(i);
                }
	      }
            }
          }
          set_if_bigger(rec_per_key, 1);


          if (select_limit > table_records/rec_per_key)
            select_limit= table_records;
          else
            select_limit= (ha_rows) (select_limit*rec_per_key);
        }


        select_limit= (ha_rows) (select_limit < fanout ?
                                 1 : select_limit/fanout);


        if (select_limit > refkey_rows_estimate)
          select_limit= table_records;
        else
          select_limit= (ha_rows) (select_limit *
                                   (double) table_records /
                                    refkey_rows_estimate);
        rec_per_key= keyinfo->actual_rec_per_key(keyinfo->user_defined_key_parts-1);
        set_if_bigger(rec_per_key, 1);


        index_scan_time= select_limit/rec_per_key *
                         MY_MIN(rec_per_key, table->file->scan_time());
        double range_scan_time;
        if (get_range_limit_read_cost(tab, table, nr, select_limit,
                                       &range_scan_time))
        {
          if (range_scan_time < index_scan_time)
            index_scan_time= range_scan_time;
        }

        if ((ref_key < 0 && (group || table->force_index || is_covering)) ||
            index_scan_time < read_time)
        {
          ha_rows quick_records= table_records;
          ha_rows refkey_select_limit= (ref_key >= 0 &&
                                        !is_hash_join_key_no(ref_key) &&
                                        table->covering_keys.is_set(ref_key)) ?
                                        refkey_rows_estimate :
                                        HA_POS_ERROR;
          if ((is_best_covering && !is_covering) ||
              (is_covering && refkey_select_limit < select_limit))
            continue;
          if (table->quick_keys.is_set(nr))
            quick_records= table->quick_rows[nr];
          if (best_key < 0 ||
              (select_limit <= MY_MIN(quick_records,best_records) ?
               keyinfo->user_defined_key_parts < best_key_parts :
               quick_records < best_records) ||
              (!is_best_covering && is_covering))
          {
            best_key= nr;
            best_key_parts= keyinfo->user_defined_key_parts;
            if (saved_best_key_parts)
              *saved_best_key_parts= used_key_parts;
            best_records= quick_records;
            is_best_covering= is_covering;
            best_key_direction= direction;
            best_select_limit= select_limit;
          }
        }
      }
    }
  }

  if (best_key < 0 || best_key == ref_key)
    DBUG_RETURN(FALSE);

  *new_key= best_key;
  *new_key_direction= best_key_direction;
  *new_select_limit= has_limit ? best_select_limit : table_records;
  if (new_used_key_parts != NULL)
    *new_used_key_parts= best_key_parts;

  DBUG_RETURN(TRUE);
}
