test_if_skip_sort_order(JOIN_TAB *tab,ORDER *order,ha_rows select_limit,
			bool no_changes, const key_map *map)
{
  int ref_key;
  uint UNINIT_VAR(ref_key_parts);
  int order_direction= 0;
  uint used_key_parts= 0;
  TABLE *table=tab->table;
  SQL_SELECT *select=tab->select;
  key_map usable_keys;
  QUICK_SELECT_I *save_quick= select ? select->quick : 0;
  Item *orig_cond= 0;
  bool orig_cond_saved= false;
  int best_key= -1;
  bool changed_key= false;
  DBUG_ENTER("test_if_skip_sort_order");


  DBUG_ASSERT(tab == tab->join->join_tab + tab->join->const_tables);


  usable_keys= *map;


  for (ORDER *tmp_order=order; tmp_order ; tmp_order=tmp_order->next)
  {
    Item *item= (*tmp_order->item)->real_item();
    if (item->type() != Item::FIELD_ITEM)
    {
      usable_keys.clear_all();
      DBUG_RETURN(0);
    }


    key_map col_keys;
    compute_part_of_sort_key_for_equals(tab->join, table, (Item_field*)item,
                                        &col_keys);
    usable_keys.intersect(col_keys);
    if (usable_keys.is_clear_all())
      goto use_filesort;
  }

  ref_key= -1;

  if (tab->ref.key >= 0 && tab->ref.key_parts)
  {
    ref_key=	   tab->ref.key;
    ref_key_parts= tab->ref.key_parts;


    if (tab->type == JT_REF_OR_NULL || tab->type == JT_FT ||
        tab->ref.uses_splitting)
      goto use_filesort;
  }
  else if (select && select->quick)
  {
    int quick_type= select->quick->get_type();


    if (quick_type == QUICK_SELECT_I::QS_TYPE_INDEX_MERGE ||
        quick_type == QUICK_SELECT_I::QS_TYPE_INDEX_INTERSECT ||
        quick_type == QUICK_SELECT_I::QS_TYPE_ROR_UNION ||
        quick_type == QUICK_SELECT_I::QS_TYPE_ROR_INTERSECT)
    {


      ref_key= MAX_KEY;
    }
    else
    {
      ref_key= select->quick->index;
      ref_key_parts= select->quick->used_key_parts;
    }
  }

  if (ref_key >= 0 && ref_key != MAX_KEY)
  {

    if (!usable_keys.is_set(ref_key))
    {

      uint new_ref_key;


      if (table->covering_keys.is_set(ref_key))
	usable_keys.intersect(table->covering_keys);
      if (tab->pre_idx_push_select_cond)
      {
        orig_cond= tab->set_cond(tab->pre_idx_push_select_cond);
        orig_cond_saved= true;
      }

      if ((new_ref_key= test_if_subkey(order, table, ref_key, ref_key_parts,
				       &usable_keys)) < MAX_KEY)
      {


        if ((table->quick_keys.is_set(new_ref_key) &&
             table->quick_key_parts[new_ref_key] > ref_key_parts) ||
             !(tab->ref.key >= 0))
	{


          key_map new_ref_key_map;
          COND *save_cond;
          bool res;
          new_ref_key_map.clear_all();
          new_ref_key_map.set_bit(new_ref_key);


          select->quick= 0;
          save_cond= select->cond;
          if (select->pre_idx_push_select_cond)
            select->cond= select->pre_idx_push_select_cond;
          res= select->test_quick_select(tab->join->thd, new_ref_key_map, 0,
                                         (tab->join->select_options &
                                          OPTION_FOUND_ROWS) ?
                                          HA_POS_ERROR :
                                          tab->join->unit->select_limit_cnt,TRUE,
                                         TRUE, FALSE, FALSE) <= 0;
          if (res)
          {
            select->cond= save_cond;
            goto use_filesort;
          }
          DBUG_ASSERT(tab->select->quick);
          tab->type= JT_ALL;
          tab->ref.key= -1;
          tab->ref.key_parts= 0;
          tab->use_quick= 1;
          best_key= new_ref_key;


	}
        else
	{


          KEYUSE *keyuse= tab->keyuse;
          while (keyuse->key != new_ref_key && keyuse->table == tab->table)
            keyuse++;
          if (create_ref_for_key(tab->join, tab, keyuse, FALSE,
                                 (tab->join->const_table_map |
                                  OUTER_REF_TABLE_BIT)))
            goto use_filesort;

          pick_table_access_method(tab);
	}

        ref_key= new_ref_key;
        changed_key= true;
     }
    }

    if (usable_keys.is_set(ref_key) &&
        (order_direction= test_if_order_by_key(tab->join, order,table,ref_key,
					       &used_key_parts)))
      goto check_reverse_order;
  }
  {
    uint UNINIT_VAR(best_key_parts);
    uint saved_best_key_parts= 0;
    int best_key_direction= 0;
    JOIN *join= tab->join;
    ha_rows table_records= table->stat_records();

    test_if_cheaper_ordering(tab, order, table, usable_keys,
                             ref_key, select_limit,
                             &best_key, &best_key_direction,
                             &select_limit, &best_key_parts,
                             &saved_best_key_parts);


    if (best_key < 0 ||
        ((select_limit >= table_records) &&
         (tab->type == JT_ALL &&
         tab->join->table_count > tab->join->const_tables + 1) &&
         !(table->file->index_flags(best_key, 0, 1) & HA_CLUSTERED_INDEX)))
      goto use_filesort;

    if (select &&
        table->quick_keys.is_set(best_key) && best_key != ref_key)
    {
      key_map tmp_map;
      tmp_map.clear_all();
      tmp_map.set_bit(best_key);
      select->quick= 0;

      bool cond_saved= false;
      Item *saved_cond;


      if (select->pre_idx_push_select_cond)
      {
        saved_cond= select->cond;
        select->cond= select->pre_idx_push_select_cond;
        cond_saved= true;
      }

      select->test_quick_select(join->thd, tmp_map, 0,
                                join->select_options & OPTION_FOUND_ROWS ?
                                HA_POS_ERROR :
                                join->unit->select_limit_cnt,
                                TRUE, FALSE, FALSE, FALSE);

      if (cond_saved)
        select->cond= saved_cond;
    }
    order_direction= best_key_direction;


    used_key_parts= (order_direction == -1) ?
      saved_best_key_parts :  best_key_parts;
    changed_key= true;
  }

check_reverse_order:
  DBUG_ASSERT(order_direction != 0);

  if (order_direction == -1)
  {
    int quick_type;
    if (select && select->quick)
    {


      if (select->quick->reverse_sorted())
        goto skipped_filesort;

      quick_type= select->quick->get_type();
      if (quick_type == QUICK_SELECT_I::QS_TYPE_INDEX_MERGE ||
          quick_type == QUICK_SELECT_I::QS_TYPE_INDEX_INTERSECT ||
          quick_type == QUICK_SELECT_I::QS_TYPE_ROR_INTERSECT ||
          quick_type == QUICK_SELECT_I::QS_TYPE_ROR_UNION ||
          quick_type == QUICK_SELECT_I::QS_TYPE_GROUP_MIN_MAX)
      {
        tab->limit= 0;
        goto use_filesort;
      }
    }
  }


  if (!no_changes)
  {
    if (best_key >= 0)
    {
      bool quick_created=
        (select && select->quick && select->quick!=save_quick);


      if (table->covering_keys.is_set(best_key))
        table->file->ha_start_keyread(best_key);
      else
        table->file->ha_end_keyread();

      if (!quick_created)
      {
        if (select)
          select->quick= 0;

        tab->index= best_key;
        tab->read_first_record= order_direction > 0 ?
                                join_read_first:join_read_last;
        tab->type=JT_NEXT;


        if (tab->rowid_filter &&
            tab->index == table->s->primary_key &&
            table->file->primary_key_is_clustered())
	{
          tab->range_rowid_filter_info= 0;
          delete tab->rowid_filter;
          tab->rowid_filter= 0;
        }

        if (tab->pre_idx_push_select_cond)
        {
          tab->set_cond(tab->pre_idx_push_select_cond);


          orig_cond= 0;
          orig_cond_saved= false;
        }

        table->file->ha_index_or_rnd_end();
        if (tab->join->select_options & SELECT_DESCRIBE)
        {
          tab->ref.key= -1;
          tab->ref.key_parts= 0;
          if (select_limit < table->stat_records())
            tab->limit= select_limit;
          table->file->ha_end_keyread();
        }
      }
      else if (tab->type != JT_ALL || tab->select->quick)
      {


        DBUG_ASSERT(tab->select->quick);
        tab->type=JT_ALL;
        tab->use_quick=1;
        tab->ref.key= -1;
        tab->ref.key_parts=0;
        tab->range_rowid_filter_info= 0;
        if (tab->rowid_filter)
	{
          delete tab->rowid_filter;
          tab->rowid_filter= 0;
        }
        tab->read_first_record= join_init_read_record;
        if (tab->is_using_loose_index_scan())
          tab->join->tmp_table_param.precomputed_group_by= TRUE;


        if (tab->select && tab->select->pre_idx_push_select_cond)
	{
          tab->set_cond(tab->select->pre_idx_push_select_cond);
           tab->table->file->cancel_pushed_idx_cond();
        }


      }
    }

    if (order_direction == -1)
    {
      if (select && select->quick)
      {

        QUICK_SELECT_I *tmp= select->quick->make_reverse(used_key_parts);
        if (!tmp)
        {
          tab->limit= 0;
          goto use_filesort;
        }


        if (tab->select && tab->select->pre_idx_push_select_cond)
	{
          tab->set_cond(tab->select->pre_idx_push_select_cond);
           tab->table->file->cancel_pushed_idx_cond();
        }
        if (select->quick == save_quick)
          save_quick= 0;
        select->set_quick(tmp);

        if (tab->use_quick == 2)
        {
          tab->use_quick= 1;
          tab->read_first_record= join_init_read_record;
        }
      }
      else if (tab->type != JT_NEXT && tab->type != JT_REF_OR_NULL &&
               tab->ref.key >= 0 && tab->ref.key_parts <= used_key_parts)
      {


        tab->read_first_record= join_read_last_key;
        tab->read_record.read_record_func= join_read_prev_same;

        if (tab->use_quick == 2)
        {
          tab->use_quick= 1;
          tab->read_first_record= join_init_read_record;
        }


        if (tab->select && tab->select->pre_idx_push_select_cond)
	{
          tab->set_cond(tab->select->pre_idx_push_select_cond);
           tab->table->file->cancel_pushed_idx_cond();
        }
      }
    }
    else if (select && select->quick)
    {

      if (tab->use_quick == 2)
      {
        tab->use_quick= 1;
        tab->read_first_record= join_init_read_record;
      }
      select->quick->need_sorted_output();
    }

    tab->read_record.unlock_row= (tab->type == JT_EQ_REF) ?
                                 join_read_key_unlock_row : rr_unlock_row;

  }


skipped_filesort:

  if (select && save_quick != select->quick)
  {
    delete save_quick;
    save_quick= NULL;
  }
  if (orig_cond_saved && !changed_key)
    tab->set_cond(orig_cond);
  if (!no_changes && changed_key && table->file->pushed_idx_cond)
    table->file->cancel_pushed_idx_cond();

  DBUG_RETURN(1);

use_filesort:

  if (select && select->quick != save_quick)
  {
    delete select->quick;
    select->quick= save_quick;
  }
  if (orig_cond_saved)
    tab->set_cond(orig_cond);

  DBUG_RETURN(0);
}
