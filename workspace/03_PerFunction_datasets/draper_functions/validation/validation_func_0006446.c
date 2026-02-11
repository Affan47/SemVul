check_collation_compatibility()
{
  ulong mysql_version= table->s->mysql_version;

  if (mysql_version < 50124)
  {
    KEY *key= table->key_info;
    KEY *key_end= key + table->s->keys;
    for (; key < key_end; key++)
    {
      KEY_PART_INFO *key_part= key->key_part;
      KEY_PART_INFO *key_part_end= key_part + key->key_parts;
      for (; key_part < key_part_end; key_part++)
      {
        if (!key_part->fieldnr)
          continue;
        Field *field= table->field[key_part->fieldnr - 1];
        uint cs_number= field->charset()->number;
        if ((mysql_version < 50048 &&
             (cs_number == 11 ||
              cs_number == 41 ||
              cs_number == 42 ||
              cs_number == 20 ||
              cs_number == 21 ||
              cs_number == 22 ||
              cs_number == 23 ||
              cs_number == 26)) ||
             (mysql_version < 50124 &&
             (cs_number == 33 ||
              cs_number == 35)))
          return HA_ADMIN_NEEDS_UPGRADE;
      }
    }
  }
  return 0;
}
