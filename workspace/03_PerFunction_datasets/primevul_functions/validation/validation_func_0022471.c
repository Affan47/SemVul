bool create_internal_tmp_table(TABLE *table, KEY *keyinfo,
                               TMP_ENGINE_COLUMNDEF *start_recinfo,
                               TMP_ENGINE_COLUMNDEF **recinfo,
                               ulonglong options)
{
  int error;
  MARIA_KEYDEF keydef;
  MARIA_UNIQUEDEF uniquedef;
  TABLE_SHARE *share= table->s;
  MARIA_CREATE_INFO create_info;
  DBUG_ENTER("create_internal_tmp_table");

  if (share->keys)
  {
    bool using_unique_constraint=0;
    HA_KEYSEG *seg= (HA_KEYSEG*) alloc_root(&table->mem_root,
                                            sizeof(*seg) * keyinfo->user_defined_key_parts);
    if (!seg)
      goto err;

    bzero(seg, sizeof(*seg) * keyinfo->user_defined_key_parts);


    if (keyinfo->key_length > table->file->max_key_length() ||
	keyinfo->user_defined_key_parts > table->file->max_key_parts() ||
	share->uniques)
    {
      if (!share->uniques && !(keyinfo->flags & HA_NOSAME))
      {
        my_error(ER_INTERNAL_ERROR, MYF(0),
                 "Using too big key for internal temp tables");
        DBUG_RETURN(1);
      }


      share->keys=    0;
      share->uniques= 1;
      using_unique_constraint=1;
      bzero((char*) &uniquedef,sizeof(uniquedef));
      uniquedef.keysegs=keyinfo->user_defined_key_parts;
      uniquedef.seg=seg;
      uniquedef.null_are_equal=1;


      bzero((uchar*) *recinfo,sizeof(**recinfo));
      (*recinfo)->type=   FIELD_CHECK;
      (*recinfo)->length= MARIA_UNIQUE_HASH_LENGTH;
      (*recinfo)++;


      bzero(table->record[0]+ share->reclength, MARIA_UNIQUE_HASH_LENGTH);
      bzero(share->default_values+ share->reclength, MARIA_UNIQUE_HASH_LENGTH);
      share->reclength+= MARIA_UNIQUE_HASH_LENGTH;
    }
    else
    {

      bzero((char*) &keydef,sizeof(keydef));
      keydef.flag= keyinfo->flags & HA_NOSAME;
      keydef.keysegs=  keyinfo->user_defined_key_parts;
      keydef.seg= seg;
    }
    for (uint i=0; i < keyinfo->user_defined_key_parts ; i++,seg++)
    {
      Field *field=keyinfo->key_part[i].field;
      seg->flag=     0;
      seg->language= field->charset()->number;
      seg->length=   keyinfo->key_part[i].length;
      seg->start=    keyinfo->key_part[i].offset;
      if (field->flags & BLOB_FLAG)
      {
	seg->type=
	((keyinfo->key_part[i].key_type & FIELDFLAG_BINARY) ?
	 HA_KEYTYPE_VARBINARY2 : HA_KEYTYPE_VARTEXT2);
	seg->bit_start= (uint8)(field->pack_length() -
                                portable_sizeof_char_ptr);
	seg->flag= HA_BLOB_PART;
	seg->length=0;
      }
      else
      {
	seg->type= keyinfo->key_part[i].type;

	if (field->real_type() == MYSQL_TYPE_STRING &&
	    keyinfo->key_part[i].length > 32)
	  seg->flag|= HA_SPACE_PACK;
      }
      if (!(field->flags & NOT_NULL_FLAG))
      {
	seg->null_bit= field->null_bit;
	seg->null_pos= (uint) (field->null_ptr - (uchar*) table->record[0]);


	if (!using_unique_constraint)
	  keydef.flag|= HA_NULL_ARE_EQUAL;
      }
    }
  }
  bzero((char*) &create_info,sizeof(create_info));
  create_info.data_file_length= table->in_use->variables.tmp_disk_table_size;


  {
    enum data_file_type file_type= table->no_rows ? NO_RECORD :
        (share->reclength < 64 && !share->blob_fields ? STATIC_RECORD :
         table->used_for_duplicate_elimination ? DYNAMIC_RECORD : BLOCK_RECORD);
    uint create_flags= HA_CREATE_TMP_TABLE | HA_CREATE_INTERNAL_TABLE |
        (table->keep_row_order ? HA_PRESERVE_INSERT_ORDER : 0);

    if (file_type != NO_RECORD && encrypt_tmp_disk_tables)
    {

      file_type= BLOCK_RECORD;
      if (table->used_for_duplicate_elimination)
      {


        uint cols= (uint)(*recinfo-start_recinfo);
        start_recinfo[cols-1].null_bit= 0;
      }
    }

    if (unlikely((error= maria_create(share->path.str, file_type, share->keys,
                                      &keydef, (uint) (*recinfo-start_recinfo),
                                      start_recinfo, share->uniques, &uniquedef,
                                      &create_info, create_flags))))
    {
      table->file->print_error(error,MYF(0));
      table->db_stat=0;
      goto err;
    }
  }

  table->in_use->inc_status_created_tmp_disk_tables();
  table->in_use->inc_status_created_tmp_tables();
  share->db_record_offset= 1;
  table->set_created();
  DBUG_RETURN(0);
 err:
  DBUG_RETURN(1);
}
