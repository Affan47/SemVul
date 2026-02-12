static int test_if_order_by_key(JOIN *join,
                                ORDER *order, TABLE *table, uint idx,
				uint *used_key_parts= NULL)
{
  KEY_PART_INFO *key_part,*key_part_end;
  key_part=table->key_info[idx].key_part;
  key_part_end=key_part + table->key_info[idx].ext_key_parts;
  key_part_map const_key_parts=table->const_key_parts[idx];
  uint user_defined_kp= table->key_info[idx].user_defined_key_parts;
  int reverse=0;
  uint key_parts;
  bool have_pk_suffix= false;
  uint pk= table->s->primary_key;
  DBUG_ENTER("test_if_order_by_key");

  if ((table->file->ha_table_flags() & HA_PRIMARY_KEY_IN_READ_INDEX) &&
      table->key_info[idx].ext_key_part_map &&
      pk != MAX_KEY && pk != idx)
  {
    have_pk_suffix= true;
  }

  for (; order ; order=order->next, const_key_parts>>=1)
  {
    Item_field *item_field= ((Item_field*) (*order->item)->real_item());
    Field *field= item_field->field;
    int flag;


    for (; const_key_parts & 1 ; const_key_parts>>= 1)
      key_part++;


    key_parts= (uint)(key_part - table->key_info[idx].key_part);
    if (have_pk_suffix &&
        reverse == 0 &&
        key_parts == table->key_info[idx].ext_key_parts &&
        table->const_key_parts[pk] == PREV_BITS(uint,
                                                table->key_info[pk].
                                                user_defined_key_parts))
    {
      key_parts= 0;
      reverse= 1;
      goto ok;
    }

    if (key_part == key_part_end)
    {


      DBUG_RETURN(0);
    }

    if (key_part->field != field)
    {


      if (item_field->item_equal &&
          item_field->item_equal->contains(key_part->field))
        field= key_part->field;
    }
    if (key_part->field != field || !field->part_of_sortkey.is_set(idx))
      DBUG_RETURN(0);

    const ORDER::enum_order keypart_order=
      (key_part->key_part_flag & HA_REVERSE_SORT) ?
      ORDER::ORDER_DESC : ORDER::ORDER_ASC;

    flag= (order->direction == keypart_order) ? 1 : -1;
    if (reverse && flag != reverse)
      DBUG_RETURN(0);
    reverse=flag;
    if (key_part < key_part_end)
      key_part++;
  }

  key_parts= (uint) (key_part - table->key_info[idx].key_part);

  if (reverse == -1 &&
      !(table->file->index_flags(idx, user_defined_kp-1, 1) & HA_READ_PREV))
    reverse= 0;

  if (have_pk_suffix && reverse == -1)
  {
    uint pk_parts= table->key_info[pk].user_defined_key_parts;
    if (!(table->file->index_flags(pk, pk_parts, 1) & HA_READ_PREV))
      reverse= 0;
  }

ok:
  if (used_key_parts != NULL)
    *used_key_parts= key_parts;
  DBUG_RETURN(reverse);
}
