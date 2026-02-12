create_tmp_table(THD *thd, TMP_TABLE_PARAM *param, List<Item> &fields,
		 ORDER *group, bool distinct, bool save_sum_fields,
		 ulonglong select_options, ha_rows rows_limit,
                 const LEX_CSTRING *table_alias, bool do_not_open,
                 bool keep_row_order)
{
  MEM_ROOT *mem_root_save, own_root;
  TABLE *table;
  TABLE_SHARE *share;
  uint	i,field_count,null_count,null_pack_length;
  uint  copy_func_count= param->func_count;
  uint  hidden_null_count, hidden_null_pack_length, hidden_field_count;
  uint  blob_count,group_null_items, string_count;
  uint  temp_pool_slot=MY_BIT_NONE;
  uint fieldnr= 0;
  ulong reclength, string_total_length;
  bool  using_unique_constraint= false;
  bool  use_packed_rows= false;
  bool  not_all_columns= !(select_options & TMP_TABLE_ALL_COLUMNS);
  bool  save_abort_on_warning;
  char  *tmpname,path[FN_REFLEN];
  uchar	*pos, *group_buff, *bitmaps;
  uchar *null_flags;
  Field **reg_field, **from_field, **default_field;
  uint *blob_field;
  Copy_field *copy=0;
  KEY *keyinfo;
  KEY_PART_INFO *key_part_info;
  Item **copy_func;
  TMP_ENGINE_COLUMNDEF *recinfo;


  uint total_uneven_bit_length= 0, hidden_uneven_bit_length= 0;
  bool force_copy_fields= param->force_copy_fields;

  save_sum_fields|= param->precomputed_group_by;
  DBUG_ENTER("create_tmp_table");
  DBUG_PRINT("enter",
             ("table_alias: '%s'  distinct: %d  save_sum_fields: %d  "
              "rows_limit: %lu  group: %d", table_alias->str,
              (int) distinct, (int) save_sum_fields,
              (ulong) rows_limit, MY_TEST(group)));

  if (use_temp_pool && !(test_flags & TEST_KEEP_TMP_TABLES))
    temp_pool_slot = bitmap_lock_set_next(&temp_pool);

  if (temp_pool_slot != MY_BIT_NONE)
    sprintf(path, "%s_%lx_%i", tmp_file_prefix,
            current_pid, temp_pool_slot);
  else
  {

    sprintf(path, "%s%lx_%lx_%x", tmp_file_prefix,current_pid,
            (ulong) thd->thread_id, thd->tmp_table++);
  }


  fn_format(path, path, mysql_tmpdir, "", MY_REPLACE_EXT|MY_UNPACK_FILENAME);

  if (group)
  {
    ORDER **prev= &group;
    if (!param->quick_group)
      group=0;
    else for (ORDER *tmp=group ; tmp ; tmp=tmp->next)
    {

      if ((*tmp->item)->const_item())
      {
        *prev= tmp->next;
        param->group_parts--;
        continue;
      }
      else
        prev= &(tmp->next);


      (*tmp->item)->marker=4;
      if ((*tmp->item)->too_big_for_varchar())
	using_unique_constraint= true;
    }
    if (param->group_length >= MAX_BLOB_WIDTH)
      using_unique_constraint= true;
    if (group)
      distinct=0;
  }

  field_count=param->field_count+param->func_count+param->sum_func_count;
  hidden_field_count=param->hidden_field_count;


  if (param->precomputed_group_by)
    copy_func_count+= param->sum_func_count;

  init_sql_alloc(&own_root, "tmp_table", TABLE_ALLOC_BLOCK_SIZE, 0,
                 MYF(MY_THREAD_SPECIFIC));

  if (!multi_alloc_root(&own_root,
                        &table, sizeof(*table),
                        &share, sizeof(*share),
                        &reg_field, sizeof(Field*) * (field_count+1),
                        &default_field, sizeof(Field*) * (field_count),
                        &blob_field, sizeof(uint)*(field_count+1),
                        &from_field, sizeof(Field*)*field_count,
                        &copy_func, sizeof(*copy_func)*(copy_func_count+1),
                        &param->keyinfo, sizeof(*param->keyinfo),
                        &key_part_info,
                        sizeof(*key_part_info)*(param->group_parts+1),
                        &param->start_recinfo,
                        sizeof(*param->recinfo)*(field_count*2+4),
                        &tmpname, (uint) strlen(path)+1,
                        &group_buff, (group && ! using_unique_constraint ?
                                      param->group_length : 0),
                        &bitmaps, bitmap_buffer_size(field_count)*6,
                        NullS))
  {
    if (temp_pool_slot != MY_BIT_NONE)
      bitmap_lock_clear_bit(&temp_pool, temp_pool_slot);
    DBUG_RETURN(NULL);
  }

  if (!(param->copy_field= copy= new (thd->mem_root) Copy_field[field_count]))
  {
    if (temp_pool_slot != MY_BIT_NONE)
      bitmap_lock_clear_bit(&temp_pool, temp_pool_slot);
    free_root(&own_root, MYF(0));
    DBUG_RETURN(NULL);
  }
  param->items_to_copy= copy_func;
  strmov(tmpname, path);


  bzero((char*) table,sizeof(*table));
  bzero((char*) reg_field,sizeof(Field*)*(field_count+1));
  bzero((char*) default_field, sizeof(Field*) * (field_count));
  bzero((char*) from_field,sizeof(Field*)*field_count);

  table->mem_root= own_root;
  mem_root_save= thd->mem_root;
  thd->mem_root= &table->mem_root;

  table->field=reg_field;
  table->alias.set(table_alias->str, table_alias->length, table_alias_charset);

  table->reginfo.lock_type=TL_WRITE;
  table->map=1;
  table->temp_pool_slot = temp_pool_slot;
  table->copy_blobs= 1;
  table->in_use= thd;
  table->quick_keys.init();
  table->covering_keys.init();
  table->intersect_keys.init();
  table->keys_in_use_for_query.init();
  table->no_rows_with_nulls= param->force_not_null_cols;

  table->s= share;
  init_tmp_table_share(thd, share, "", 0, "(temporary)", tmpname);
  share->blob_field= blob_field;
  share->table_charset= param->table_charset;
  share->primary_key= MAX_KEY;
  share->keys_for_keyread.init();
  share->keys_in_use.init();
  if (param->schema_table)
    share->db= INFORMATION_SCHEMA_NAME;


  reclength= string_total_length= 0;
  blob_count= string_count= null_count= hidden_null_count= group_null_items= 0;
  param->using_outer_summary_function= 0;

  List_iterator_fast<Item> li(fields);
  Item *item;
  Field **tmp_from_field=from_field;
  while ((item=li++))
  {
    Item::Type type= item->type();
    if (type == Item::COPY_STR_ITEM)
    {
      item= ((Item_copy *)item)->get_item();
      type= item->type();
    }
    if (not_all_columns)
    {
      if (item->with_sum_func && type != Item::SUM_FUNC_ITEM)
      {
        if (item->used_tables() & OUTER_REF_TABLE_BIT)
          item->update_used_tables();
        if ((item->real_type() == Item::SUBSELECT_ITEM) ||
            (item->used_tables() & ~OUTER_REF_TABLE_BIT))
        {


	  param->using_outer_summary_function=1;
	  continue;
        }
      }
      if (item->const_item() && (int) hidden_field_count <= 0)
        continue;
    }
    if (type == Item::SUM_FUNC_ITEM && !group && !save_sum_fields)
    {
      Item_sum *sum_item= (Item_sum *) item;
      sum_item->result_field=0;
      for (i=0 ; i < sum_item->get_arg_count() ; i++)
      {
	Item *arg= sum_item->get_arg(i);
	if (!arg->const_item())
	{
          Item *tmp_item;
          Field *new_field=
            create_tmp_field(thd, table, arg, arg->type(), &copy_func,
                             tmp_from_field, &default_field[fieldnr],
                             group != 0,not_all_columns,
                             distinct, false);
	  if (!new_field)
	    goto err;
          DBUG_ASSERT(!new_field->field_name.str || strlen(new_field->field_name.str) == new_field->field_name.length);
	  tmp_from_field++;
	  reclength+=new_field->pack_length();
	  if (new_field->flags & BLOB_FLAG)
	  {
	    *blob_field++= fieldnr;
	    blob_count++;
	  }
          if (new_field->type() == MYSQL_TYPE_BIT)
            total_uneven_bit_length+= new_field->field_length & 7;
	  *(reg_field++)= new_field;
          if (new_field->real_type() == MYSQL_TYPE_STRING ||
              new_field->real_type() == MYSQL_TYPE_VARCHAR)
          {
            string_count++;
            string_total_length+= new_field->pack_length();
          }
          thd->mem_root= mem_root_save;
          if (!(tmp_item= new (thd->mem_root)
                Item_temptable_field(thd, new_field)))
            goto err;
          arg= sum_item->set_arg(i, thd, tmp_item);
          thd->mem_root= &table->mem_root;
          if (param->force_not_null_cols)
	  {
            new_field->flags|= NOT_NULL_FLAG;
            new_field->null_ptr= NULL;
          }
	  if (!(new_field->flags & NOT_NULL_FLAG))
          {
	    null_count++;


            arg->maybe_null=1;
          }
          new_field->field_index= fieldnr++;
	}
      }
    }
    else
    {


      Field *new_field= (param->schema_table) ?
        item->create_field_for_schema(thd, table) :
        create_tmp_field(thd, table, item, type, &copy_func,
                         tmp_from_field, &default_field[fieldnr],
                         group != 0,
                         !force_copy_fields &&
                           (not_all_columns || group !=0),


                         item->marker == 4  || param->bit_fields_as_long,
                         force_copy_fields);

      if (unlikely(!new_field))
      {
	if (unlikely(thd->is_fatal_error))
	  goto err;
	continue;
      }
      DBUG_ASSERT(!new_field->field_name.str || strlen(new_field->field_name.str) == new_field->field_name.length);
      if (type == Item::SUM_FUNC_ITEM)
      {
        Item_sum *agg_item= (Item_sum *) item;


        if (!agg_item->result_field || !param->materialized_subquery)
          agg_item->result_field= new_field;
      }
      tmp_from_field++;
      if (param->force_not_null_cols)
      {
        new_field->flags|= NOT_NULL_FLAG;
        new_field->null_ptr= NULL;
      }
      reclength+=new_field->pack_length();
      if (!(new_field->flags & NOT_NULL_FLAG))
	null_count++;
      if (new_field->type() == MYSQL_TYPE_BIT)
        total_uneven_bit_length+= new_field->field_length & 7;
      if (new_field->flags & BLOB_FLAG)
      {
        *blob_field++= fieldnr;
	blob_count++;
      }

      if (new_field->real_type() == MYSQL_TYPE_STRING ||
          new_field->real_type() == MYSQL_TYPE_VARCHAR)
      {
        string_count++;
        string_total_length+= new_field->pack_length();
      }

      if (item->marker == 4 && item->maybe_null)
      {
	group_null_items++;
	new_field->flags|= GROUP_FLAG;
      }
      new_field->field_index= fieldnr++;
      *(reg_field++)= new_field;
    }
    if (!--hidden_field_count)
    {


      hidden_null_count=null_count;


      param->hidden_field_count= fieldnr;
      null_count= 0;


      hidden_uneven_bit_length= total_uneven_bit_length;
      total_uneven_bit_length= 0;
    }
  }
  DBUG_ASSERT(fieldnr == (uint) (reg_field - table->field));
  DBUG_ASSERT(field_count >= (uint) (reg_field - table->field));
  field_count= fieldnr;
  *reg_field= 0;
  *blob_field= 0;
  share->fields= field_count;
  share->column_bitmap_size= bitmap_buffer_size(share->fields);


  if (blob_count || using_unique_constraint
      || (thd->variables.big_tables && !(select_options & SELECT_SMALL_RESULT))
      || (select_options & TMP_TABLE_FORCE_MYISAM)
      || thd->variables.tmp_memory_table_size == 0)
  {
    share->db_plugin= ha_lock_engine(0, TMP_ENGINE_HTON);
    table->file= get_new_handler(share, &table->mem_root,
                                 share->db_type());
    if (group &&
	(param->group_parts > table->file->max_key_parts() ||
	 param->group_length > table->file->max_key_length()))
      using_unique_constraint= true;
  }
  else
  {
    share->db_plugin= ha_lock_engine(0, heap_hton);
    table->file= get_new_handler(share, &table->mem_root,
                                 share->db_type());
  }
  if (!table->file)
    goto err;

  if (table->file->set_ha_share_ref(&share->ha_share))
  {
    delete table->file;
    goto err;
  }

  if (!using_unique_constraint)
    reclength+= group_null_items;

  share->blob_fields= blob_count;
  if (blob_count == 0)
  {

    if (param->hidden_field_count)
      hidden_null_count++;
    else
      null_count++;
  }
  hidden_null_pack_length= (hidden_null_count + 7 +
                            hidden_uneven_bit_length) / 8;
  null_pack_length= (hidden_null_pack_length +
                     (null_count + total_uneven_bit_length + 7) / 8);
  reclength+=null_pack_length;
  if (!reclength)
    reclength=1;

  if (blob_count ||
      (string_total_length >= STRING_TOTAL_LENGTH_TO_PACK_ROWS &&
       (reclength / string_total_length <= RATIO_TO_PACK_ROWS ||
        string_total_length / string_count >= AVG_STRING_LENGTH_TO_PACK_ROWS)))
    use_packed_rows= 1;

  share->reclength= reclength;
  {
    uint alloc_length=ALIGN_SIZE(reclength+MI_UNIQUE_HASH_LENGTH+1);
    share->rec_buff_length= alloc_length;
    if (!(table->record[0]= (uchar*)
                            alloc_root(&table->mem_root, alloc_length*3)))
      goto err;
    table->record[1]= table->record[0]+alloc_length;
    share->default_values= table->record[1]+alloc_length;
  }
  copy_func[0]=0;
  param->func_count= (uint)(copy_func - param->items_to_copy);

  setup_tmp_table_column_bitmaps(table, bitmaps);

  recinfo=param->start_recinfo;
  null_flags=(uchar*) table->record[0];
  pos=table->record[0]+ null_pack_length;
  if (null_pack_length)
  {
    bzero((uchar*) recinfo,sizeof(*recinfo));
    recinfo->type=FIELD_NORMAL;
    recinfo->length=null_pack_length;
    recinfo++;
    bfill(null_flags,null_pack_length,255);

    table->null_flags= (uchar*) table->record[0];
    share->null_fields= null_count+ hidden_null_count;
    share->null_bytes= share->null_bytes_for_compare= null_pack_length;
  }
  null_count= (blob_count == 0) ? 1 : 0;
  hidden_field_count=param->hidden_field_count;


  save_abort_on_warning= thd->abort_on_warning;
  thd->abort_on_warning= 0;

  for (i=0,reg_field=table->field; i < field_count; i++,reg_field++,recinfo++)
  {
    Field *field= *reg_field;
    uint length;
    bzero((uchar*) recinfo,sizeof(*recinfo));

    if (!(field->flags & NOT_NULL_FLAG))
    {
      recinfo->null_bit= (uint8)1 << (null_count & 7);
      recinfo->null_pos= null_count/8;
      field->move_field(pos,null_flags+null_count/8,
			(uint8)1 << (null_count & 7));
      null_count++;
    }
    else
      field->move_field(pos,(uchar*) 0,0);
    if (field->type() == MYSQL_TYPE_BIT)
    {

      ((Field_bit*) field)->set_bit_ptr(null_flags + null_count / 8,
                                        null_count & 7);
      null_count+= (field->field_length & 7);
    }
    field->reset();


    if (default_field[i] && default_field[i]->ptr)
    {


      Field *orig_field= default_field[i];

      if (orig_field->is_null_in_record(orig_field->table->s->default_values))
        field->set_null();
      else
      {


        my_ptrdiff_t ptr_diff= (orig_field->table->s->default_values -
                                orig_field->table->record[0]);
        field->set_notnull();
        orig_field->move_field_offset(ptr_diff);
        field_conv(field, orig_field);
        orig_field->move_field_offset(-ptr_diff);
      }
    }

    if (from_field[i])
    {
      copy->set(field,from_field[i],save_sum_fields);
      copy++;
    }
    length=field->pack_length_in_rec();
    pos+= length;


    recinfo->length=length;
    if (field->flags & BLOB_FLAG)
      recinfo->type= FIELD_BLOB;
    else if (use_packed_rows &&
             field->real_type() == MYSQL_TYPE_STRING &&
	     length >= MIN_STRING_LENGTH_TO_PACK_ROWS)
      recinfo->type= FIELD_SKIP_ENDSPACE;
    else if (field->real_type() == MYSQL_TYPE_VARCHAR)
      recinfo->type= FIELD_VARCHAR;
    else
      recinfo->type= FIELD_NORMAL;

    if (!--hidden_field_count)
      null_count=(null_count+7) & ~7;


    field->set_table_name(&table->alias);
  }

  bzero(pos, table->s->reclength - (pos - table->record[0]));
  MEM_CHECK_DEFINED(table->record[0], table->s->reclength);

  thd->abort_on_warning= save_abort_on_warning;
  param->copy_field_end=copy;
  param->recinfo= recinfo;
  store_record(table,s->default_values);

  if (thd->variables.tmp_memory_table_size == ~ (ulonglong) 0)
    share->max_rows= ~(ha_rows) 0;
  else
    share->max_rows= (ha_rows) (((share->db_type() == heap_hton) ?
                                 MY_MIN(thd->variables.tmp_memory_table_size,
                                     thd->variables.max_heap_table_size) :
                                 thd->variables.tmp_memory_table_size) /
                                share->reclength);
  set_if_bigger(share->max_rows,1);


  set_if_smaller(share->max_rows, rows_limit);
  param->end_write_records= rows_limit;

  keyinfo= param->keyinfo;

  if (group)
  {
    DBUG_PRINT("info",("Creating group key in temporary table"));
    table->group=group;
    param->group_buff=group_buff;
    share->keys=1;
    share->uniques= MY_TEST(using_unique_constraint);
    table->key_info= table->s->key_info= keyinfo;
    table->keys_in_use_for_query.set_bit(0);
    share->keys_in_use.set_bit(0);
    keyinfo->key_part=key_part_info;
    keyinfo->flags=HA_NOSAME | HA_BINARY_PACK_KEY | HA_PACK_KEY;
    keyinfo->ext_key_flags= keyinfo->flags;
    keyinfo->usable_key_parts=keyinfo->user_defined_key_parts= param->group_parts;
    keyinfo->ext_key_parts= keyinfo->user_defined_key_parts;
    keyinfo->key_length=0;
    keyinfo->rec_per_key=NULL;
    keyinfo->read_stats= NULL;
    keyinfo->collected_stats= NULL;
    keyinfo->algorithm= HA_KEY_ALG_UNDEF;
    keyinfo->is_statistics_from_stat_tables= FALSE;
    keyinfo->name= group_key;
    ORDER *cur_group= group;
    for (; cur_group ; cur_group= cur_group->next, key_part_info++)
    {
      Field *field=(*cur_group->item)->get_tmp_table_field();
      DBUG_ASSERT(field->table == table);
      bool maybe_null=(*cur_group->item)->maybe_null;
      key_part_info->null_bit=0;
      key_part_info->field=  field;
      key_part_info->fieldnr= field->field_index + 1;
      if (cur_group == group)
        field->key_start.set_bit(0);
      key_part_info->offset= field->offset(table->record[0]);
      key_part_info->length= (uint16) field->key_length();
      key_part_info->type=   (uint8) field->key_type();
      key_part_info->key_type =
	((ha_base_keytype) key_part_info->type == HA_KEYTYPE_TEXT ||
	 (ha_base_keytype) key_part_info->type == HA_KEYTYPE_VARTEXT1 ||
	 (ha_base_keytype) key_part_info->type == HA_KEYTYPE_VARTEXT2) ?
	0 : FIELDFLAG_BINARY;
      key_part_info->key_part_flag= 0;
      if (!using_unique_constraint)
      {
	cur_group->buff=(char*) group_buff;

        if (maybe_null && !field->null_bit)
        {


          (*cur_group->item)->maybe_null= maybe_null= 0;
        }

	if (!(cur_group->field= field->new_key_field(thd->mem_root,table,
                                                     group_buff +
                                                     MY_TEST(maybe_null),
                                                     key_part_info->length,
                                                     field->null_ptr,
                                                     field->null_bit)))
	  goto err;

	if (maybe_null)
	{


	  keyinfo->flags|= HA_NULL_ARE_EQUAL;
	  key_part_info->null_bit=field->null_bit;
	  key_part_info->null_offset= (uint) (field->null_ptr -
					      (uchar*) table->record[0]);
          cur_group->buff++;
	  group_buff++;
	}
	group_buff+= cur_group->field->pack_length();
      }
      keyinfo->key_length+=  key_part_info->length;
    }


    DBUG_ASSERT(using_unique_constraint ||
                group_buff <= param->group_buff + param->group_length);
  }

  if (distinct && field_count != param->hidden_field_count)
  {


    DBUG_PRINT("info",("hidden_field_count: %d", param->hidden_field_count));

    if (blob_count)
    {


      share->uniques= 1;
    }
    null_pack_length-=hidden_null_pack_length;
    keyinfo->user_defined_key_parts=
      ((field_count-param->hidden_field_count)+
       (share->uniques ? MY_TEST(null_pack_length) : 0));
    keyinfo->ext_key_parts= keyinfo->user_defined_key_parts;
    keyinfo->usable_key_parts= keyinfo->user_defined_key_parts;
    table->distinct= 1;
    share->keys= 1;
    if (!(key_part_info= (KEY_PART_INFO*)
          alloc_root(&table->mem_root,
                     keyinfo->user_defined_key_parts * sizeof(KEY_PART_INFO))))
      goto err;
    bzero((void*) key_part_info, keyinfo->user_defined_key_parts * sizeof(KEY_PART_INFO));
    table->keys_in_use_for_query.set_bit(0);
    share->keys_in_use.set_bit(0);
    table->key_info= table->s->key_info= keyinfo;
    keyinfo->key_part=key_part_info;
    keyinfo->flags=HA_NOSAME | HA_NULL_ARE_EQUAL | HA_BINARY_PACK_KEY | HA_PACK_KEY;
    keyinfo->ext_key_flags= keyinfo->flags;
    keyinfo->key_length= 0;
    keyinfo->name= distinct_key;
    keyinfo->algorithm= HA_KEY_ALG_UNDEF;
    keyinfo->is_statistics_from_stat_tables= FALSE;
    keyinfo->read_stats= NULL;
    keyinfo->collected_stats= NULL;


    size_t rpk_size= keyinfo->user_defined_key_parts * sizeof(keyinfo->rec_per_key[0]);
    if (!(keyinfo->rec_per_key= (ulong*) alloc_root(&table->mem_root,
                                                    rpk_size)))
      goto err;
    bzero(keyinfo->rec_per_key, rpk_size);


    if (null_pack_length && share->uniques)
    {
      key_part_info->null_bit=0;
      key_part_info->offset=hidden_null_pack_length;
      key_part_info->length=null_pack_length;
      key_part_info->field= new Field_string(table->record[0],
                                             (uint32) key_part_info->length,
                                             (uchar*) 0,
                                             (uint) 0,
                                             Field::NONE,
                                             &null_clex_str, &my_charset_bin);
      if (!key_part_info->field)
        goto err;
      key_part_info->field->init(table);
      key_part_info->key_type=FIELDFLAG_BINARY;
      key_part_info->type=    HA_KEYTYPE_BINARY;
      key_part_info->fieldnr= key_part_info->field->field_index + 1;
      key_part_info++;
    }

    for (i=param->hidden_field_count, reg_field=table->field + i ;
	 i < field_count;
	 i++, reg_field++, key_part_info++)
    {
      key_part_info->field=    *reg_field;
      (*reg_field)->flags |= PART_KEY_FLAG;
      if (key_part_info == keyinfo->key_part)
        (*reg_field)->key_start.set_bit(0);
      key_part_info->null_bit= (*reg_field)->null_bit;
      key_part_info->null_offset= (uint) ((*reg_field)->null_ptr -
                                          (uchar*) table->record[0]);

      key_part_info->offset=   (*reg_field)->offset(table->record[0]);
      key_part_info->length=   (uint16) (*reg_field)->pack_length();
      key_part_info->fieldnr= (*reg_field)->field_index + 1;


      key_part_info->store_length= key_part_info->length;

      if ((*reg_field)->real_maybe_null())
      {
        key_part_info->store_length+= HA_KEY_NULL_LENGTH;
        key_part_info->key_part_flag |= HA_NULL_PART;
      }
      if ((*reg_field)->type() == MYSQL_TYPE_BLOB ||
          (*reg_field)->real_type() == MYSQL_TYPE_VARCHAR ||
          (*reg_field)->type() == MYSQL_TYPE_GEOMETRY)
      {
        if ((*reg_field)->type() == MYSQL_TYPE_BLOB ||
            (*reg_field)->type() == MYSQL_TYPE_GEOMETRY)
          key_part_info->key_part_flag|= HA_BLOB_PART;
        else
          key_part_info->key_part_flag|= HA_VAR_LENGTH_PART;

        key_part_info->store_length+=HA_KEY_BLOB_LENGTH;
      }

      keyinfo->key_length+= key_part_info->store_length;

      key_part_info->type=     (uint8) (*reg_field)->key_type();
      key_part_info->key_type =
	((ha_base_keytype) key_part_info->type == HA_KEYTYPE_TEXT ||
	 (ha_base_keytype) key_part_info->type == HA_KEYTYPE_VARTEXT1 ||
	 (ha_base_keytype) key_part_info->type == HA_KEYTYPE_VARTEXT2) ?
	0 : FIELDFLAG_BINARY;
    }
  }

  if (unlikely(thd->is_fatal_error))
    goto err;
  share->db_record_offset= 1;
  table->used_for_duplicate_elimination= (param->sum_func_count == 0 &&
                                          (table->group || table->distinct));
  table->keep_row_order= keep_row_order;

  if (!do_not_open)
  {
    if (instantiate_tmp_table(table, param->keyinfo, param->start_recinfo,
                              &param->recinfo, select_options))
      goto err;
  }


  MEM_CHECK_DEFINED(table->record[0], table->s->reclength);
  MEM_CHECK_DEFINED(share->default_values, table->s->reclength);

  thd->mem_root= mem_root_save;

  DBUG_RETURN(table);

err:
  thd->mem_root= mem_root_save;
  free_tmp_table(thd,table);
  if (temp_pool_slot != MY_BIT_NONE)
    bitmap_lock_clear_bit(&temp_pool, temp_pool_slot);
  DBUG_RETURN(NULL);
}
