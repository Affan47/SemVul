type_suffix (tree type)
{
  static const char *const suffixes[] = { "", "U", "L", "UL", "LL", "ULL" };
  int unsigned_suffix;
  int is_long;

  if (type == long_long_integer_type_node
      || type == long_long_unsigned_type_node)
    is_long = 2;
  else if (type == long_integer_type_node
	   || type == long_unsigned_type_node)
    is_long = 1;
  else if (type == integer_type_node
	   || type == unsigned_type_node
	   || type == short_integer_type_node
	   || type == short_unsigned_type_node
	   || type == signed_char_type_node
	   || type == unsigned_char_type_node


	   || type == char_type_node)
    is_long = 0;
  else
    gcc_unreachable ();

  unsigned_suffix = TYPE_UNSIGNED (type);
  if (TYPE_PRECISION (type) < TYPE_PRECISION (integer_type_node))
    unsigned_suffix = 0;
  return suffixes[is_long * 2 + unsigned_suffix];
}
