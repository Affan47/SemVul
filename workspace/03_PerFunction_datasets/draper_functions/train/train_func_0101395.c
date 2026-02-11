clear_subcollection(CSUBCOLLECTION *_object)
{
  void *value;
  HASH_ENUM iter;

  CLEAR(&iter);

  for(;;)
  {
    value = HASH_TABLE_next(THIS->hash_table, &iter);
    if (value == NULL)
      break;

     if (THIS->desc->release)
			(*THIS->desc->release)(THIS->container, *((void **)value));

    GB_Unref(value);
  }

  HASH_TABLE_delete(&THIS->hash_table);
}
