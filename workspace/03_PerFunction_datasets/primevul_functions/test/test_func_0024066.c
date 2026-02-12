make_join_select(JOIN *join,SQL_SELECT *select,COND *cond)
{
  THD *thd= join->thd;
  DBUG_ENTER("make_join_select");
  if (select)
  {
    add_not_null_conds(join);
    table_map used_tables;


    if (cond)
    {
      if (join->table_count > 1)
        cond->update_used_tables();


      {
        join->exec_const_cond=
	  make_cond_for_table(thd, cond,
                              join->const_table_map,
                              (table_map) 0, -1, FALSE, FALSE);

        for (uint i= 0 ; i < join->const_tables ; i++)
          add_cond_and_fix(thd, &join->exec_const_cond,
                           join->join_tab[i].select_cond);

        DBUG_EXECUTE("where",print_where(join->exec_const_cond,"constants",
					 QT_ORDINARY););
        if (join->exec_const_cond && !join->exec_const_cond->is_expensive() &&
            !join->exec_const_cond->val_int())
        {
          DBUG_PRINT("info",("Found impossible WHERE condition"));
          join->exec_const_cond= NULL;
          DBUG_RETURN(1);
        }

        if (join->table_count != join->const_tables)
        {
          COND *outer_ref_cond= make_cond_for_table(thd, cond,
                                                    join->const_table_map |
                                                    OUTER_REF_TABLE_BIT,
                                                    OUTER_REF_TABLE_BIT,
                                                    -1, FALSE, FALSE);
          if (outer_ref_cond)
          {
            add_cond_and_fix(thd, &outer_ref_cond, join->outer_ref_cond);
            join->outer_ref_cond= outer_ref_cond;
          }
        }
        else
        {
          COND *pseudo_bits_cond=
            make_cond_for_table(thd, cond,
                                join->const_table_map |
                                PSEUDO_TABLE_BITS,
                                PSEUDO_TABLE_BITS,
                                -1, FALSE, FALSE);
          if (pseudo_bits_cond)
          {
            add_cond_and_fix(thd, &pseudo_bits_cond,
                             join->pseudo_bits_cond);
            join->pseudo_bits_cond= pseudo_bits_cond;
          }
        }
      }
    }


    uint i;
    for (i= join->top_join_tab_count - 1; i >= join->const_tables; i--)
    {
      if (!join->join_tab[i].bush_children)
        break;
    }
    uint last_top_base_tab_idx= i;

    table_map save_used_tables= 0;
    used_tables=((select->const_tables=join->const_table_map) |
		 OUTER_REF_TABLE_BIT | RAND_TABLE_BIT);
    JOIN_TAB *tab;
    table_map current_map;
    i= join->const_tables;
    for (tab= first_depth_first_tab(join); tab;
         tab= next_depth_first_tab(join, tab))
    {
      bool is_hj;


      JOIN_TAB *first_inner_tab= tab->first_inner;

      if (!tab->bush_children)
        current_map= tab->table->map;
      else
        current_map= tab->bush_children->start->emb_sj_nest->sj_inner_tables;

      bool use_quick_range=0;
      COND *tmp;


      if (tab->emb_sj_nest && tab->emb_sj_nest->sj_mat_info &&
          tab->emb_sj_nest->sj_mat_info->is_used &&
          !(used_tables & tab->emb_sj_nest->sj_inner_tables))
      {
        save_used_tables= used_tables;
        used_tables= join->const_table_map | OUTER_REF_TABLE_BIT |
                     RAND_TABLE_BIT;
      }

      used_tables|=current_map;

      if (tab->type == JT_REF && tab->quick &&
	  (((uint) tab->ref.key == tab->quick->index &&
	    tab->ref.key_length < tab->quick->max_used_key_length) ||
           (!is_hash_join_key_no(tab->ref.key) &&
            tab->table->intersect_keys.is_set(tab->ref.key))))
      {

	tab->type=JT_ALL;
	use_quick_range=1;
	tab->use_quick=1;
        tab->ref.key= -1;
	tab->ref.key_parts=0;
	join->best_positions[i].records_read= rows2double(tab->quick->records);


        if (i != join->const_tables &&
            join->table_count > join->const_tables + 1 &&
            join->best_positions[i].use_join_buffer)
          join->full_join= 1;
      }

      tmp= NULL;

      if (cond)
      {
        if (tab->bush_children)
        {

          tmp= make_cond_after_sjm(thd, cond, cond, save_used_tables,
                                   used_tables, FALSE);
          used_tables= save_used_tables | used_tables;
          save_used_tables= 0;
        }
        else
        {
          tmp= make_cond_for_table(thd, cond, used_tables, current_map, i,
                                   FALSE, FALSE);
          if (tab == join->join_tab + last_top_base_tab_idx)
          {


            table_map rand_table_bit= (table_map) RAND_TABLE_BIT;
            COND *rand_cond= make_cond_for_table(thd, cond, used_tables,
                                                 rand_table_bit, -1,
                                                 FALSE, FALSE);
            add_cond_and_fix(thd, &tmp, rand_cond);
          }
        }

        if (tab->select_cond)
          add_cond_and_fix(thd, &tmp, tab->select_cond);
      }

      is_hj= (tab->type == JT_REF || tab->type == JT_EQ_REF) &&
             (join->allowed_join_cache_types & JOIN_CACHE_HASHED_BIT) &&
	     ((join->max_allowed_join_cache_level+1)/2 == 2 ||
              ((join->max_allowed_join_cache_level+1)/2 > 2 &&
	       is_hash_join_key_no(tab->ref.key))) &&
              (!tab->emb_sj_nest ||
               join->allowed_semijoin_with_cache) &&
              (!(tab->table->map & join->outer_join) ||
               join->allowed_outer_join_with_cache);

      if (cond && !tmp && tab->quick)
      {
        if (tab->type != JT_ALL && !is_hj)
        {


          delete tab->quick;
          tab->quick= 0;
        }
        else
        {


          DBUG_PRINT("info", ("Item_int"));
          tmp= new (thd->mem_root) Item_int(thd, (longlong) 1, 1);
        }

      }
      if (tmp || !cond || tab->type == JT_REF || tab->type == JT_REF_OR_NULL ||
          tab->type == JT_EQ_REF || first_inner_tab)
      {
        DBUG_EXECUTE("where",print_where(tmp,
                                         tab->table? tab->table->alias.c_ptr() :"sjm-nest",
                                         QT_ORDINARY););
	SQL_SELECT *sel= tab->select= ((SQL_SELECT*)
                                       thd->memdup((uchar*) select,
                                                   sizeof(*select)));
	if (!sel)
	  DBUG_RETURN(1);


        if (cond && tmp)
        {


          COND *tmp_cond;
          if (!(tmp_cond= add_found_match_trig_cond(thd, first_inner_tab, tmp,
                                                    0)))
            DBUG_RETURN(1);
          sel->cond= tmp_cond;
          tab->set_select_cond(tmp_cond, __LINE__);


          if (tab->table)
          {
            tab->table->file->pushed_cond= NULL;
            if ((tab->table->file->ha_table_flags() &
                  HA_CAN_TABLE_CONDITION_PUSHDOWN) &&
                !first_inner_tab)
            {
              COND *push_cond=
              make_cond_for_table(thd, tmp_cond, current_map, current_map,
                                  -1, FALSE, FALSE);
              if (push_cond)
              {

                if (!tab->table->file->cond_push(push_cond))
                  tab->table->file->pushed_cond= push_cond;
              }
            }
          }
        }
        else
        {
          sel->cond= NULL;
          tab->set_select_cond(NULL, __LINE__);
        }

	sel->head=tab->table;
        DBUG_EXECUTE("where",
                     print_where(tmp,
                                 tab->table ? tab->table->alias.c_ptr() :
                                   "(sjm-nest)",
                                 QT_ORDINARY););
	if (tab->quick)
	{


          if ((tab->needed_reg.is_clear_all() && tab->type != JT_EQ_REF &&
              tab->type != JT_FT &&
              ((tab->type != JT_CONST && tab->type != JT_REF) ||
               (uint) tab->ref.key == tab->quick->index)) || is_hj)
          {
            DBUG_ASSERT(tab->quick->is_valid());
	    sel->quick=tab->quick;
	    sel->quick_keys.clear_all();
	    sel->needed_reg.clear_all();
	  }
	  else
	  {
	    delete tab->quick;
	  }
	  tab->quick=0;
	}
	uint ref_key= sel->head? (uint) sel->head->reginfo.join_tab->ref.key+1 : 0;
	if (i == join->const_tables && ref_key)
	{
	  if (!tab->const_keys.is_clear_all() &&
              tab->table->reginfo.impossible_range)
	    DBUG_RETURN(1);
	}
	else if (tab->type == JT_ALL && ! use_quick_range)
	{
	  if (!tab->const_keys.is_clear_all() &&
	      tab->table->reginfo.impossible_range)
	    DBUG_RETURN(1);


	  if (!tab->table->is_filled_at_execution() &&
              !tab->loosescan_match_tab &&
              ((cond && (!tab->keys.is_subset(tab->const_keys) && i > 0)) ||
               (!tab->const_keys.is_clear_all() && i == join->const_tables &&
                join->unit->select_limit_cnt <
                join->best_positions[i].records_read &&
                !(join->select_options & OPTION_FOUND_ROWS))))
	  {

	    COND *orig_cond=sel->cond;
	    sel->cond= and_conds(thd, sel->cond, *tab->on_expr_ref);


	    if (sel->cond && !sel->cond->fixed)
	      sel->cond->quick_fix_field();

	    if (sel->test_quick_select(thd, tab->keys,
				       ((used_tables & ~ current_map) |
                                        OUTER_REF_TABLE_BIT),
				       (join->select_options &
					OPTION_FOUND_ROWS ?
					HA_POS_ERROR :
					join->unit->select_limit_cnt), 0,
                                        FALSE, FALSE) < 0)
            {


              sel->cond=orig_cond;
              if (!*tab->on_expr_ref ||
                  sel->test_quick_select(thd, tab->keys,
                                         used_tables & ~ current_map,
                                         (join->select_options &
                                          OPTION_FOUND_ROWS ?
                                          HA_POS_ERROR :
                                          join->unit->select_limit_cnt),0,
                                          FALSE, FALSE) < 0)
		DBUG_RETURN(1);
            }
            else
	      sel->cond=orig_cond;


	    if (sel->quick)
	      join->best_positions[i].records_read= (double)sel->quick->records;
	  }
	  else
	  {
	    sel->needed_reg=tab->needed_reg;
	  }
	  sel->quick_keys= tab->table->quick_keys;
	  if (!sel->quick_keys.is_subset(tab->checked_keys) ||
              !sel->needed_reg.is_subset(tab->checked_keys))
	  {


	    tab->use_quick= (!sel->needed_reg.is_clear_all() &&
			     (sel->quick_keys.is_clear_all() ||
                              (sel->quick &&
                               sel->quick->read_time >
                               tab->table->file->scan_time() +
                               tab->table->file->stats.records/TIME_FOR_COMPARE
                               ))) ?
	      2 : 1;
	    sel->read_tables= used_tables & ~current_map;
            sel->quick_keys.clear_all();
	  }
	  if (i != join->const_tables && tab->use_quick != 2 &&
              !tab->first_inner)
	  {
            if (tab->make_scan_filter())
              DBUG_RETURN(1);
          }
	}
      }


      JOIN_TAB *start_from= tab->bush_root_tab?
                               tab->bush_root_tab->bush_children->start :
                               join->join_tab + join->const_tables;
      JOIN_TAB *end_with= tab->bush_root_tab?
                               tab->bush_root_tab->bush_children->end :
                               join->join_tab + join->top_join_tab_count;
      for (JOIN_TAB *join_tab= start_from;
           join_tab != end_with;
           join_tab++)
      {
        if (*join_tab->on_expr_ref)
        {
          JOIN_TAB *cond_tab= join_tab->first_inner;
          COND *tmp_cond= make_cond_for_table(thd, *join_tab->on_expr_ref,
                                              join->const_table_map,
                                              (table_map) 0, -1, FALSE, FALSE);
          if (!tmp_cond)
            continue;
          tmp_cond= new (thd->mem_root) Item_func_trig_cond(thd, tmp_cond,
                                            &cond_tab->not_null_compl);
          if (!tmp_cond)
            DBUG_RETURN(1);
          tmp_cond->quick_fix_field();
          cond_tab->select_cond= !cond_tab->select_cond ? tmp_cond :
                                 new (thd->mem_root) Item_cond_and(thd, cond_tab->select_cond,
                                                   tmp_cond);
          if (!cond_tab->select_cond)
	    DBUG_RETURN(1);
          cond_tab->select_cond->quick_fix_field();
          cond_tab->select_cond->update_used_tables();
          if (cond_tab->select)
            cond_tab->select->cond= cond_tab->select_cond;
        }
      }


      JOIN_TAB *last_tab= tab;


      while (first_inner_tab && first_inner_tab->last_inner == last_tab)
      {


        COND *on_expr= *first_inner_tab->on_expr_ref;

        table_map used_tables2= (join->const_table_map |
                                 OUTER_REF_TABLE_BIT | RAND_TABLE_BIT);

        start_from= tab->bush_root_tab?
                      tab->bush_root_tab->bush_children->start :
                      join->join_tab + join->const_tables;
        for (JOIN_TAB *inner_tab= start_from;
             inner_tab <= last_tab;
             inner_tab++)
        {
          DBUG_ASSERT(inner_tab->table);
          current_map= inner_tab->table->map;
          used_tables2|= current_map;


          COND *tmp_cond= make_cond_for_table(thd, on_expr, used_tables2,
                                              current_map,
                                               -1,
					      FALSE, FALSE);
          if (tab == last_tab)
          {


            table_map rand_table_bit= (table_map) RAND_TABLE_BIT;
            COND *rand_cond= make_cond_for_table(thd, on_expr, used_tables2,
                                                 rand_table_bit, -1,
                                                 FALSE, FALSE);
            add_cond_and_fix(thd, &tmp_cond, rand_cond);
          }
          bool is_sjm_lookup_tab= FALSE;
          if (inner_tab->bush_children)
          {


            SJ_MATERIALIZATION_INFO *sjm=
              inner_tab->bush_children->start->emb_sj_nest->sj_mat_info;
            if (sjm->is_used && !sjm->is_sj_scan)
              is_sjm_lookup_tab= TRUE;
          }

          if (inner_tab == first_inner_tab && inner_tab->on_precond &&
              !is_sjm_lookup_tab)
            add_cond_and_fix(thd, &tmp_cond, inner_tab->on_precond);
          if (tmp_cond && !is_sjm_lookup_tab)
          {
            JOIN_TAB *cond_tab=  (inner_tab < first_inner_tab ?
                                  first_inner_tab : inner_tab);
            Item **sel_cond_ref= (inner_tab < first_inner_tab ?
                                  &first_inner_tab->on_precond :
                                  &inner_tab->select_cond);


            if (!(tmp_cond= add_found_match_trig_cond(thd,
                                                     cond_tab->first_inner,
                                                     tmp_cond,
                                                     first_inner_tab)))
              DBUG_RETURN(1);


            DBUG_PRINT("info", ("Item_func_trig_cond"));
            tmp_cond= new (thd->mem_root) Item_func_trig_cond(thd, tmp_cond,
                                              &first_inner_tab->
                                              not_null_compl);
            DBUG_PRINT("info", ("Item_func_trig_cond %p",
                                tmp_cond));
            if (tmp_cond)
              tmp_cond->quick_fix_field();

            DBUG_PRINT("info", ("Item_cond_and"));
            *sel_cond_ref= !(*sel_cond_ref) ?
                             tmp_cond :
                             new (thd->mem_root) Item_cond_and(thd, *sel_cond_ref, tmp_cond);
            DBUG_PRINT("info", ("Item_cond_and %p",
                                (*sel_cond_ref)));
            if (!(*sel_cond_ref))
              DBUG_RETURN(1);
            (*sel_cond_ref)->quick_fix_field();
            (*sel_cond_ref)->update_used_tables();
            if (cond_tab->select)
              cond_tab->select->cond= cond_tab->select_cond;
          }
        }
        first_inner_tab= first_inner_tab->first_upper;
      }
      if (!tab->bush_children)
        i++;
    }
  }
  DBUG_RETURN(0);
}
