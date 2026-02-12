Item *Item_num::safe_charset_converter(CHARSET_INFO *tocs)
{


  if (!(tocs->state & MY_CS_NONASCII))
    return this;

  Item_string *conv;
  uint conv_errors;
  char buf[64], buf2[64];
  String tmp(buf, sizeof(buf), &my_charset_bin);
  String cstr(buf2, sizeof(buf2), &my_charset_bin);
  String *ostr= val_str(&tmp);
  char *ptr;
  cstr.copy(ostr->ptr(), ostr->length(), ostr->charset(), tocs, &conv_errors);
  if (conv_errors || !(conv= new Item_string(cstr.ptr(), cstr.length(),
                                             cstr.charset(),
                                             collation.derivation)))
  {


    return NULL;
  }
  if (!(ptr= current_thd->strmake(cstr.ptr(), cstr.length())))
    return NULL;
  conv->str_value.set(ptr, cstr.length(), cstr.charset());

  conv->str_value.mark_as_const();
  conv->fix_char_length(max_char_length());
  return conv;
}
