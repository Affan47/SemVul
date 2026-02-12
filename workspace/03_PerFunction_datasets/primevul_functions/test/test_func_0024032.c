double table_cond_selectivity(JOIN *join, uint idx, JOIN_TAB *s,
                              table_map rem_tables)
{
  uint16 ref_keyuse_steps_buf[MAX_REF_PARTS];
  uint   ref_keyuse_size= MAX_REF_PARTS;
  uint16 *ref_keyuse_steps= ref_keyuse_steps_buf;
  Field *field;
  TABLE *table= s->table;
  MY_BITMAP *read_set= table->read_set;
  double sel= s->table->cond_selectivity;
  POSITION *pos= &join->positions[idx];
  uint keyparts= 0;
  uint found_part_ref_or_null= 0;

  if (pos->key != 0)
  {


    KEYUSE *keyuse= pos->key;
    KEYUSE *prev_ref_keyuse= keyuse;
    uint key= keyuse->key;
    bool used_range_selectivity= false;


    if (!is_hash_join_key_no(key))
    {
      key_part_map quick_key_map= (key_part_map(1) << table->quick_key_parts[key]) - 1;
      if (table->quick_rows[key] &&
          !(quick_key_map & ~table->const_key_parts[key]))
      {


        for (; quick_key_map & 1 ; quick_key_map>>= 1)
        {
          while (keyuse->table == table && keyuse->key == key &&
                 keyuse->keypart == keyparts)
          {
            keyuse++;
          }
          keyparts++;
        }


        sel /= (double)table->quick_rows[key] / (double) table->stat_records();
        set_if_smaller(sel, 1.0);
        used_range_selectivity= true;
      }
    }


    keyuse= pos->key;
    keyparts=0;
    while (keyuse->table == table && keyuse->key == key)
    {
      if (!(keyuse->used_tables & (rem_tables | table->map)))
      {
        if (are_tables_local(s, keyuse->val->used_tables()))
	{
          if (is_hash_join_key_no(key))
	  {
            if (keyparts == keyuse->keypart)
              keyparts++;
          }
          else
	  {
            if (keyparts == keyuse->keypart &&
                !((keyuse->val->used_tables()) & ~pos->ref_depend_map) &&
                !(found_part_ref_or_null & keyuse->optimize))
	    {

              keyparts++;
              found_part_ref_or_null|= keyuse->optimize & ~KEY_OPTIMIZE_EQ;
            }
          }

          if (keyparts > keyuse->keypart)
	  {

            if (!used_range_selectivity && keyuse->val->const_item())
            {
              uint fldno;
              if (is_hash_join_key_no(key))
                fldno= keyuse->keypart;
              else
                fldno= table->key_info[key].key_part[keyparts-1].fieldnr - 1;

              if (table->field[fldno]->cond_selectivity > 0)
	      {
                sel /= table->field[fldno]->cond_selectivity;
                set_if_smaller(sel, 1.0);
              }


            }
            if (keyparts > 1)
	    {


              if (keyparts - 2 >= ref_keyuse_size)
              {
                uint new_size= MY_MAX(ref_keyuse_size*2, keyparts);
                void *new_buf;
                if (!(new_buf= my_malloc(sizeof(*ref_keyuse_steps)*new_size,
                                         MYF(0))))
                {
                  sel= 1.0;
                  goto exit;
                }
                memcpy(new_buf, ref_keyuse_steps,
                       sizeof(*ref_keyuse_steps)*ref_keyuse_size);
                if (ref_keyuse_steps != ref_keyuse_steps_buf)
                  my_free(ref_keyuse_steps);

                ref_keyuse_steps= (uint16*)new_buf;
                ref_keyuse_size= new_size;
              }

              ref_keyuse_steps[keyparts-2]= (uint16)(keyuse - prev_ref_keyuse);
              prev_ref_keyuse= keyuse;
            }
          }
	}
      }
      keyuse++;
    }
  }
  else
  {


    sel= 1;
  }


  if (pos->key != NULL)
  {
    for (Field **f_ptr=table->field ; (field= *f_ptr) ; f_ptr++)
    {
      if (!bitmap_is_set(read_set, field->field_index) ||
          !field->next_equal_field)
        continue;
      for (Field *next_field= field->next_equal_field;
           next_field != field;
           next_field= next_field->next_equal_field)
      {
        if (!(next_field->table->map & rem_tables) && next_field->table != table)
        {
          if (field->cond_selectivity > 0)
	  {
            sel/= field->cond_selectivity;
            set_if_smaller(sel, 1.0);
          }
          break;
        }
      }
    }
  }

  sel*= table_multi_eq_cond_selectivity(join, idx, s, rem_tables,
                                        keyparts, ref_keyuse_steps);
exit:
  if (ref_keyuse_steps != ref_keyuse_steps_buf)
    my_free(ref_keyuse_steps);
  return sel;
}
