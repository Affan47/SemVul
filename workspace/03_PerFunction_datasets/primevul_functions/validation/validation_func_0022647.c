part_of_refkey(TABLE *table,Field *field)
{
  JOIN_TAB *join_tab= table->reginfo.join_tab;
  if (!join_tab)
    return (Item*) 0;

  uint ref_parts= join_tab->ref.key_parts;
  if (ref_parts)
  {
    uint key= join_tab->ref.key;
    KEY *key_info= join_tab->get_keyinfo_by_key_no(key);
    KEY_PART_INFO *key_part= key_info->key_part;

    for (uint part=0 ; part < ref_parts ; part++,key_part++)
    {
      if (field->eq(key_part->field))
      {


        if (part != join_tab->ref.null_ref_part &&
            !(key_part->key_part_flag & HA_PART_KEY_SEG))
        {
          return join_tab->ref.items[part];
        }
        break;
      }
    }
  }
  return (Item*) 0;
}
