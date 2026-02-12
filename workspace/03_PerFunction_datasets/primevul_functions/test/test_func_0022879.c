void trim_whitespace(CHARSET_INFO *cs, LEX_STRING *str, uint *prefix_length)
{


  *prefix_length= 0;
  while ((str->length > 0) && (my_isspace(cs, str->str[0])))
  {
    (*prefix_length)++;
    str->length --;
    str->str ++;
  }


  while ((str->length > 0) && (my_isspace(cs, str->str[str->length-1])))
  {
    str->length --;
  }
}
