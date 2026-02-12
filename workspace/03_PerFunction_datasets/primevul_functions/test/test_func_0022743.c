int maria_create(const char *name, enum data_file_type datafile_type,
                 uint keys,MARIA_KEYDEF *keydefs,
                 uint columns, MARIA_COLUMNDEF *columndef,
                 uint uniques, MARIA_UNIQUEDEF *uniquedefs,
                 MARIA_CREATE_INFO *ci,uint flags)
{
  register uint i,j;
  File UNINIT_VAR(dfile), UNINIT_VAR(file);
  int errpos,save_errno, create_mode= O_RDWR | O_TRUNC, res;
  myf create_flag;
  uint length,max_key_length,packed,pack_bytes,pointer,real_length_diff,
       key_length,info_length,key_segs,options,min_key_length,
       base_pos,long_varchar_count,
       unique_key_parts,fulltext_keys,offset, not_block_record_extra_length;
  uint max_field_lengths, extra_header_size, column_nr;
  uint internal_table= flags & HA_CREATE_INTERNAL_TABLE;
  ulong reclength, real_reclength,min_pack_length;
  char kfilename[FN_REFLEN], klinkname[FN_REFLEN], *klinkname_ptr= NullS;
  char dfilename[FN_REFLEN], dlinkname[FN_REFLEN], *dlinkname_ptr= 0;
  ulong pack_reclength;
  ulonglong tot_length,max_rows, tmp;
  enum en_fieldtype type;
  enum data_file_type org_datafile_type= datafile_type;
  MARIA_SHARE share;
  MARIA_KEYDEF *keydef,tmp_keydef;
  MARIA_UNIQUEDEF *uniquedef;
  HA_KEYSEG *keyseg,tmp_keyseg;
  MARIA_COLUMNDEF *column, *end_column;
  double *rec_per_key_part;
  ulong  *nulls_per_key_part;
  uint16 *column_array;
  my_off_t key_root[HA_MAX_POSSIBLE_KEY], kfile_size_before_extension;
  MARIA_CREATE_INFO tmp_create_info;
  my_bool tmp_table= FALSE;
  my_bool forced_packed;
  myf     sync_dir=  0;
  uchar   *log_data= NULL;
  my_bool encrypted= maria_encrypt_tables && datafile_type == BLOCK_RECORD;
  my_bool insert_order= MY_TEST(flags & HA_PRESERVE_INSERT_ORDER);
  uint crypt_page_header_space= 0;
  DBUG_ENTER("maria_create");
  DBUG_PRINT("enter", ("keys: %u  columns: %u  uniques: %u  flags: %u",
                      keys, columns, uniques, flags));

  DBUG_ASSERT(maria_inited);

  if (!ci)
  {
    bzero((char*) &tmp_create_info,sizeof(tmp_create_info));
    ci=&tmp_create_info;
  }

  if (keys + uniques > MARIA_MAX_KEY)
  {
    DBUG_RETURN(my_errno=HA_WRONG_CREATE_OPTION);
  }
  errpos=0;
  options=0;
  bzero((uchar*) &share,sizeof(share));

  if (flags & HA_DONT_TOUCH_DATA)
  {

    org_datafile_type= ci->org_data_file_type;
    if (!(ci->old_options & HA_OPTION_TEMP_COMPRESS_RECORD))
      options= (ci->old_options &
                (HA_OPTION_COMPRESS_RECORD | HA_OPTION_PACK_RECORD |
                 HA_OPTION_READ_ONLY_DATA | HA_OPTION_CHECKSUM |
                 HA_OPTION_TMP_TABLE | HA_OPTION_DELAY_KEY_WRITE |
                 HA_OPTION_LONG_BLOB_PTR | HA_OPTION_PAGE_CHECKSUM));
    else
    {

      options= (ci->old_options &
                (HA_OPTION_CHECKSUM | HA_OPTION_TMP_TABLE |
                 HA_OPTION_DELAY_KEY_WRITE | HA_OPTION_LONG_BLOB_PTR |
                 HA_OPTION_PAGE_CHECKSUM));
    }
  }
  else
  {

    if (ci->transactional)
      datafile_type= BLOCK_RECORD;
  }

  if (!(rec_per_key_part=
	(double*) my_malloc((keys + uniques)*HA_MAX_KEY_SEG*sizeof(double) +
                            (keys + uniques)*HA_MAX_KEY_SEG*sizeof(ulong) +
                            sizeof(uint16) * columns,
                            MYF(MY_WME | MY_ZEROFILL))))
    DBUG_RETURN(my_errno);
  nulls_per_key_part= (ulong*) (rec_per_key_part +
                                (keys + uniques) * HA_MAX_KEY_SEG);
  column_array= (uint16*) (nulls_per_key_part +
                           (keys + uniques) * HA_MAX_KEY_SEG);


  long_varchar_count=packed= not_block_record_extra_length=
    pack_reclength= max_field_lengths= 0;
  reclength= min_pack_length= ci->null_bytes;
  forced_packed= 0;
  column_nr= 0;

  if (encrypted)
  {
    DBUG_ASSERT(datafile_type == BLOCK_RECORD);
    crypt_page_header_space= ma_crypt_get_data_page_header_space();
  }

  for (column= columndef, end_column= column + columns ;
       column != end_column ;
       column++)
  {

    column->column_nr= column_nr++;
    column->offset= reclength;
    column->empty_pos= 0;
    column->empty_bit= 0;
    column->fill_length= column->length;
    if (column->null_bit)
      options|= HA_OPTION_NULL_FIELDS;

    reclength+= column->length;
    type= column->type;
    if (datafile_type == BLOCK_RECORD)
    {
      if (type == FIELD_SKIP_PRESPACE)
        type= column->type= FIELD_NORMAL;
      if (type == FIELD_NORMAL &&
          column->length > FULL_PAGE_SIZE2(maria_block_size,
                                           crypt_page_header_space))
      {

        type= column->type= FIELD_SKIP_ENDSPACE;
      }
    }

    if (type != FIELD_NORMAL && type != FIELD_CHECK)
    {
      column->empty_pos= packed/8;
      column->empty_bit= (1 << (packed & 7));
      if (type == FIELD_BLOB)
      {
        forced_packed= 1;
        packed++;
	share.base.blobs++;
	if (pack_reclength != INT_MAX32)
	{
	  if (column->length == 4+portable_sizeof_char_ptr)
	    pack_reclength= INT_MAX32;
	  else
          {

	    pack_reclength+= (1 << ((column->length-
                                     portable_sizeof_char_ptr)*8));
          }
	}
        max_field_lengths+= (column->length - portable_sizeof_char_ptr);
      }
      else if (type == FIELD_SKIP_PRESPACE ||
	       type == FIELD_SKIP_ENDSPACE)
      {
        forced_packed= 1;
        max_field_lengths+= column->length > 255 ? 2 : 1;
        not_block_record_extra_length++;
        packed++;
      }
      else if (type == FIELD_VARCHAR)
      {
	pack_reclength++;
        not_block_record_extra_length++;
        max_field_lengths++;
        if (datafile_type != DYNAMIC_RECORD)
          packed++;
        column->fill_length= 1;
        options|= HA_OPTION_NULL_FIELDS;


        if (MY_TEST(column->length >= 257))
	{
	  long_varchar_count++;
          max_field_lengths++;
          column->fill_length= 2;
	}
      }
      else if (type == FIELD_SKIP_ZERO)
        packed++;
      else
      {
        if (!column->null_bit)
          min_pack_length+= column->length;
        else
        {

          not_block_record_extra_length+= column->length;
        }
        column->empty_pos= 0;
        column->empty_bit= 0;
      }
    }
    else
    {
      if (!column->null_bit)
      {
        min_pack_length+= column->length;
        share.base.fixed_not_null_fields++;
        share.base.fixed_not_null_fields_length+= column->length;
      }
      else
        not_block_record_extra_length+= column->length;
    }
  }

  if (datafile_type == STATIC_RECORD && forced_packed)
  {

    datafile_type= BLOCK_RECORD;
  }

  if (datafile_type == NO_RECORD && uniques)
  {

    datafile_type= BLOCK_RECORD;
  }

  if (encrypted)
  {


    if (datafile_type != BLOCK_RECORD)
    {
      encrypted= FALSE;
      crypt_page_header_space= 0;
    }
  }

  if (datafile_type == DYNAMIC_RECORD)
    options|= HA_OPTION_PACK_RECORD;

  if (datafile_type == STATIC_RECORD || datafile_type == NO_RECORD)
  {

    flags&= ~HA_CREATE_CHECKSUM;
    options&= ~HA_OPTION_CHECKSUM;
    min_pack_length= reclength;
    packed= 0;
  }
  else if (datafile_type != BLOCK_RECORD)
    min_pack_length+= not_block_record_extra_length;
  else
    min_pack_length+= 5;

  if (flags & HA_CREATE_TMP_TABLE)
  {
    options|= HA_OPTION_TMP_TABLE;
    tmp_table= TRUE;
    create_mode|= O_NOFOLLOW | (internal_table ? 0 : O_EXCL);

    ci->transactional= FALSE;
    flags&= ~HA_CREATE_PAGE_CHECKSUM;
  }
  share.base.null_bytes= ci->null_bytes;
  share.base.original_null_bytes= ci->null_bytes;
  share.base.born_transactional= ci->transactional;
  share.base.max_field_lengths= max_field_lengths;
  share.base.field_offsets= 0;

  if (flags & HA_CREATE_CHECKSUM || (options & HA_OPTION_CHECKSUM))
  {
    options|= HA_OPTION_CHECKSUM;
    min_pack_length++;
    pack_reclength++;
  }
  if (pack_reclength < INT_MAX32)
    pack_reclength+= max_field_lengths + long_varchar_count;
  else
    pack_reclength= INT_MAX32;

  if (flags & HA_CREATE_DELAY_KEY_WRITE)
    options|= HA_OPTION_DELAY_KEY_WRITE;
  if (flags & HA_CREATE_RELIES_ON_SQL_LAYER)
    options|= HA_OPTION_RELIES_ON_SQL_LAYER;
  if (flags & HA_CREATE_PAGE_CHECKSUM)
    options|= HA_OPTION_PAGE_CHECKSUM;

  pack_bytes= (packed + 7) / 8;
  if (pack_reclength != INT_MAX32)
    pack_reclength+= reclength+pack_bytes +
      MY_TEST(test_all_bits(options, HA_OPTION_CHECKSUM |
                                     HA_OPTION_PACK_RECORD));
  min_pack_length+= pack_bytes;

  extra_header_size= MAX_FIXED_HEADER_SIZE;
  if (ci->transactional)
  {
    extra_header_size= TRANS_MAX_FIXED_HEADER_SIZE;
    DBUG_PRINT("info",("creating a transactional table"));
  }
  share.base.min_block_length= (extra_header_size + share.base.null_bytes +
                                pack_bytes);
  if (!ci->data_file_length && ci->max_rows)
  {
    set_if_bigger(ci->max_rows, ci->reloc_rows);
    if (pack_reclength == INT_MAX32 ||
             (~(ulonglong) 0)/ci->max_rows < (ulonglong) pack_reclength)
      ci->data_file_length= ~(ulonglong) 0;
    else
    {
      ci->data_file_length= _ma_safe_mul(ci->max_rows, pack_reclength);
      if (datafile_type == BLOCK_RECORD)
      {

        ci->data_file_length= _ma_safe_mul(ci->data_file_length, 2);
        set_if_bigger(ci->data_file_length, maria_block_size*2);
      }
    }
  }
  else if (!ci->max_rows)
  {
    if (datafile_type == BLOCK_RECORD)
    {
      uint rows_per_page=
          ((maria_block_size - PAGE_OVERHEAD_SIZE_RAW - crypt_page_header_space)
           / (min_pack_length + extra_header_size + DIR_ENTRY_SIZE));
      ulonglong data_file_length= ci->data_file_length;
      if (!data_file_length)
        data_file_length= ((((ulonglong) 1 << ((BLOCK_RECORD_POINTER_SIZE-1) *
                                               8))/2 -1) * maria_block_size);
      if (rows_per_page > 0)
      {
        set_if_smaller(rows_per_page, MAX_ROWS_PER_PAGE);
        ci->max_rows= (data_file_length / maria_block_size+1) * rows_per_page;
      }
      else
        ci->max_rows= data_file_length / (min_pack_length +
                                          extra_header_size +
                                          DIR_ENTRY_SIZE);
    }
    else
      ci->max_rows=(ha_rows) (ci->data_file_length/(min_pack_length +
                                                    ((options &
                                                      HA_OPTION_PACK_RECORD) ?
                                                     3 : 0)));
    set_if_smaller(ci->reloc_rows, ci->max_rows);
  }
  max_rows= (ulonglong) ci->max_rows;
  if (datafile_type == BLOCK_RECORD)
  {


    pointer= maria_get_pointer_length((ci->data_file_length /
                                       maria_block_size) * 2, 4) + 1;
    set_if_smaller(pointer, BLOCK_RECORD_POINTER_SIZE);

    if (!max_rows)
      max_rows= (((((ulonglong) 1 << ((pointer-1)*8)) -1) * maria_block_size) /
                 min_pack_length / 2);
                                      }
  else
  {
    if (datafile_type == NO_RECORD)
      pointer= 0;
    else if (datafile_type != STATIC_RECORD)
      pointer= maria_get_pointer_length(ci->data_file_length,
                                        maria_data_pointer_size);
    else
      pointer= maria_get_pointer_length(ci->max_rows, maria_data_pointer_size);
    if (!max_rows)
      max_rows= ((((ulonglong) 1 << (pointer*8)) -1) / min_pack_length);
  }

  real_reclength=reclength;
  if (datafile_type == STATIC_RECORD)
  {
    if (reclength <= pointer)
      reclength=pointer+1;
  }
  else
    reclength+= long_varchar_count;

  max_key_length=0; tot_length=0 ; key_segs=0;
  fulltext_keys=0;
  share.state.rec_per_key_part=   rec_per_key_part;
  share.state.nulls_per_key_part= nulls_per_key_part;
  share.state.key_root=key_root;
  share.state.key_del= HA_OFFSET_ERROR;
  if (uniques)
    max_key_length= MARIA_UNIQUE_HASH_LENGTH + pointer;

  for (i=0, keydef=keydefs ; i < keys ; i++ , keydef++)
  {
    share.state.key_root[i]= HA_OFFSET_ERROR;
    length= real_length_diff= 0;
    min_key_length= key_length= pointer;

    if (keydef->key_alg == HA_KEY_ALG_RTREE)
      keydef->flag|= HA_RTREE_INDEX;

    if (keydef->flag & HA_SPATIAL)
    {
#ifdef HAVE_SPATIAL

      uint sp_segs=SPDIMS*2;
      keydef->flag=HA_SPATIAL;

      if (flags & HA_DONT_TOUCH_DATA)
      {


        keydef->keysegs-=sp_segs-1;
      }

      for (j=0, keyseg=keydef->seg ; (int) j < keydef->keysegs ;
	   j++, keyseg++)
      {
        if (keyseg->type != HA_KEYTYPE_BINARY &&
	    keyseg->type != HA_KEYTYPE_VARBINARY1 &&
            keyseg->type != HA_KEYTYPE_VARBINARY2)
        {
          my_errno=HA_WRONG_CREATE_OPTION;
          goto err_no_lock;
        }
      }
      keydef->keysegs+=sp_segs;
      key_length+=SPLEN*sp_segs;
      length++;
      min_key_length++;
#else
      my_errno= HA_ERR_UNSUPPORTED;
      goto err_no_lock;
#endif
    }
    else if (keydef->flag & HA_FULLTEXT)
    {
      keydef->flag=HA_FULLTEXT | HA_PACK_KEY | HA_VAR_LENGTH_KEY;
      options|=HA_OPTION_PACK_KEYS;

      for (j=0, keyseg=keydef->seg ; (int) j < keydef->keysegs ;
	   j++, keyseg++)
      {
        if (keyseg->type != HA_KEYTYPE_TEXT &&
	    keyseg->type != HA_KEYTYPE_VARTEXT1 &&
            keyseg->type != HA_KEYTYPE_VARTEXT2)
        {
          my_errno=HA_WRONG_CREATE_OPTION;
          goto err_no_lock;
        }
        if (!(keyseg->flag & HA_BLOB_PART) &&
	    (keyseg->type == HA_KEYTYPE_VARTEXT1 ||
             keyseg->type == HA_KEYTYPE_VARTEXT2))
        {

          keyseg->flag|= HA_VAR_LENGTH_PART;

          keyseg->bit_start= ((keyseg->type == HA_KEYTYPE_VARTEXT1)?
                              1 : 2);
        }
      }

      fulltext_keys++;
      key_length+= HA_FT_MAXBYTELEN+HA_FT_WLEN;
      length++;
      min_key_length+= 1 + HA_FT_WLEN;
      real_length_diff=HA_FT_MAXBYTELEN-FT_MAX_WORD_LEN_FOR_SORT;
    }
    else
    {

      if (keydef->flag & HA_PACK_KEY)
      {

	if ((keydef->seg[0].flag & HA_SPACE_PACK) &&
	    keydef->seg[0].type == (int) HA_KEYTYPE_NUM)
	  keydef->seg[0].flag&= ~HA_SPACE_PACK;


	if (!(keydef->seg[0].flag & (HA_SPACE_PACK | HA_BLOB_PART |
				     HA_VAR_LENGTH_PART)))
	{

	  keydef->flag&= ~HA_PACK_KEY;
	  keydef->flag|= HA_BINARY_PACK_KEY | HA_VAR_LENGTH_KEY;
	}
	else
	{
	  keydef->seg[0].flag|=HA_PACK_KEY;
	  keydef->flag|=HA_VAR_LENGTH_KEY;
	  options|=HA_OPTION_PACK_KEYS;
	}
      }
      if (keydef->flag & HA_BINARY_PACK_KEY)
	options|=HA_OPTION_PACK_KEYS;

      if (keydef->flag & HA_AUTO_KEY && ci->with_auto_increment)
	share.base.auto_key=i+1;
      for (j=0, keyseg=keydef->seg ; j < keydef->keysegs ; j++, keyseg++)
      {

	switch (keyseg->type) {
	case HA_KEYTYPE_SHORT_INT:
	case HA_KEYTYPE_LONG_INT:
	case HA_KEYTYPE_FLOAT:
	case HA_KEYTYPE_DOUBLE:
	case HA_KEYTYPE_USHORT_INT:
	case HA_KEYTYPE_ULONG_INT:
	case HA_KEYTYPE_LONGLONG:
	case HA_KEYTYPE_ULONGLONG:
	case HA_KEYTYPE_INT24:
	case HA_KEYTYPE_UINT24:
	case HA_KEYTYPE_INT8:
	  keyseg->flag|= HA_SWAP_KEY;
          break;
        case HA_KEYTYPE_VARTEXT1:
        case HA_KEYTYPE_VARTEXT2:
        case HA_KEYTYPE_VARBINARY1:
        case HA_KEYTYPE_VARBINARY2:
          if (!(keyseg->flag & HA_BLOB_PART))
          {

            keyseg->flag|= HA_VAR_LENGTH_PART;

            keyseg->bit_start= ((keyseg->type == HA_KEYTYPE_VARTEXT1 ||
                                 keyseg->type == HA_KEYTYPE_VARBINARY1) ?
                                1 : 2);
          }
          break;
	default:
	  break;
	}
	if (keyseg->flag & HA_SPACE_PACK)
	{
          DBUG_ASSERT(!(keyseg->flag & (HA_VAR_LENGTH_PART | HA_BLOB_PART)));
	  keydef->flag |= HA_SPACE_PACK_USED | HA_VAR_LENGTH_KEY;
	  options|=HA_OPTION_PACK_KEYS;
	  length++;
          if (!keyseg->null_bit)
            min_key_length++;
          key_length+= keyseg->length;
	  if (keyseg->length >= 255)
	  {

	    length+= 2;
	  }
	}
	else if (keyseg->flag & (HA_VAR_LENGTH_PART | HA_BLOB_PART))
	{
          DBUG_ASSERT(!test_all_bits(keyseg->flag,
                                    (HA_VAR_LENGTH_PART | HA_BLOB_PART)));
	  keydef->flag|=HA_VAR_LENGTH_KEY;
	  length++;
          if (!keyseg->null_bit)
            min_key_length++;
	  options|=HA_OPTION_PACK_KEYS;
          key_length+= keyseg->length;
	  if (keyseg->length >= 255)
	  {

	    length+= 2;
	  }
	}
        else
        {
          key_length+= keyseg->length;
          if (!keyseg->null_bit)
            min_key_length+= keyseg->length;
        }
	if (keyseg->null_bit)
	{
	  key_length++;

          min_key_length++;
	  options|=HA_OPTION_PACK_KEYS;
	  keyseg->flag|=HA_NULL_PART;
	  keydef->flag|=HA_VAR_LENGTH_KEY | HA_NULL_PART_KEY;
	}
      }
    }
    key_segs+=keydef->keysegs;
    if (keydef->keysegs > HA_MAX_KEY_SEG)
    {
      my_errno=HA_WRONG_CREATE_OPTION;
      goto err_no_lock;
    }


    if ((keydef->flag & (HA_NOSAME | HA_NULL_PART_KEY)) == HA_NOSAME &&
	key_segs)
      share.state.rec_per_key_part[key_segs-1]=1L;
    length+=key_length;


    if (length > _ma_max_key_length())
    {
      my_errno=HA_WRONG_CREATE_OPTION;
      goto err_no_lock;
    }
    keydef->block_length= (uint16) maria_block_size;
    keydef->keylength= (uint16) key_length;
    keydef->minlength= (uint16) min_key_length;
    keydef->maxlength= (uint16) length;

    if (length > max_key_length)
      max_key_length= length;

    tot_length= update_tot_length(tot_length, max_rows, length);
  }

  unique_key_parts=0;
  for (i=0, uniquedef=uniquedefs ; i < uniques ; i++ , uniquedef++)
  {
    uniquedef->key=keys+i;
    unique_key_parts+=uniquedef->keysegs;
    share.state.key_root[keys+i]= HA_OFFSET_ERROR;

    tot_length= update_tot_length(tot_length, max_rows, MARIA_UNIQUE_HASH_LENGTH + pointer);
  }
  keys+=uniques;
  key_segs+=uniques;

  base_pos=(MARIA_STATE_INFO_SIZE + keys * MARIA_STATE_KEY_SIZE +
	    key_segs * MARIA_STATE_KEYSEG_SIZE);
  info_length= base_pos+(uint) (MARIA_BASE_INFO_SIZE+
                                keys * MARIA_KEYDEF_SIZE+
                                uniques * MARIA_UNIQUEDEF_SIZE +
                                (key_segs + unique_key_parts)*HA_KEYSEG_SIZE+
                                columns*(MARIA_COLUMNDEF_SIZE + 2));

  if (encrypted)
  {
    share.base.extra_options|= MA_EXTRA_OPTIONS_ENCRYPTED;


    info_length+= ma_crypt_get_file_length();
  }

  if (insert_order)
  {
    share.base.extra_options|= MA_EXTRA_OPTIONS_INSERT_ORDER;
  }

  share.state.state.key_file_length= MY_ALIGN(info_length, maria_block_size);
  DBUG_PRINT("info", ("info_length: %u", info_length));

  if (share.state.state.key_file_length > 65535)
  {
    my_printf_error(HA_WRONG_CREATE_OPTION,
                    "Aria table '%s' has too many columns and/or "
                    "indexes and/or unique constraints.",
                    MYF(0), name + dirname_length(name));
    my_errno= HA_WRONG_CREATE_OPTION;
    goto err_no_lock;
  }

  bmove(share.state.header.file_version, maria_file_magic, 4);
  ci->old_options=options | (ci->old_options & HA_OPTION_TEMP_COMPRESS_RECORD ?
                             HA_OPTION_COMPRESS_RECORD |
                             HA_OPTION_TEMP_COMPRESS_RECORD: 0);
  mi_int2store(share.state.header.options,ci->old_options);
  mi_int2store(share.state.header.header_length,info_length);
  mi_int2store(share.state.header.state_info_length,MARIA_STATE_INFO_SIZE);
  mi_int2store(share.state.header.base_info_length,MARIA_BASE_INFO_SIZE);
  mi_int2store(share.state.header.base_pos,base_pos);
  share.state.header.data_file_type= share.data_file_type= datafile_type;
  share.state.header.org_data_file_type= org_datafile_type;
  share.state.header.not_used= 0;

  share.state.dellink = HA_OFFSET_ERROR;
  share.state.first_bitmap_with_space= 0;
#ifdef MARIA_EXTERNAL_LOCKING
  share.state.process=	(ulong) getpid();
#endif
  share.state.version=	(ulong) time((time_t*) 0);
  share.state.sortkey=  (ushort) ~0;
  share.state.auto_increment=ci->auto_increment;
  share.options=options;
  share.base.rec_reflength=pointer;
  share.base.block_size= maria_block_size;
  share.base.language= (ci->language ? ci->language :
                        default_charset_info->number);


  tmp= (tot_length / maria_block_size + keys * MARIA_INDEX_BLOCK_MARGIN);


  share.base.key_reflength=
    maria_get_pointer_length(MY_MAX(ci->key_file_length,tmp),3);
  share.base.keys= share.state.header.keys= keys;
  share.state.header.uniques= uniques;
  share.state.header.fulltext_keys= fulltext_keys;
  mi_int2store(share.state.header.key_parts,key_segs);
  mi_int2store(share.state.header.unique_key_parts,unique_key_parts);

  maria_set_all_keys_active(share.state.key_map, keys);

  share.base.keystart = share.state.state.key_file_length;
  share.base.max_key_block_length= maria_block_size;
  share.base.max_key_length=ALIGN_SIZE(max_key_length+4);
  share.base.records=ci->max_rows;
  share.base.reloc=  ci->reloc_rows;
  share.base.reclength=real_reclength;
  share.base.pack_reclength= reclength + MY_TEST(options & HA_OPTION_CHECKSUM);
  share.base.max_pack_length=pack_reclength;
  share.base.min_pack_length=min_pack_length;
  share.base.pack_bytes= pack_bytes;
  share.base.fields= columns;
  share.base.pack_fields= packed;

  if (share.data_file_type == BLOCK_RECORD)
  {


    share.state.state.data_file_length= maria_block_size;

    share.base.pack_reclength+= share.base.max_field_lengths+3;
    share.base.max_pack_length= share.base.pack_reclength;


    if (share.base.max_pack_length < maria_block_size)
    {
      share.base.max_pack_length+= FLAG_SIZE;
      if (ci->transactional)
        share.base.max_pack_length+= TRANSID_SIZE * 2;
    }
  }


  if (tmp_table)
    share.base.max_data_file_length= (my_off_t) ci->data_file_length;
  else if (ci->transactional && translog_status == TRANSLOG_OK &&
           !maria_in_recovery)
  {


    sync_dir= MY_SYNC_DIR;


    share.state.skip_redo_lsn= share.state.is_of_horizon=
      share.state.create_rename_lsn= LSN_MAX;
  }

  if (datafile_type == DYNAMIC_RECORD)
  {
    share.base.min_block_length=
      (share.base.pack_reclength+3 < MARIA_EXTEND_BLOCK_LENGTH &&
       ! share.base.blobs) ?
      MY_MAX(share.base.pack_reclength,MARIA_MIN_BLOCK_LENGTH) :
      MARIA_EXTEND_BLOCK_LENGTH;
  }
  else if (datafile_type == STATIC_RECORD)
    share.base.min_block_length= share.base.pack_reclength;

  if (! (flags & HA_DONT_TOUCH_DATA))
    share.state.create_time= time((time_t*) 0);

  if (!internal_table)
    mysql_mutex_lock(&THR_LOCK_maria);


  if (ci->index_file_name)
  {
    char *iext= strrchr(ci->index_file_name, '.');
    int have_iext= iext && !strcmp(iext, MARIA_NAME_IEXT);
    if (tmp_table)
    {
      char *path;

      if ((path= strrchr(ci->index_file_name, FN_LIBCHAR)))
        *path= '\0';
      fn_format(kfilename, name, ci->index_file_name, MARIA_NAME_IEXT,
                MY_REPLACE_DIR | MY_UNPACK_FILENAME |
                MY_RETURN_REAL_PATH | MY_APPEND_EXT);
    }
    else
    {
      fn_format(kfilename, ci->index_file_name, "", MARIA_NAME_IEXT,
                MY_UNPACK_FILENAME | MY_RETURN_REAL_PATH |
                (have_iext ? MY_REPLACE_EXT : MY_APPEND_EXT));
    }
    fn_format(klinkname, name, "", MARIA_NAME_IEXT,
              MY_UNPACK_FILENAME|MY_APPEND_EXT);
    klinkname_ptr= klinkname;


    create_flag=
      (ci->data_file_name &&
       !strcmp(ci->index_file_name, ci->data_file_name)) ? 0 : sync_dir;
  }
  else
  {
    char *iext= strrchr(name, '.');
    int have_iext= iext && !strcmp(iext, MARIA_NAME_IEXT);
    fn_format(kfilename, name, "", MARIA_NAME_IEXT, MY_UNPACK_FILENAME |
              (internal_table ? 0 : MY_RETURN_REAL_PATH) |
              (have_iext ? MY_REPLACE_EXT : MY_APPEND_EXT));


    create_flag=  (flags & HA_CREATE_KEEP_FILES) ? 0 : MY_DELETE_OLD;
    create_flag|= (!ci->data_file_name ? 0 : sync_dir);
  }


  if (!internal_table && _ma_test_if_reopen(kfilename))
  {
    my_printf_error(HA_ERR_TABLE_EXIST, "Aria table '%s' is in use "
                    "(most likely by a MERGE table). Try FLUSH TABLES.",
                    MYF(0), name + dirname_length(name));
    my_errno= HA_ERR_TABLE_EXIST;
    goto err;
  }

  if ((file= mysql_file_create_with_symlink(key_file_kfile, klinkname_ptr,
                                            kfilename, 0, create_mode,
                                            MYF(MY_WME|create_flag))) < 0)
    goto err;
  errpos=1;

  DBUG_PRINT("info", ("write state info and base info"));
  if (_ma_state_info_write_sub(file, &share.state,
                               MA_STATE_INFO_WRITE_FULL_INFO) ||
      _ma_base_info_write(file, &share.base))
    goto err;
  DBUG_PRINT("info", ("base_pos: %d  base_info_size: %d",
                      base_pos, MARIA_BASE_INFO_SIZE));
  DBUG_ASSERT(mysql_file_tell(file,MYF(0)) == base_pos+ MARIA_BASE_INFO_SIZE);


  DBUG_PRINT("info", ("write key and keyseg definitions"));
  for (i=0 ; i < share.base.keys - uniques; i++)
  {
    uint sp_segs=(keydefs[i].flag & HA_SPATIAL) ? 2*SPDIMS : 0;

    if (_ma_keydef_write(file, &keydefs[i]))
      goto err;
    for (j=0 ; j < keydefs[i].keysegs-sp_segs ; j++)
      if (_ma_keyseg_write(file, &keydefs[i].seg[j]))
       goto err;
#ifdef HAVE_SPATIAL
    for (j=0 ; j < sp_segs ; j++)
    {
      HA_KEYSEG sseg;
      sseg.type=SPTYPE;
      sseg.language= 7;
      sseg.null_bit=0;
      sseg.bit_start=0;
      sseg.bit_length= 0;
      sseg.bit_pos= 0;
      sseg.length=SPLEN;
      sseg.null_pos=0;
      sseg.start=j*SPLEN;
      sseg.flag= HA_SWAP_KEY;
      if (_ma_keyseg_write(file, &sseg))
        goto err;
    }
#endif
  }

  offset= real_reclength - uniques*MARIA_UNIQUE_HASH_LENGTH;
  bzero((char*) &tmp_keydef,sizeof(tmp_keydef));
  bzero((char*) &tmp_keyseg,sizeof(tmp_keyseg));
  for (i=0; i < uniques ; i++)
  {
    tmp_keydef.keysegs=1;
    tmp_keydef.flag=		HA_UNIQUE_CHECK;
    tmp_keydef.block_length=	(uint16) maria_block_size;
    tmp_keydef.keylength=	MARIA_UNIQUE_HASH_LENGTH + pointer;
    tmp_keydef.minlength=tmp_keydef.maxlength=tmp_keydef.keylength;
    tmp_keyseg.type=		MARIA_UNIQUE_HASH_TYPE;
    tmp_keyseg.length=		MARIA_UNIQUE_HASH_LENGTH;
    tmp_keyseg.start=		offset;
    offset+=			MARIA_UNIQUE_HASH_LENGTH;
    if (_ma_keydef_write(file,&tmp_keydef) ||
	_ma_keyseg_write(file,(&tmp_keyseg)))
      goto err;
  }


  DBUG_PRINT("info", ("write unique definitions"));
  for (i=0 ; i < share.state.header.uniques ; i++)
  {
    HA_KEYSEG *keyseg_end;
    keyseg= uniquedefs[i].seg;
    if (_ma_uniquedef_write(file, &uniquedefs[i]))
      goto err;
    for (keyseg= uniquedefs[i].seg, keyseg_end= keyseg+ uniquedefs[i].keysegs;
         keyseg < keyseg_end;
         keyseg++)
    {
      switch (keyseg->type) {
      case HA_KEYTYPE_VARTEXT1:
      case HA_KEYTYPE_VARTEXT2:
      case HA_KEYTYPE_VARBINARY1:
      case HA_KEYTYPE_VARBINARY2:
        if (!(keyseg->flag & HA_BLOB_PART))
        {
          keyseg->flag|= HA_VAR_LENGTH_PART;
          keyseg->bit_start= ((keyseg->type == HA_KEYTYPE_VARTEXT1 ||
                               keyseg->type == HA_KEYTYPE_VARBINARY1) ?
                              1 : 2);
        }
        break;
      default:
        DBUG_ASSERT((keyseg->flag & HA_VAR_LENGTH_PART) == 0);
        break;
      }
      if (_ma_keyseg_write(file, keyseg))
	goto err;
    }
  }
  DBUG_PRINT("info", ("write field definitions"));
  if (datafile_type == BLOCK_RECORD)
  {

    MARIA_COLUMNDEF **col_order, **pos;
    if (!(col_order= (MARIA_COLUMNDEF**) my_malloc(share.base.fields *
                                                   sizeof(MARIA_COLUMNDEF*),
                                                   MYF(MY_WME))))
      goto err;
    for (column= columndef, pos= col_order ;
         column != end_column ;
         column++, pos++)
      *pos= column;
    qsort(col_order, share.base.fields, sizeof(*col_order),
          (qsort_cmp) compare_columns);
    for (i=0 ; i < share.base.fields ; i++)
    {
      column_array[col_order[i]->column_nr]= i;
      if (_ma_columndef_write(file, col_order[i]))
      {
        my_free(col_order);
        goto err;
      }
    }
    my_free(col_order);
  }
  else
  {
    for (i=0 ; i < share.base.fields ; i++)
    {
      column_array[i]= (uint16) i;
      if (_ma_columndef_write(file, &columndef[i]))
        goto err;
    }
  }
  if (_ma_column_nr_write(file, column_array, columns))
    goto err;

  if (encrypted)
  {
    if (ma_crypt_create(&share) ||
        ma_crypt_write(&share, file))
      goto err;
  }

  if ((kfile_size_before_extension= mysql_file_tell(file,MYF(0))) == MY_FILEPOS_ERROR)
    goto err;
#ifndef DBUG_OFF
  if (kfile_size_before_extension != info_length)
    DBUG_PRINT("warning",("info_length: %u  != used_length: %u",
			  info_length, (uint)kfile_size_before_extension));
#endif

  if (sync_dir)
  {


    char empty_string[]= "";
    LEX_CUSTRING log_array[TRANSLOG_INTERNAL_PARTS + 4];
    translog_size_t total_rec_length= 0;
    uint k;
    LSN lsn;
    log_array[TRANSLOG_INTERNAL_PARTS + 1].length= 1 + 2 + 2 +
      (uint) kfile_size_before_extension;

    log_data= my_malloc(log_array[TRANSLOG_INTERNAL_PARTS + 1].length, MYF(0));
    if ((log_data == NULL) ||
        mysql_file_pread(file, 1 + 2 + 2 + log_data,
                 (size_t) kfile_size_before_extension, 0, MYF(MY_NABP)))
      goto err;


    log_data[0]= MY_TEST(flags & HA_DONT_TOUCH_DATA);
    int2store(log_data + 1, kfile_size_before_extension);
    int2store(log_data + 1 + 2, share.base.keystart);
    log_array[TRANSLOG_INTERNAL_PARTS + 0].str= (uchar *)name;

    log_array[TRANSLOG_INTERNAL_PARTS + 0].length= strlen(name) + 1;
    log_array[TRANSLOG_INTERNAL_PARTS + 1].str= log_data;

    {
      const char *s= ci->data_file_name ? ci->data_file_name : empty_string;
      log_array[TRANSLOG_INTERNAL_PARTS + 2].str= (uchar*)s;
      log_array[TRANSLOG_INTERNAL_PARTS + 2].length= strlen(s) + 1;
      s= ci->index_file_name ? ci->index_file_name : empty_string;
      log_array[TRANSLOG_INTERNAL_PARTS + 3].str= (uchar*)s;
      log_array[TRANSLOG_INTERNAL_PARTS + 3].length= strlen(s) + 1;
    }
    for (k= TRANSLOG_INTERNAL_PARTS;
         k < (sizeof(log_array)/sizeof(log_array[0])); k++)
      total_rec_length+= (translog_size_t) log_array[k].length;


    if (unlikely(translog_write_record(&lsn,
                                       LOGREC_REDO_CREATE_TABLE,
                                       &dummy_transaction_object, NULL,
                                       total_rec_length,
                                       sizeof(log_array)/sizeof(log_array[0]),
                                       log_array, NULL, NULL) ||
                 translog_flush(lsn)))
      goto err;
    share.kfile.file= file;
    DBUG_EXECUTE_IF("maria_flush_whole_log",
                    {
                      DBUG_PRINT("maria_flush_whole_log", ("now"));
                      translog_flush(translog_get_horizon());
                    });
    DBUG_EXECUTE_IF("maria_crash_create_table",
                    {
                      DBUG_PRINT("maria_crash_create_table", ("now"));
                      DBUG_ABORT();
                    });


    if (_ma_update_state_lsns_sub(&share, lsn, trnman_get_min_safe_trid(),
                                  FALSE, TRUE))
      goto err;
    my_free(log_data);
  }

  if (!(flags & HA_DONT_TOUCH_DATA))
  {
    if (ci->data_file_name)
    {
      char *dext= strrchr(ci->data_file_name, '.');
      int have_dext= dext && !strcmp(dext, MARIA_NAME_DEXT);

      if (tmp_table)
      {
        char *path;

        if ((path= strrchr(ci->data_file_name, FN_LIBCHAR)))
          *path= '\0';
        fn_format(dfilename, name, ci->data_file_name, MARIA_NAME_DEXT,
                  MY_REPLACE_DIR | MY_UNPACK_FILENAME | MY_APPEND_EXT);
      }
      else
      {
        fn_format(dfilename, ci->data_file_name, "", MARIA_NAME_DEXT,
                  MY_UNPACK_FILENAME |
                  (have_dext ? MY_REPLACE_EXT : MY_APPEND_EXT));
      }
      fn_format(dlinkname, name, "",MARIA_NAME_DEXT,
                MY_UNPACK_FILENAME | MY_APPEND_EXT);
      dlinkname_ptr= dlinkname;
      create_flag=0;
    }
    else
    {
      fn_format(dfilename,name,"", MARIA_NAME_DEXT,
                MY_UNPACK_FILENAME | MY_APPEND_EXT);
      create_flag= (flags & HA_CREATE_KEEP_FILES) ? 0 : MY_DELETE_OLD;
    }
    if ((dfile=
         mysql_file_create_with_symlink(key_file_dfile, dlinkname_ptr,
                                        dfilename, 0, create_mode,
                                        MYF(MY_WME | create_flag | sync_dir))) < 0)
      goto err;
    errpos=3;

    if (_ma_initialize_data_file(&share, dfile))
      goto err;
  }


  DBUG_PRINT("info", ("enlarge to keystart: %lu",
                      (ulong) share.base.keystart));
  if (mysql_file_chsize(file,(ulong) share.base.keystart,0,MYF(0)))
    goto err;

  if (!internal_table && sync_dir && mysql_file_sync(file, MYF(0)))
    goto err;

  if (! (flags & HA_DONT_TOUCH_DATA))
  {
#ifdef USE_RELOC
    if (mysql_file_chsize(key_file_dfile, dfile,
                          share.base.min_pack_length*ci->reloc_rows,0,MYF(0)))
      goto err;
#endif
    if (!internal_table && sync_dir && mysql_file_sync(dfile, MYF(0)))
      goto err;
    if (mysql_file_close(dfile,MYF(0)))
      goto err;
  }
  if (!internal_table)
    mysql_mutex_unlock(&THR_LOCK_maria);
  res= 0;
  my_free((char*) rec_per_key_part);
  ma_crypt_free(&share);
  errpos=0;
  if (mysql_file_close(file,MYF(0)))
    res= my_errno;
  DBUG_RETURN(res);

err:
  if (!internal_table)
    mysql_mutex_unlock(&THR_LOCK_maria);

err_no_lock:
  save_errno=my_errno;
  switch (errpos) {
  case 3:
    mysql_file_close(dfile, MYF(0));
    if (! (flags & HA_DONT_TOUCH_DATA))
    {
      mysql_file_delete(key_file_dfile, dfilename, MYF(sync_dir));
      if (dlinkname_ptr)
        mysql_file_delete(key_file_dfile, dlinkname_ptr, MYF(sync_dir));
    }

  case 1:
    mysql_file_close(file, MYF(0));
    if (! (flags & HA_DONT_TOUCH_DATA))
    {
      mysql_file_delete(key_file_kfile, kfilename, MYF(sync_dir));
      if (klinkname_ptr)
        mysql_file_delete(key_file_kfile, klinkname_ptr, MYF(sync_dir));
    }
  }
  ma_crypt_free(&share);
  my_free(log_data);
  my_free(rec_per_key_part);
  DBUG_RETURN(my_errno=save_errno);
}
