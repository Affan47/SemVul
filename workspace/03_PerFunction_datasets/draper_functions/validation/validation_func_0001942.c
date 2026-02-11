infix_add_string(strid_t infix)
{
  glui32 ch;
  glui32 return_offset = infix_strlen;

  while((ch = glk_get_char_stream(infix)) != 0) {
    if(infix_stringdata)
      infix_stringdata[infix_strlen] = ch;
    infix_strlen++;
  }

  if(infix_stringdata)
    infix_stringdata[infix_strlen] = 0;
  infix_strlen++;

  return return_offset;
}
