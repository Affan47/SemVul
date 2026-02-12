bool set_tty_option(char *name, char *value)
{
  if (!strcmp(name, "t_Co")) {
    int colors = atoi(value);


    if (colors != t_colors) {
      t_colors = colors;

      init_highlight(TRUE, FALSE);
    }

    return true;
  }

  return is_tty_option(name) || !strcmp(name, "term")
    || !strcmp(name, "ttytype");
}
