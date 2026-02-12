bool Item_param::convert_str_value(THD *thd)
{
  bool rc= FALSE;
  if (state == STRING_VALUE || state == LONG_DATA_VALUE)
  {


    if (value.cs_info.final_character_set_of_str_value !=
        value.cs_info.character_set_of_placeholder)
    {
      rc= thd->convert_string(&str_value,
                              value.cs_info.character_set_of_placeholder,
                              value.cs_info.final_character_set_of_str_value);
    }
    else
      str_value.set_charset(value.cs_info.final_character_set_of_str_value);


    max_length= str_value.numchars() * str_value.charset()->mbmaxlen;


    decimals= NOT_FIXED_DEC;


    str_value_ptr.set(str_value.ptr(), str_value.length(),
                      str_value.charset());

    collation.set(str_value.charset(), DERIVATION_COERCIBLE);
  }
  return rc;
}
