static bool create_ref_for_key(JOIN *join, JOIN_TAB *j,
                               KEYUSE *org_keyuse, bool allow_full_scan,
                               table_map used_tables)
{
  uint keyparts, length, key;
  TABLE *table;
  KEY *keyinfo;
  KEYUSE *keyuse= org_keyuse;
  bool ftkey= (keyuse->keypart == FT_KEYPART);
  THD *thd= join->thd;
  DBUG_ENTER("create_ref_for_key");


  table= j->table;
  key= keyuse->key;
  if (!is_hash_join_key_no(key))
    keyinfo= table->key_info+key;
  else
  {
    if (create_hj_key_for_table(join, j, org_keyuse, used_tables))
      DBUG_RETURN(TRUE);
    keyinfo= j->hj_key;
  }

  if (ftkey)
  {
    Item_func_match *ifm=(Item_func_match *)keyuse->val;

    length=0;
    keyparts=1;
    ifm->join_key=1;
  }
  else
  {
    keyparts=length=0;
    uint found_part_ref_or_null= 0;


    do
    {
      if (!(~used_tables & keyuse->used_tables) &&
          (!keyuse->validity_ref || *keyuse->validity_ref) &&
	  j->keyuse_is_valid_for_access_in_chosen_plan(join, keyuse))
      {
        if  (are_tables_local(j, keyuse->val->used_tables()))
        {
          if ((is_hash_join_key_no(key) && keyuse->keypart != NO_KEYPART) ||
              (!is_hash_join_key_no(key) && keyparts == keyuse->keypart &&
               !(found_part_ref_or_null & keyuse->optimize)))
          {
             length+= keyinfo->key_part[keyparts].store_length;
             keyparts++;
             found_part_ref_or_null|= keyuse->optimize & ~KEY_OPTIMIZE_EQ;
          }
        }
      }
      keyuse++;
    } while (keyuse->table == table && keyuse->key == key);

    if (!keyparts && allow_full_scan)
    {

      j->type= JT_ALL;
      j->index= key;
      DBUG_RETURN(FALSE);
    }

    DBUG_ASSERT(length > 0);
    DBUG_ASSERT(keyparts != 0);
  }


  j->ref.key_parts= keyparts;
  j->ref.key_length= length;
  j->ref.key= (int) key;
  if (!(j->ref.key_buff= (uchar*) thd->calloc(ALIGN_SIZE(length)*2)) ||
      !(j->ref.key_copy= (store_key**) thd->alloc((sizeof(store_key*) *
						          (keyparts+1)))) ||
      !(j->ref.items=(Item**) thd->alloc(sizeof(Item*)*keyparts)) ||
      !(j->ref.cond_guards= (bool**) thd->alloc(sizeof(uint*)*keyparts)))
  {
    DBUG_RETURN(TRUE);
  }
  j->ref.key_buff2=j->ref.key_buff+ALIGN_SIZE(length);
  j->ref.key_err=1;
  j->ref.has_record= FALSE;
  j->ref.null_rejecting= 0;
  j->ref.disable_cache= FALSE;
  j->ref.null_ref_part= NO_REF_PART;
  j->ref.const_ref_part_map= 0;
  j->ref.uses_splitting= FALSE;
  keyuse=org_keyuse;

  store_key **ref_key= j->ref.key_copy;
  uchar *key_buff=j->ref.key_buff, *null_ref_key= 0;
  uint null_ref_part= NO_REF_PART;
  bool keyuse_uses_no_tables= TRUE;
  uint not_null_keyparts= 0;
  if (ftkey)
  {
    j->ref.items[0]=((Item_func*)(keyuse->val))->key_item();

    j->ref.cond_guards[0]= NULL;
    if (keyuse->used_tables)
      DBUG_RETURN(TRUE);

    j->type=JT_FT;
  }
  else
  {
    uint i;
    for (i=0 ; i < keyparts ; keyuse++,i++)
    {
      while (((~used_tables) & keyuse->used_tables) ||
             (keyuse->validity_ref && !(*keyuse->validity_ref)) ||
	     !j->keyuse_is_valid_for_access_in_chosen_plan(join, keyuse) ||
             keyuse->keypart == NO_KEYPART ||
	     (keyuse->keypart !=
              (is_hash_join_key_no(key) ?
                 keyinfo->key_part[i].field->field_index : i)) ||
             !are_tables_local(j, keyuse->val->used_tables()))
	 keyuse++;

      uint maybe_null= MY_TEST(keyinfo->key_part[i].null_bit);
      j->ref.items[i]=keyuse->val;
      j->ref.cond_guards[i]= keyuse->cond_guard;

      if (!keyuse->val->maybe_null || keyuse->null_rejecting)
        not_null_keyparts++;


      Item *real= (keyuse->val)->real_item();
      if (keyuse->null_rejecting && (real->type() == Item::FIELD_ITEM) &&
          ((Item_field*)real)->field->maybe_null())
        j->ref.null_rejecting|= (key_part_map)1 << i;

      keyuse_uses_no_tables= keyuse_uses_no_tables && !keyuse->used_tables;
      j->ref.uses_splitting |= (keyuse->validity_ref != NULL);


      if (!keyuse->val->used_tables() && !thd->lex->describe)
      {
        store_key_item tmp(thd,
                           keyinfo->key_part[i].field,
                           key_buff + maybe_null,
                           maybe_null ?  key_buff : 0,
                           keyinfo->key_part[i].length,
                           keyuse->val,
                           FALSE);
        if (unlikely(thd->is_fatal_error))
          DBUG_RETURN(TRUE);
        tmp.copy();
        j->ref.const_ref_part_map |= key_part_map(1) << i ;
      }
      else
      {
        *ref_key++= get_store_key(thd,
                                  keyuse,join->const_table_map,
                                  &keyinfo->key_part[i],
                                  key_buff, maybe_null);
        if (!keyuse->val->used_tables())
          j->ref.const_ref_part_map |= key_part_map(1) << i ;
      }


      if ((keyuse->optimize & KEY_OPTIMIZE_REF_OR_NULL) && maybe_null)
      {
	null_ref_key= key_buff;
        null_ref_part= i;
      }
      key_buff+= keyinfo->key_part[i].store_length;
    }
  }
  *ref_key=0;
  if (j->type == JT_FT)
    DBUG_RETURN(0);
  ulong key_flags= j->table->actual_key_flags(keyinfo);
  if (j->type == JT_CONST)
    j->table->const_table= 1;
  else if (!((keyparts == keyinfo->user_defined_key_parts &&
              (
                (key_flags & (HA_NOSAME | HA_NULL_PART_KEY)) == HA_NOSAME ||

                ((key_flags & HA_NOSAME) && keyparts == not_null_keyparts)
              )) ||

              (keyparts > keyinfo->user_defined_key_parts &&
               MY_TEST(key_flags & HA_EXT_NOSAME) &&
               keyparts == keyinfo->ext_key_parts)
            ) ||
            null_ref_key)
  {

    j->type= null_ref_key ? JT_REF_OR_NULL : JT_REF;
    j->ref.null_ref_key= null_ref_key;
    j->ref.null_ref_part= null_ref_part;
  }
  else if (keyuse_uses_no_tables)
  {


    j->type=JT_CONST;
  }
  else
    j->type=JT_EQ_REF;

  j->read_record.unlock_row= (j->type == JT_EQ_REF)?
                             join_read_key_unlock_row : rr_unlock_row;
  DBUG_RETURN(0);
}
