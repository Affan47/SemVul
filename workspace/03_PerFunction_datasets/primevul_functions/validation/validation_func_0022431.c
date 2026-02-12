make_join_statistics(JOIN *join, List<TABLE_LIST> &tables_list,
                     DYNAMIC_ARRAY *keyuse_array)
{
  int error= 0;
  TABLE *UNINIT_VAR(table);
  uint i,table_count,const_count,key;
  table_map found_const_table_map, all_table_map;
  key_map const_ref, eq_part;
  bool has_expensive_keyparts;
  TABLE **table_vector;
  JOIN_TAB *stat,*stat_end,*s,**stat_ref, **stat_vector;
  KEYUSE *keyuse,*start_keyuse;
  table_map outer_join=0;
  table_map no_rows_const_tables= 0;
  SARGABLE_PARAM *sargables= 0;
  List_iterator<TABLE_LIST> ti(tables_list);
  TABLE_LIST *tables;
  DBUG_ENTER("make_join_statistics");

  table_count=join->table_count;


  if (!multi_alloc_root(join->thd->mem_root,
                        &stat, sizeof(JOIN_TAB)*(table_count),
                        &stat_ref, sizeof(JOIN_TAB*)* MAX_TABLES,
                        &stat_vector, sizeof(JOIN_TAB*)* (table_count +1),
                        &table_vector, sizeof(TABLE*)*(table_count*2),
                        &join->positions, sizeof(POSITION)*(table_count + 1),
                        &join->best_positions,
                        sizeof(POSITION)*(table_count + 1),
                        NullS))
    DBUG_RETURN(1);


  bzero((void*)stat, sizeof(JOIN_TAB)* table_count);

  for (i=0 ; i <= table_count ; i++)
    (void) new ((char*) (join->positions + i)) POSITION;

  join->best_ref= stat_vector;

  stat_end=stat+table_count;
  found_const_table_map= all_table_map=0;
  const_count=0;

  for (s= stat, i= 0; (tables= ti++); s++, i++)
  {
    TABLE_LIST *embedding= tables->embedding;
    stat_vector[i]=s;
    s->keys.init();
    s->const_keys.init();
    s->checked_keys.init();
    s->needed_reg.init();
    table_vector[i]=s->table=table=tables->table;
    s->tab_list= tables;
    table->pos_in_table_list= tables;
    error= tables->fetch_number_of_rows();
    set_statistics_for_table(join->thd, table);
    bitmap_clear_all(&table->cond_set);

#ifdef WITH_PARTITION_STORAGE_ENGINE
    const bool all_partitions_pruned_away= table->all_partitions_pruned_away;
#else
    const bool all_partitions_pruned_away= FALSE;
#endif

    DBUG_EXECUTE_IF("bug11747970_raise_error",
                    { join->thd->set_killed(KILL_QUERY_HARD); });
    if (unlikely(error))
    {
      table->file->print_error(error, MYF(0));
      goto error;
    }
    table->quick_keys.clear_all();
    table->intersect_keys.clear_all();
    table->reginfo.join_tab=s;
    table->reginfo.not_exists_optimize=0;
    bzero((char*) table->const_key_parts, sizeof(key_part_map)*table->s->keys);
    all_table_map|= table->map;
    s->preread_init_done= FALSE;
    s->join=join;

    s->dependent= tables->dep_tables;
    if (tables->schema_table)
      table->file->stats.records= table->used_stat_records= 2;
    table->quick_condition_rows= table->stat_records();

    s->on_expr_ref= &tables->on_expr;
    if (*s->on_expr_ref)
    {

      if (!table->is_filled_at_execution() &&
          ((!table->file->stats.records &&
            (table->file->ha_table_flags() & HA_STATS_RECORDS_IS_EXACT)) ||
           all_partitions_pruned_away) && !embedding)
      {
        s->dependent= 0;
        no_rows_const_tables |= table->map;
	set_position(join,const_count++,s,(KEYUSE*) 0);
	continue;
      }
      outer_join|= table->map;
      s->embedding_map= 0;
      for (;embedding; embedding= embedding->embedding)
        s->embedding_map|= embedding->nested_join->nj_map;
      continue;
    }
    if (embedding)
    {

      s->embedding_map= 0;
      bool inside_an_outer_join= FALSE;
      do
      {


        if (embedding->sj_on_expr)
        {
          embedding= embedding->embedding;
          continue;
        }
        inside_an_outer_join= TRUE;
        NESTED_JOIN *nested_join= embedding->nested_join;
        s->embedding_map|=nested_join->nj_map;
        s->dependent|= embedding->dep_tables;
        embedding= embedding->embedding;
        outer_join|= nested_join->used_tables;
      }
      while (embedding);
      if (inside_an_outer_join)
        continue;
    }
    if (!table->is_filled_at_execution() &&
        (table->s->system ||
         (table->file->stats.records <= 1 &&
          (table->file->ha_table_flags() & HA_STATS_RECORDS_IS_EXACT)) ||
         all_partitions_pruned_away) &&
	!s->dependent &&
        !table->fulltext_searched && !join->no_const_tables)
    {
      set_position(join,const_count++,s,(KEYUSE*) 0);
      no_rows_const_tables |= table->map;
    }


    if (table->pos_in_table_list->jtbm_subselect &&
        table->pos_in_table_list->jtbm_subselect->is_jtbm_const_tab)
    {
      set_position(join,const_count++,s,(KEYUSE*) 0);
      no_rows_const_tables |= table->map;
    }
  }

  stat_vector[i]=0;
  join->outer_join=outer_join;

  if (join->outer_join)
  {


    for (s= stat ; s < stat_end ; s++)
    {
      table= s->table;
      for (JOIN_TAB *t= stat ; t < stat_end ; t++)
      {
        if (t->dependent & table->map)
          t->dependent |= table->reginfo.join_tab->dependent;
      }
      if (outer_join & s->table->map)
        s->table->maybe_null= 1;
    }

    for (i= 0, s= stat ; i < table_count ; i++, s++)
    {
      if (s->dependent & s->table->map)
      {
        join->table_count=0;
        my_message(ER_WRONG_OUTER_JOIN,
                   ER_THD(join->thd, ER_WRONG_OUTER_JOIN), MYF(0));
        goto error;
      }
      s->key_dependent= s->dependent;
    }
  }

  if (join->conds || outer_join)
  {
    if (update_ref_and_keys(join->thd, keyuse_array, stat, join->table_count,
                            join->conds, ~outer_join, join->select_lex, &sargables))
      goto error;


    bool skip_unprefixed_keyparts=
      !(join->is_in_subquery() &&
        ((Item_in_subselect*)join->unit->item)->test_strategy(SUBS_IN_TO_EXISTS));

    if (keyuse_array->elements &&
        sort_and_filter_keyuse(join->thd, keyuse_array,
                               skip_unprefixed_keyparts))
      goto error;
    DBUG_EXECUTE("opt", print_keyuse_array(keyuse_array););
  }

  join->const_table_map= no_rows_const_tables;
  join->const_tables= const_count;
  eliminate_tables(join);
  join->const_table_map &= ~no_rows_const_tables;
  const_count= join->const_tables;
  found_const_table_map= join->const_table_map;


  for (POSITION *p_pos=join->positions, *p_end=p_pos+const_count;
       p_pos < p_end ;
       p_pos++)
  {
    s= p_pos->table;
    if (! (s->table->map & join->eliminated_tables))
    {
      int tmp;
      s->type=JT_SYSTEM;
      join->const_table_map|=s->table->map;
      if ((tmp=join_read_const_table(join->thd, s, p_pos)))
      {
        if (tmp > 0)
          goto error;
      }
      else
      {
        found_const_table_map|= s->table->map;
        s->table->pos_in_table_list->optimized_away= TRUE;
      }
    }
  }


  int ref_changed;
  do
  {
    ref_changed = 0;
  more_const_tables_found:


    for (JOIN_TAB **pos=stat_vector+const_count ; (s= *pos) ; pos++)
    {
      table=s->table;

      if (table->is_filled_at_execution())
        continue;


      if ((keyuse= s->keyuse) && *s->on_expr_ref && !s->embedding_map &&
         !(table->map & join->eliminated_tables))
      {


        while (keyuse->table == table)
        {
          if (!keyuse->is_for_hash_join() &&
              !(keyuse->val->used_tables() & ~join->const_table_map) &&
              keyuse->val->is_null() && keyuse->null_rejecting)
          {
            s->type= JT_CONST;
            s->table->const_table= 1;
            mark_as_null_row(table);
            found_const_table_map|= table->map;
	    join->const_table_map|= table->map;
	    set_position(join,const_count++,s,(KEYUSE*) 0);
            goto more_const_tables_found;
           }
	  keyuse++;
        }
      }

      if (s->dependent)
      {

	if (s->dependent & ~(found_const_table_map))
	  continue;
	if (table->file->stats.records <= 1L &&
	    (table->file->ha_table_flags() & HA_STATS_RECORDS_IS_EXACT) &&
            !table->pos_in_table_list->embedding &&
	      !((outer_join & table->map) &&
		(*s->on_expr_ref)->is_expensive()))
	{
	  int tmp= 0;
	  s->type=JT_SYSTEM;
	  join->const_table_map|=table->map;
	  set_position(join,const_count++,s,(KEYUSE*) 0);
	  if ((tmp= join_read_const_table(join->thd, s, join->positions+const_count-1)))
	  {
	    if (tmp > 0)
	      goto error;
	  }
	  else
	    found_const_table_map|= table->map;
	  continue;
	}
      }

      if ((keyuse=s->keyuse))
      {
	s->type= JT_REF;
	while (keyuse->table == table)
	{
          if (keyuse->is_for_hash_join())
	  {
            keyuse++;
            continue;
          }
	  start_keyuse=keyuse;
	  key=keyuse->key;
	  s->keys.set_bit(key);

          const_ref.clear_all();
	  eq_part.clear_all();
          has_expensive_keyparts= false;
	  do
	  {
            if (keyuse->val->type() != Item::NULL_ITEM &&
                !keyuse->optimize &&
                keyuse->keypart != FT_KEYPART)
	    {
	      if (!((~found_const_table_map) & keyuse->used_tables))
              {
		const_ref.set_bit(keyuse->keypart);
                if (keyuse->val->is_expensive())
                  has_expensive_keyparts= true;
              }
	      eq_part.set_bit(keyuse->keypart);
	    }
	    keyuse++;
	  } while (keyuse->table == table && keyuse->key == key);

          TABLE_LIST *embedding= table->pos_in_table_list->embedding;


          KEY *keyinfo= table->key_info + key;
          uint  key_parts= table->actual_n_key_parts(keyinfo);
          if (eq_part.is_prefix(key_parts) &&
              !table->fulltext_searched &&
              (!embedding || (embedding->sj_on_expr && !embedding->embedding)))
	  {
            key_map base_part, base_const_ref, base_eq_part;
            base_part.set_prefix(keyinfo->user_defined_key_parts);
            base_const_ref= const_ref;
            base_const_ref.intersect(base_part);
            base_eq_part= eq_part;
            base_eq_part.intersect(base_part);
            if (table->actual_key_flags(keyinfo) & HA_NOSAME)
            {

	      if (base_const_ref == base_eq_part &&
                  !has_expensive_keyparts &&
                  !((outer_join & table->map) &&
                    (*s->on_expr_ref)->is_expensive()))
	      {
	        int tmp;
	        ref_changed = 1;
	        s->type= JT_CONST;
	        join->const_table_map|=table->map;
	        set_position(join,const_count++,s,start_keyuse);

	        if (create_ref_for_key(join, s, start_keyuse, FALSE,
				       found_const_table_map))
                  goto error;
	        if ((tmp=join_read_const_table(join->thd, s,
                                               join->positions+const_count-1)))
	        {
		  if (tmp > 0)
		    goto error;
	        }
	        else
		  found_const_table_map|= table->map;
	        break;
	      }
	    }
            else if (base_const_ref == base_eq_part)
              s->const_keys.set_bit(key);
          }
	}
      }
    }
  } while (ref_changed);

  join->sort_by_table= get_sort_by_table(join->order, join->group_list,
                                         join->select_lex->leaf_tables,
                                         join->const_table_map);


  if (const_count && sargables)
  {
    for( ; sargables->field ; sargables++)
    {
      Field *field= sargables->field;
      JOIN_TAB *join_tab= field->table->reginfo.join_tab;
      key_map possible_keys= field->key_start;
      possible_keys.intersect(field->table->keys_in_use_for_query);
      bool is_const= 1;
      for (uint j=0; j < sargables->num_values; j++)
        is_const&= sargables->arg_value[j]->const_item();
      if (is_const)
        join_tab[0].const_keys.merge(possible_keys);
    }
  }

  join->impossible_where= false;
  if (join->conds && const_count)
  {
    Item* &conds= join->conds;
    COND_EQUAL *orig_cond_equal = join->cond_equal;

    conds->update_used_tables();
    conds= conds->remove_eq_conds(join->thd, &join->cond_value, true);
    if (conds && conds->type() == Item::COND_ITEM &&
        ((Item_cond*) conds)->functype() == Item_func::COND_AND_FUNC)
      join->cond_equal= &((Item_cond_and*) conds)->m_cond_equal;
    join->select_lex->where= conds;
    if (join->cond_value == Item::COND_FALSE)
    {
      join->impossible_where= true;
      conds= new (join->thd->mem_root) Item_int(join->thd, (longlong) 0, 1);
    }

    join->cond_equal= NULL;
    if (conds)
    {
      if (conds->type() == Item::COND_ITEM &&
	  ((Item_cond*) conds)->functype() == Item_func::COND_AND_FUNC)
        join->cond_equal= (&((Item_cond_and *) conds)->m_cond_equal);
      else if (conds->type() == Item::FUNC_ITEM &&
	       ((Item_func*) conds)->functype() == Item_func::MULT_EQUAL_FUNC)
      {
        if (!join->cond_equal)
          join->cond_equal= new COND_EQUAL;
        join->cond_equal->current_level.empty();
        join->cond_equal->current_level.push_back((Item_equal*) conds,
                                                  join->thd->mem_root);
      }
    }

    if (orig_cond_equal != join->cond_equal)
    {


      for (JOIN_TAB **pos=stat_vector+const_count ; (s= *pos) ; pos++)
      {
        if (*s->on_expr_ref && s->cond_equal &&
	    s->cond_equal->upper_levels == orig_cond_equal)
          s->cond_equal->upper_levels= join->cond_equal;
      }
    }
  }


  for (s=stat ; s < stat_end ; s++)
  {
    s->startup_cost= 0;
    if (s->type == JT_SYSTEM || s->type == JT_CONST)
    {

      s->found_records= s->records= 1;
      s->read_time=1.0;
      s->worst_seeks=1.0;
      continue;
    }

    if (s->table->is_filled_at_execution())
    {
      get_delayed_table_estimates(s->table, &s->records, &s->read_time,
                                  &s->startup_cost);
      s->found_records= s->records;
      table->quick_condition_rows=s->records;
    }
    else
    {
       s->scan_time();
    }

    if (s->table->is_splittable())
      s->add_keyuses_for_splitting();


    s->worst_seeks= MY_MIN((double) s->found_records / 10,
			(double) s->read_time*3);
    if (s->worst_seeks < 2.0)
      s->worst_seeks=2.0;


    add_group_and_distinct_keys(join, s);

    s->table->cond_selectivity= 1.0;


    if ((!s->const_keys.is_clear_all() ||
	 !bitmap_is_clear_all(&s->table->cond_set)) &&
        !s->table->is_filled_at_execution() &&
        !(s->table->pos_in_table_list->derived &&
          s->table->pos_in_table_list->is_materialized_derived()))
    {
      bool impossible_range= FALSE;
      ha_rows records= HA_POS_ERROR;
      SQL_SELECT *select= 0;
      Item **sargable_cond= NULL;
      if (!s->const_keys.is_clear_all())
      {
        sargable_cond= get_sargable_cond(join, s->table);

        select= make_select(s->table, found_const_table_map,
			    found_const_table_map,
                            *sargable_cond,
                            (SORT_INFO*) 0,
			    1, &error);
        if (!select)
          goto error;
        records= get_quick_record_count(join->thd, select, s->table,
				        &s->const_keys, join->row_limit);


        *sargable_cond= select->cond;

        s->quick=select->quick;
        s->needed_reg=select->needed_reg;
        select->quick=0;
        impossible_range= records == 0 && s->table->reginfo.impossible_range;
      }
      if (!impossible_range)
      {
        if (!sargable_cond)
          sargable_cond= get_sargable_cond(join, s->table);
        if (join->thd->variables.optimizer_use_condition_selectivity > 1)
          calculate_cond_selectivity_for_table(join->thd, s->table,
                                               sargable_cond);
        if (s->table->reginfo.impossible_range)
	{
          impossible_range= TRUE;
          records= 0;
        }
      }
      if (impossible_range)
      {


        TABLE_LIST *emb= s->table->pos_in_table_list->embedding;
        if (emb && !emb->sj_on_expr)
        {

          mark_join_nest_as_const(join, emb, &found_const_table_map,
                                &const_count);
        }
        else
        {
          join->const_table_map|= s->table->map;
          set_position(join,const_count++,s,(KEYUSE*) 0);
          s->type= JT_CONST;
          s->table->const_table= 1;
          if (*s->on_expr_ref)
          {

            s->info= ET_IMPOSSIBLE_ON_CONDITION;
            found_const_table_map|= s->table->map;
            mark_as_null_row(s->table);
          }
        }
      }
      if (records != HA_POS_ERROR)
      {
	s->found_records=records;
	s->read_time= s->quick ? s->quick->read_time : 0.0;
      }
      if (select)
        delete select;
    }

  }

  if (pull_out_semijoin_tables(join))
    DBUG_RETURN(TRUE);

  join->join_tab=stat;
  join->top_join_tab_count= table_count;
  join->map2table=stat_ref;
  join->table= table_vector;
  join->const_tables=const_count;
  join->found_const_table_map=found_const_table_map;

  if (join->const_tables != join->table_count)
    optimize_keyuse(join, keyuse_array);

  DBUG_ASSERT(!join->conds || !join->cond_equal ||
              !join->cond_equal->current_level.elements ||
              (join->conds->type() == Item::COND_ITEM &&
	       ((Item_cond*) (join->conds))->functype() ==
               Item_func::COND_AND_FUNC &&
               join->cond_equal ==
	       &((Item_cond_and *) (join->conds))->m_cond_equal) ||
              (join->conds->type() == Item::FUNC_ITEM &&
	       ((Item_func*) (join->conds))->functype() ==
               Item_func::MULT_EQUAL_FUNC &&
	       join->cond_equal->current_level.elements == 1 &&
               join->cond_equal->current_level.head() == join->conds));

  if (optimize_semijoin_nests(join, all_table_map))
    DBUG_RETURN(TRUE);

  {
    double records= 1;
    SELECT_LEX_UNIT *unit= join->select_lex->master_unit();


    if (join->const_tables != join->table_count)
    {
      if (choose_plan(join, all_table_map & ~join->const_table_map))
        goto error;

#ifdef HAVE_valgrind


      for (uint k=join->const_tables; k < join->table_count; k++)
        MEM_UNDEFINED(&join->positions[k], sizeof(join->positions[k]));
#endif
    }
    else
    {
      memcpy((uchar*) join->best_positions,(uchar*) join->positions,
	     sizeof(POSITION)*join->const_tables);
      join->join_record_count= 1.0;
      join->best_read=1.0;
    }

    if (!(join->select_options & SELECT_DESCRIBE) &&
        unit->derived && unit->derived->is_materialized_derived())
    {


      for (i= 0; i < join->table_count ; i++)
        if (double rr= join->best_positions[i].records_read)
          records= COST_MULT(records, rr);
      ha_rows rows= records > (double) HA_ROWS_MAX ? HA_ROWS_MAX : (ha_rows) records;
      set_if_smaller(rows, unit->select_limit_cnt);
      join->select_lex->increase_derived_records(rows);
    }
  }

  if (join->choose_subquery_plan(all_table_map & ~join->const_table_map))
    goto error;

  DEBUG_SYNC(join->thd, "inside_make_join_statistics");

  DBUG_RETURN(0);

error:


  {
    TABLE_LIST *tmp_table;
    List_iterator<TABLE_LIST> ti2(tables_list);
    while ((tmp_table= ti2++))
      tmp_table->table->reginfo.join_tab= NULL;
  }
  DBUG_RETURN (1);
}
