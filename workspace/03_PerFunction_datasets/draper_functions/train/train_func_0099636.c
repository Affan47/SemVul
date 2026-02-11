calc_max_width()
{

  unsigned maxwidth = 0;
  unsigned i;
  for(i = 0; i < cli_option_count; i++) {
    unsigned width = 0;
    cli_option* o = cli_full_options[i];
    if(o->name) {
      width += strlen(o->name);
      switch(o->type) {
      case CLI_STRING:     width += 6; break;
      case CLI_INTEGER:    width += 4; break;
      case CLI_UINTEGER:   width += 4; break;
      case CLI_STRINGLIST: width += 5; break;
      case CLI_FUNCTION:   width += 6; break;
      case CLI_SEPARATOR:  width = 0; break;
      case CLI_FLAG:       break;
      case CLI_COUNTER:    break;
      }
    }
    if(width > maxwidth)
      maxwidth = width;
  }
  return maxwidth;
}
