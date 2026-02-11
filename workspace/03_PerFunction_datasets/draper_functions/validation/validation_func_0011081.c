ieee_complex_type (p, size)
     PTR p;
     unsigned int size;
{
  struct ieee_handle *info = (struct ieee_handle *) p;
  char code;

  switch (size)
    {
    case 4:
      if (info->complex_float_index != 0)
	return ieee_push_type (info, info->complex_float_index, size * 2,
			       FALSE, FALSE);
      code = 'c';
      break;
    case 12:
    case 16:


    case 8:
      if (info->complex_double_index != 0)
	return ieee_push_type (info, info->complex_double_index, size * 2,
			       FALSE, FALSE);
      code = 'd';
      break;
    default:
      fprintf (stderr, _("IEEE unsupported complex type size %u\n"), size);
      return FALSE;
    }


  if (! ieee_define_type (info, size * 2, FALSE, FALSE)
      || ! ieee_write_number (info, code)
      || ! ieee_write_id (info, ""))
    return FALSE;

  if (size == 4)
    info->complex_float_index = info->type_stack->type.indx;
  else
    info->complex_double_index = info->type_stack->type.indx;

  return TRUE;
}
