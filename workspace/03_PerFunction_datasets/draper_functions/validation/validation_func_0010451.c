vfy_count_arguments (vfy_string signature)
{
  const char *ptr = IDENTIFIER_POINTER (signature);
  int arg_count = 0;


  ptr++;


  while (*ptr != ')')
    {
      ptr = skip_one_type (ptr);
      arg_count += 1;
    }

  return arg_count;
}
