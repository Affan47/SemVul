key_cmp_if_same(TABLE *table,const uchar *key,uint idx,uint key_length)
{
  uint store_length;
  KEY_PART_INFO *key_part;
  const uchar *key_end= key + key_length;;

  for (key_part=table->key_info[idx].key_part;
       key < key_end ;
       key_part++, key+= store_length)
  {
    uint length;
    store_length= key_part->store_length;

    if (key_part->null_bit)
    {
      if (*key != test(table->record[0][key_part->null_offset] &
		       key_part->null_bit))
	return 1;
      if (*key)
	continue;
      key++;
      store_length--;
    }
    if (key_part->key_part_flag & (HA_BLOB_PART | HA_VAR_LENGTH_PART |
                                   HA_BIT_PART))
    {
      if (key_part->field->key_cmp(key, key_part->length))
	return 1;
      continue;
    }
    length= min((uint) (key_end-key), store_length);
    if (!(key_part->key_type & (FIELDFLAG_NUMBER+FIELDFLAG_BINARY+
                                FIELDFLAG_PACK)))
    {
      CHARSET_INFO *cs= key_part->field->charset();
      uint char_length= key_part->length / cs->mbmaxlen;
      const uchar *pos= table->record[0] + key_part->offset;
      if (length > char_length)
      {
        char_length= my_charpos(cs, pos, pos + length, char_length);
        set_if_smaller(char_length, length);
      }
      if (cs->coll->strnncollsp(cs,
                                (const uchar*) key, length,
                                (const uchar*) pos, char_length, 0))
        return 1;
      continue;
    }
    if (memcmp(key,table->record[0]+key_part->offset,length))
      return 1;
  }
  return 0;
}
