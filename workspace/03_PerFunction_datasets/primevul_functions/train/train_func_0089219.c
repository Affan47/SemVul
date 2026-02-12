do_colour_osc(bool has_index_arg, uint i, bool reset)
{
  int osc_num = term.cmd_num;
  char *s = term.cmd_buf;
  int index;

do_osc_control:

  if (has_index_arg) {
    int osc = i;
    int len = 0;
    sscanf(s, "%u;%n", &index, &len);
    i = index;
    if ((reset ? len != 0 : len == 0) || i >= COLOUR_NUM)
      return;
    s += len;
    if (osc % 100 == 5) {
      if (i == 0)
        i = BOLD_COLOUR_I;
#ifdef other_color_substitutes
      else if (i == 1)
        i = UNDERLINE_COLOUR_I;
      else if (i == 2)
        i = BLINK_COLOUR_I;
      else if (i == 3)
        i = REVERSE_COLOUR_I;
      else if (i == 4)
        i = ITALIC_COLOUR_I;
#endif
      else if (i > 4)
        return;
      else {

        i = COLOUR_NUM;
      }
    }
    else if (i >= 256)
      return;
  }

  char * cont = strchr(s, ';');
  if (cont)
    *cont = 0;

  colour c;
  if (i >= COLOUR_NUM) {

  }
  else if (reset)
    win_set_colour(i, (colour)-1);
  else if (!strcmp(s, "?")) {
    child_printf("\e]%u;", osc_num);
    if (has_index_arg)
      child_printf("%u;", index);
    c = i < COLOUR_NUM ? colours[i] : 0;
    char * osc_fini = term.state == CMD_ESCAPE ? "\e\\" : "\a";
    child_printf("rgb:%04x/%04x/%04x%s",
                 red(c) * 0x101, green(c) * 0x101, blue(c) * 0x101, osc_fini);
  }
  else if (parse_colour(s, &c))
    win_set_colour(i, c);

  if (cont) {
    s = cont;
    s++;
    if (osc_num >= 10 && osc_num <= 19) {
      int new_num;
      int len = 0;
      sscanf(s, "%u;%n", &new_num, &len);
      if (len) {
        s += len;
        osc_num = new_num;
      }
      else
        osc_num++;


      switch (osc_num) {
        when 10:   i = FG_COLOUR_I;
        when 11:   i = BG_COLOUR_I;
        when 12:   i = CURSOR_COLOUR_I;
        when 17:   i = SEL_COLOUR_I;
        when 19:   i = SEL_TEXT_COLOUR_I;
        when 15:   i = TEK_FG_COLOUR_I;
        when 16:   i = TEK_BG_COLOUR_I;
        when 18:   i = TEK_CURSOR_COLOUR_I;
        otherwise: i = COLOUR_NUM;
      }
    }
    goto do_osc_control;
  }
}
