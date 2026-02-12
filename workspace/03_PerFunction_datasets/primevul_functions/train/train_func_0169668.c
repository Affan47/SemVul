bool Item_param::set_str(const char *str, ulong length)
{
  DBUG_ENTER("Item_param::set_str");


  uint dummy_errors;
  if (str_value.copy(str, length, &my_charset_bin, &my_charset_bin,
                     &dummy_errors))
    DBUG_RETURN(TRUE);
  state= STRING_VALUE;
  max_length= length;
  maybe_null= 0;


  DBUG_RETURN(FALSE);
}
