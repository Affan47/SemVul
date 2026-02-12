static LEX_CSTRING get_token(const char **str)
{
  LEX_CSTRING ret = { NULL, 0 };

  if (*str != NULL)
  {
    ret.str= *str;

    if (*ret.str != '\0')
    {

      while (**str && **str != ';') (*str)++;

      ret.length= *str - ret.str;


      if (**str == ';') (*str)++;
    }
  }

  return ret;
}
