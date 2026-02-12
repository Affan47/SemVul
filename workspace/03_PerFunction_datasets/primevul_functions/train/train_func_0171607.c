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
  THD* thd= join ? join->thd : table->in_use;

  Json_writer_object trace_wrapper(thd);
  Json_writer_object trace_cheaper_ordering(
      thd, "reconsidering_access_paths_for_index_ordering");
  trace_cheaper_ordering.add("clause", group ? "GROUP BY" : "ORDER BY");


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
    {
      fanout*= join->best_positions[i].records_read;

      fanout*= join->best_positions[i].cond_selectivity;
    }
  }
  else
    read_time= table->file->scan_time();

  trace_cheaper_ordering.add("fanout", fanout);


  read_time += COST_EPS;
  trace_cheaper_ordering.add("read_time", read_time);


  if (ref_key >= 0 && ref_key != MAX_KEY && tab->type == JT_REF)
  {


    if (tab->ref.const_ref_part_map ==
        make_prev_keypart_map(tab->ref.key_parts) &&
        table->quick_keys.is_set(ref_key) &&
        table->quick_key_parts[ref_key] == tab->ref.key_parts)
      refkey_rows_estimate= table->quick_rows[ref_key];
    else
    {
      const KEY *ref_keyinfo= table->key_info + ref_key;
      refkey_rows_estimate= ref_keyinfo->rec_per_key[tab->ref.key_parts - 1];
    }
    set_if_bigger(refkey_rows_estimate, 1);
  }

  if (tab)
    trace_cheaper_ordering.add_table_name(tab);
  else
    trace_cheaper_ordering.add_table_name(table);
  trace_cheaper_ordering.add("rows_estimation", refkey_rows_estimate);

  Json_writer_array possible_keys(thd,"possible_keys");
  for (nr=0; nr < table->s->keys ; nr++)
  {
    int direction;
    ha_rows select_limit= select_limit_arg;
    uint used_key_parts= 0;
    Json_writer_object possible_key(thd);
    possible_key.add("index", table->key_info[nr].name);

    if (keys.is_set(nr) &&
        (direction= test_if_order_by_key(join, order, table, nr,
                                         &used_key_parts)))
    {


      DBUG_ASSERT (ref_key != (int) nr);

      possible_key.add("can_resolve_order", true);
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


        {


          refkey_rows_estimate= MY_MIN(refkey_rows_estimate,
                                       ha_rows(table_records *
                                               table->cond_selectivity));
        }


        if (select_limit > refkey_rows_estimate)
          select_limit= table_records;
        else
          select_limit= (ha_rows) (select_limit *
                                   (double) table_records /
                                    refkey_rows_estimate);
        possible_key.add("updated_limit", select_limit);
        rec_per_key= keyinfo->actual_rec_per_key(keyinfo->user_defined_key_parts-1);
        set_if_bigger(rec_per_key, 1);


        index_scan_time= select_limit/rec_per_key *
                         MY_MIN(rec_per_key, table->file->scan_time());
        double range_scan_time;
        if (get_range_limit_read_cost(tab, table, table_records, nr,
                                      select_limit, &range_scan_time))
        {
          possible_key.add("range_scan_time", range_scan_time);
          if (range_scan_time < index_scan_time)
            index_scan_time= range_scan_time;
        }
        possible_key.add("index_scan_time", index_scan_time);

        if ((ref_key < 0 && (group || table->force_index || is_covering)) ||
            index_scan_time < read_time)
        {
          ha_rows quick_records= table_records;
          ha_rows refkey_select_limit= (ref_key >= 0 &&
                                        !is_hash_join_key_no(ref_key) &&
                                        table->covering_keys.is_set(ref_key)) ?
                                        refkey_rows_estimate :
                                        HA_POS_ERROR;
          if (is_best_covering && !is_covering)
          {
            possible_key.add("chosen", false);
            possible_key.add("cause", "covering index already found");
            continue;
          }

          if (is_covering && refkey_select_limit < select_limit)
          {
            possible_key.add("chosen", false);
            possible_key.add("cause", "ref estimates better");
            continue;
          }
          if (table->quick_keys.is_set(nr))
            quick_records= table->quick_rows[nr];
          possible_key.add("records", quick_records);
          if (best_key < 0 ||
              (select_limit <= MY_MIN(quick_records,best_records) ?
               keyinfo->user_defined_key_parts < best_key_parts :
               quick_records < best_records) ||
              (!is_best_covering && is_covering))
          {
            possible_key.add("chosen", true);
            best_key= nr;
            best_key_parts= keyinfo->user_defined_key_parts;
            if (saved_best_key_parts)
              *saved_best_key_parts= used_key_parts;
            best_records= quick_records;
            is_best_covering= is_covering;
            best_key_direction= direction;
            best_select_limit= select_limit;
          }
          else
          {
            char const *cause;
            possible_key.add("chosen", false);
            if (is_covering)
              cause= "covering index already found";
            else
            {
              if (select_limit <= MY_MIN(quick_records,best_records))
                cause= "keyparts greater than the current best keyparts";
              else
                cause= "rows estimation greater";
            }
            possible_key.add("cause", cause);
          }
        }
        else
        {
          possible_key.add("usable", false);
          possible_key.add("cause", "cost");
        }
      }
      else
      {
        possible_key.add("usable", false);
        if (!group && select_limit == HA_POS_ERROR)
          possible_key.add("cause", "order by without limit");
      }
    }
    else
    {
      if (keys.is_set(nr))
      {
        possible_key.add("can_resolve_order", false);
        possible_key.add("cause", "order can not be resolved by key");
      }
      else
      {
        possible_key.add("can_resolve_order", false);
        possible_key.add("cause", "not usable index for the query");
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
