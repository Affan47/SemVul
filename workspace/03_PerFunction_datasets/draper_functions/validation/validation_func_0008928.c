_fiid_obj_field_start_end (fiid_obj_t obj,
                           const char *field,
                           unsigned int *start,
                           unsigned int *end)
{
  unsigned int i = 0;
  unsigned int _start = 0;
  unsigned int _end = 0;

  assert (obj);
  assert (obj->magic == FIID_OBJ_MAGIC);
  assert (field);
  assert (start);
  assert (end);


  for (i = 0; obj->field_data[i].max_field_len; i++)
    {
      if (!strcmp (obj->field_data[i].key, field))
        {
          _end = _start + obj->field_data[i].max_field_len;
          *start = _start;
          *end = _end;
          return (obj->field_data[i].max_field_len);
        }
      _start += obj->field_data[i].max_field_len;
    }

  obj->errnum = FIID_ERR_FIELD_NOT_FOUND;
  return (-1);
}
