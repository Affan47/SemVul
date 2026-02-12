best_access_path(JOIN      *join,
                 JOIN_TAB  *s,
                 table_map remaining_tables,
                 const POSITION *join_positions,
                 uint      idx,
                 bool      disable_jbuf,
                 double    record_count,
                 POSITION *pos,
                 POSITION *loose_scan_pos)
{
  THD *thd= join->thd;
  uint use_cond_selectivity= thd->variables.optimizer_use_condition_selectivity;
  KEYUSE *best_key=         0;
  uint best_max_key_part=   0;
  my_bool found_constraint= 0;
  double best=              DBL_MAX;
  double best_time=         DBL_MAX;
  double records=           DBL_MAX;
  table_map best_ref_depends_map= 0;
  Range_rowid_filter_cost_info *best_filter= 0;
  double tmp;
  ha_rows rec;
  bool best_uses_jbuf= FALSE;
  MY_BITMAP *eq_join_set= &s->table->eq_join_set;
  KEYUSE *hj_start_key= 0;
  SplM_plan_info *spl_plan= 0;
  Range_rowid_filter_cost_info *filter= 0;
  const char* cause= NULL;
  enum join_type best_type= JT_UNKNOWN, type= JT_UNKNOWN;

  disable_jbuf= disable_jbuf || idx == join->const_tables;

  Loose_scan_opt loose_scan_opt;
  DBUG_ENTER("best_access_path");

  Json_writer_object trace_wrapper(thd, "best_access_path");
  Json_writer_array trace_paths(thd, "considered_access_paths");

  bitmap_clear_all(eq_join_set);

  loose_scan_opt.init(join, s, remaining_tables);

  if (s->table->is_splittable())
    spl_plan= s->choose_best_splitting(record_count, remaining_tables);

  if (s->keyuse)
  {
    KEYUSE *keyuse;
    KEYUSE *start_key=0;
    TABLE *table= s->table;
    double best_records= DBL_MAX;
    uint max_key_part=0;


    rec= s->records/MATCHING_ROWS_IN_OTHER_TABLE;
    for (keyuse=s->keyuse ; keyuse->table == table ;)
    {
      KEY *keyinfo;
      ulong key_flags;
      uint key_parts;
      key_part_map found_part= 0;
      key_part_map notnull_part=0;
      table_map found_ref= 0;
      uint key= keyuse->key;
      filter= 0;
      bool ft_key=  (keyuse->keypart == FT_KEYPART);

      key_part_map const_part= 0;

      key_part_map ref_or_null_part= 0;
      if (is_hash_join_key_no(key))
      {


        if (!(remaining_tables & keyuse->used_tables) &&
            idx > join->const_tables)
        {
          if (!hj_start_key)
            hj_start_key= keyuse;
          bitmap_set_bit(eq_join_set, keyuse->keypart);
        }
        keyuse++;
        continue;
      }

      keyinfo= table->key_info+key;
      key_parts= table->actual_n_key_parts(keyinfo);
      key_flags= table->actual_key_flags(keyinfo);


      start_key= keyuse;

      loose_scan_opt.next_ref_key();
      DBUG_PRINT("info", ("Considering ref access on key %s",
                          keyuse->table->key_info[keyuse->key].name.str));

      do
      {
        uint keypart= keyuse->keypart;
        table_map best_part_found_ref= 0;
        double best_prev_record_reads= DBL_MAX;

        do
        {


          if (!(remaining_tables & keyuse->used_tables) &&
              (!keyuse->validity_ref || *keyuse->validity_ref) &&
              s->access_from_tables_is_allowed(keyuse->used_tables,
                                               join->sjm_lookup_tables) &&
              !(ref_or_null_part && (keyuse->optimize &
                                     KEY_OPTIMIZE_REF_OR_NULL)))
          {
            found_part|= keyuse->keypart_map;
            if (!(keyuse->used_tables & ~join->const_table_map))
              const_part|= keyuse->keypart_map;

            if (!keyuse->val->maybe_null || keyuse->null_rejecting)
              notnull_part|=keyuse->keypart_map;

            double tmp2= prev_record_reads(join_positions, idx,
                                           (found_ref | keyuse->used_tables));
            if (tmp2 < best_prev_record_reads)
            {
              best_part_found_ref= keyuse->used_tables & ~join->const_table_map;
              best_prev_record_reads= tmp2;
            }
            if (rec > keyuse->ref_table_rows)
              rec= keyuse->ref_table_rows;


            if (keyuse->optimize & KEY_OPTIMIZE_REF_OR_NULL)
              ref_or_null_part |= keyuse->keypart_map;
          }
          loose_scan_opt.add_keyuse(remaining_tables, keyuse);
          keyuse++;
        } while (keyuse->table == table && keyuse->key == key &&
                 keyuse->keypart == keypart);
	found_ref|= best_part_found_ref;
      } while (keyuse->table == table && keyuse->key == key);


      if (!found_part && !ft_key && !loose_scan_opt.have_a_case())
        continue;

      if (rec < MATCHING_ROWS_IN_OTHER_TABLE)
        rec= MATCHING_ROWS_IN_OTHER_TABLE;

      Json_writer_object trace_access_idx(thd);


      if (ft_key)
      {


        tmp= prev_record_reads(join_positions, idx, found_ref);
        records= 1.0;
        type= JT_FT;
        trace_access_idx.add("access_type", join_type_str[type])
                        .add("full-text index", keyinfo->name);
      }
      else
      {
        found_constraint= MY_TEST(found_part);
        loose_scan_opt.check_ref_access_part1(s, key, start_key, found_part);


        const key_part_map all_key_parts= PREV_BITS(uint, key_parts);
        if (found_part == all_key_parts && !ref_or_null_part)
        {
          max_key_part= (uint) ~0;


          if ((key_flags & (HA_NOSAME | HA_EXT_NOSAME)) &&
              (!(key_flags & HA_NULL_PART_KEY) ||
               all_key_parts == notnull_part))
          {
            type= JT_EQ_REF;
            trace_access_idx.add("access_type", join_type_str[type])
                            .add("index", keyinfo->name);
            tmp = prev_record_reads(join_positions, idx, found_ref);
            records=1.0;
          }
          else
          {
            type= JT_REF;
            trace_access_idx.add("access_type", join_type_str[type])
                            .add("index", keyinfo->name);
            if (!found_ref)
            {


              if (table->quick_keys.is_set(key))
              {
                records= (double) table->quick_rows[key];
                trace_access_idx.add("used_range_estimates", true);
              }
              else
              {

                records= (double) s->records/rec;
                trace_access_idx.add("used_range_estimates", false)
                                .add("cause", "not available");
              }
            }
            else
            {
              if (!(records= keyinfo->actual_rec_per_key(key_parts-1)))
              {
                records=
                  ((double) s->records / (double) rec *
                   (1.0 +
                    ((double) (table->s->max_key_length-keyinfo->key_length) /
                     (double) table->s->max_key_length)));
                if (records < 2.0)
                  records=2.0;
              }


              if (table->quick_keys.is_set(key) &&
                  (const_part &
                    (((key_part_map)1 << table->quick_key_parts[key])-1)) ==
                  (((key_part_map)1 << table->quick_key_parts[key])-1) &&
                  table->quick_n_ranges[key] == 1 &&
                  records > (double) table->quick_rows[key])
              {

                records= (double) table->quick_rows[key];
                trace_access_idx.add("used_range_estimates", true);
              }
              else
              {
                if (table->quick_keys.is_set(key))
                {
                  trace_access_idx.add("used_range_estimates",false)
                                  .add("cause",
                                       "not better than ref estimates");
                }
                else
                {
                  trace_access_idx.add("used_range_estimates", false)
                                  .add("cause", "not available");
                }
              }
            }

            tmp= records;
            set_if_smaller(tmp, (double) thd->variables.max_seeks_for_key);
            if (table->covering_keys.is_set(key))
              tmp= table->file->keyread_time(key, 1, (ha_rows) tmp);
            else
              tmp= table->file->read_time(key, 1,
                                          (ha_rows) MY_MIN(tmp,s->worst_seeks));
            tmp= COST_MULT(tmp, record_count);
          }
        }
        else
        {
          type = ref_or_null_part ? JT_REF_OR_NULL : JT_REF;
          trace_access_idx.add("access_type", join_type_str[type])
                          .add("index", keyinfo->name);


          if ((found_part & 1) &&
              (!(table->file->index_flags(key, 0, 0) & HA_ONLY_WHOLE_INDEX) ||
               found_part == PREV_BITS(uint,keyinfo->user_defined_key_parts)))
          {
            max_key_part= max_part_bit(found_part);


            if (table->quick_keys.is_set(key) && !found_ref &&
                table->quick_key_parts[key] == max_key_part &&
                table->quick_n_ranges[key] == 1 + MY_TEST(ref_or_null_part))
            {
              tmp= records= (double) table->quick_rows[key];
              trace_access_idx.add("used_range_estimates", true);
            }
            else
            {

              if ((records= keyinfo->actual_rec_per_key(max_key_part-1)))
              {


                if (!found_ref && table->quick_keys.is_set(key) &&
                    table->quick_key_parts[key] > max_key_part &&
                    records < (double)table->quick_rows[key])
                {
                  trace_access_idx.add("used_range_estimates", true);
                  records= (double)table->quick_rows[key];
                }
                else
                {
                  if (table->quick_keys.is_set(key) &&
                      table->quick_key_parts[key] < max_key_part)
                  {
                    trace_access_idx.add("chosen", false);
                    cause= "range uses more keyparts";
                  }
                }

                tmp= records;
              }
              else
              {


                double rec_per_key;
                if (!(rec_per_key=(double)
                      keyinfo->rec_per_key[keyinfo->user_defined_key_parts-1]))
                  rec_per_key=(double) s->records/rec+1;

                if (!s->records)
                  tmp = 0;
                else if (rec_per_key/(double) s->records >= 0.01)
                  tmp = rec_per_key;
                else
                {
                  double a=s->records*0.01;
                  if (keyinfo->user_defined_key_parts > 1)
                    tmp= (max_key_part * (rec_per_key - a) +
                          a*keyinfo->user_defined_key_parts - rec_per_key)/
                         (keyinfo->user_defined_key_parts-1);
                  else
                    tmp= a;
                  set_if_bigger(tmp,1.0);
                }
                records = (ulong) tmp;
              }

              if (ref_or_null_part)
              {

                tmp *= 2.0;
                records *= 2.0;
              }


              if (table->quick_keys.is_set(key) &&
                  table->quick_key_parts[key] <= max_key_part &&
                  const_part &
                    ((key_part_map)1 << table->quick_key_parts[key]) &&
                  table->quick_n_ranges[key] == 1 + MY_TEST(ref_or_null_part &
                                                            const_part) &&
                  records > (double) table->quick_rows[key])
              {
                tmp= records= (double) table->quick_rows[key];
              }
            }


            set_if_smaller(tmp, (double) thd->variables.max_seeks_for_key);
            if (table->covering_keys.is_set(key))
              tmp= table->file->keyread_time(key, 1, (ha_rows) tmp);
            else
              tmp= table->file->read_time(key, 1,
                                          (ha_rows) MY_MIN(tmp,s->worst_seeks));
            tmp= COST_MULT(tmp, record_count);
          }
          else
          {
            if (!(found_part & 1))
              cause= "no predicate for first keypart";
            tmp= best_time;
          }
        }

        tmp= COST_ADD(tmp, s->startup_cost);
        loose_scan_opt.check_ref_access_part2(key, start_key, records, tmp,
                                              found_ref);
      }

      if (records < DBL_MAX &&
	  (found_part & 1))
      {
        double rows= record_count * records;
        double access_cost_factor= MY_MIN(tmp / rows, 1.0);
        filter=
          table->best_range_rowid_filter_for_partial_join(start_key->key, rows,
                                                          access_cost_factor);
        if (filter)
	{
          filter->get_cmp_gain(rows);
          tmp-= filter->get_adjusted_gain(rows) - filter->get_cmp_gain(rows);
          DBUG_ASSERT(tmp >= 0);
          trace_access_idx.add("rowid_filter_key",
                               s->table->key_info[filter->key_no].name);
        }
      }
      trace_access_idx.add("rows", records).add("cost", tmp);

      if (tmp + 0.0001 < best_time - records/(double) TIME_FOR_COMPARE)
      {
        trace_access_idx.add("chosen", true);
        best_time= COST_ADD(tmp, records/(double) TIME_FOR_COMPARE);
        best= tmp;
        best_records= records;
        best_key= start_key;
        best_max_key_part= max_key_part;
        best_ref_depends_map= found_ref;
        best_filter= filter;
        best_type= type;
      }
      else
      {
        trace_access_idx.add("chosen", false)
                        .add("cause", cause ? cause : "cost");
      }
      cause= NULL;
    }
    records= best_records;
  }


  if (idx > join->const_tables && best_key == 0 &&
      (join->allowed_join_cache_types & JOIN_CACHE_HASHED_BIT) &&
      join->max_allowed_join_cache_level > 2 &&
     !bitmap_is_clear_all(eq_join_set) &&  !disable_jbuf &&
      (!s->emb_sj_nest ||
       join->allowed_semijoin_with_cache) &&
      (!(s->table->map & join->outer_join) ||
       join->allowed_outer_join_with_cache))
  {
    Json_writer_object trace_access_hash(thd);
    double join_sel= 0.1;

    double rnd_records= matching_candidates_in_table(s, found_constraint,
                                                     use_cond_selectivity);

    tmp= s->quick ? s->quick->read_time : s->scan_time();
    double cmp_time= (s->records - rnd_records)/(double) TIME_FOR_COMPARE;
    tmp= COST_ADD(tmp, cmp_time);


    double refills= (1.0 + floor((double) cache_record_length(join,idx) *
                           record_count /
			   (double) thd->variables.join_buff_size));
    tmp= COST_MULT(tmp, refills);
    best_time= COST_ADD(tmp,
                        COST_MULT((record_count*join_sel) / TIME_FOR_COMPARE,
                                  rnd_records));
    best= tmp;
    records= rnd_records;
    best_key= hj_start_key;
    best_ref_depends_map= 0;
    best_uses_jbuf= TRUE;
    best_filter= 0;
    best_type= JT_HASH;
    trace_access_hash.add("type", "hash");
    trace_access_hash.add("index", "hj-key");
    trace_access_hash.add("cost", rnd_records);
    trace_access_hash.add("cost", best);
    trace_access_hash.add("chosen", true);
  }


  Json_writer_object trace_access_scan(thd);
  if ((records >= s->found_records || best > s->read_time) &&
      !(best_key && best_key->key == MAX_KEY) &&
      !(s->quick && best_key && s->quick->index == best_key->key &&
        best_max_key_part >= s->table->quick_key_parts[best_key->key]) &&
      !((s->table->file->ha_table_flags() & HA_TABLE_SCAN_ON_INDEX) &&
        ! s->table->covering_keys.is_clear_all() && best_key && !s->quick) &&
      !(s->table->force_index && best_key && !s->quick) &&
      !(best_key && s->table->pos_in_table_list->jtbm_subselect))
  {
    double rnd_records= matching_candidates_in_table(s, found_constraint,
                                                      use_cond_selectivity);


    filter= 0;
    if (s->quick)
    {


      double cmp_time= (s->found_records - rnd_records)/(double) TIME_FOR_COMPARE;
      tmp= COST_MULT(record_count,
                     COST_ADD(s->quick->read_time, cmp_time));

      if ( s->quick->get_type() == QUICK_SELECT_I::QS_TYPE_RANGE)
      {
        double rows= record_count * s->found_records;
        double access_cost_factor= MY_MIN(tmp / rows, 1.0);
        uint key_no= s->quick->index;
        filter=
        s->table->best_range_rowid_filter_for_partial_join(key_no, rows,
                                                           access_cost_factor);
        if (filter)
        {
          tmp-= filter->get_adjusted_gain(rows);
          DBUG_ASSERT(tmp >= 0);
        }
        type= JT_RANGE;
      }
      else
      {
        type= JT_INDEX_MERGE;
        best_filter= 0;
      }
      loose_scan_opt.check_range_access(join, idx, s->quick);
    }
    else
    {

      if (s->table->force_index && !best_key)
      {
        type= JT_NEXT;
        tmp= s->table->file->read_time(s->ref.key, 1, s->records);
      }
      else
      {
        tmp= s->scan_time();
        type= JT_ALL;
      }

      if ((s->table->map & join->outer_join) || disable_jbuf)
      {


        double cmp_time= (s->records - rnd_records)/(double) TIME_FOR_COMPARE;
        tmp= COST_MULT(record_count, COST_ADD(tmp,cmp_time));
      }
      else
      {
        double refills= (1.0 + floor((double) cache_record_length(join,idx) *
                        (record_count /
                         (double) thd->variables.join_buff_size)));
        tmp= COST_MULT(tmp, refills);


        double cmp_time= (s->records - rnd_records)/(double) TIME_FOR_COMPARE;
        tmp= COST_ADD(tmp, cmp_time);
      }
    }

    trace_access_scan.add("access_type", type == JT_ALL ?
                                         "scan" :
                                         join_type_str[type]);

    if (s->table->is_splittable())
      tmp+= s->table->get_materialization_cost();
    else
      tmp+= s->startup_cost;


    const double best_filter_cmp_gain= best_filter
      ? best_filter->get_cmp_gain(record_count * records)
      : 0;
    trace_access_scan.add("resulting_rows", rnd_records);
    trace_access_scan.add("cost", tmp);

    if (best == DBL_MAX ||
        COST_ADD(tmp, record_count/(double) TIME_FOR_COMPARE*rnd_records) <
         (best_key->is_for_hash_join() ? best_time :
          COST_ADD(best - best_filter_cmp_gain,
                   record_count/(double) TIME_FOR_COMPARE*records)))
    {


      best= tmp;
      records= rnd_records;
      best_key= 0;
      best_filter= 0;
      if (s->quick && s->quick->get_type() == QUICK_SELECT_I::QS_TYPE_RANGE)
        best_filter= filter;

      best_ref_depends_map= 0;
      best_uses_jbuf= MY_TEST(!disable_jbuf && !((s->table->map &
                                                  join->outer_join)));
      spl_plan= 0;
      best_type= type;
    }
    trace_access_scan.add("chosen", best_key == NULL);
  }
  else
  {
    trace_access_scan.add("type", "scan");
    trace_access_scan.add("chosen", false);
    trace_access_scan.add("cause", "cost");
  }


  pos->records_read= records;
  pos->read_time=    best;
  pos->key=          best_key;
  pos->table=        s;
  pos->ref_depend_map= best_ref_depends_map;
  pos->loosescan_picker.loosescan_key= MAX_KEY;
  pos->use_join_buffer= best_uses_jbuf;
  pos->spl_plan= spl_plan;
  pos->range_rowid_filter_info= best_filter;

  loose_scan_opt.save_to_position(s, loose_scan_pos);

  if (!best_key &&
      idx == join->const_tables &&
      s->table == join->sort_by_table &&
      join->unit->select_limit_cnt >= records)
  {
    trace_access_scan.add("use_tmp_table", true);
    join->sort_by_table= (TABLE*) 1;
  }
  trace_access_scan.end();
  trace_paths.end();

  if (unlikely(thd->trace_started()))
    print_best_access_for_table(thd, pos, best_type);

  DBUG_VOID_RETURN;
}
