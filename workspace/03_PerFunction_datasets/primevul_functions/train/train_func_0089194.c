do_ctrl(char c)
{
  if (tek_mode) {
    tek_ctrl(c);
    return true;
  }

  switch (c) {
    when '\e':
      term.state = ESCAPE;
      term.esc_mod = 0;
    when '\a':
      write_bell();
    when '\b':
      write_backspace();
    when '\t':
      write_tab();
    when '\v':
      write_linefeed();
      if (term.newline_mode)
        write_return();
    when '\f':
      write_linefeed();
      if (term.newline_mode)
        write_return();
    when '\r':
      write_return();
    when '\n':
      write_linefeed();
      if (term.newline_mode)
        write_return();
    when CTRL('E'):
      if (!term.vt52_mode) {
        char * ab = cs__wcstombs(cfg.answerback);
        child_write(ab, strlen(ab));
        free(ab);
      }
    when CTRL('N'):
      if (!term.vt52_mode) {
        term.curs.gl = 1;
        term_update_cs();
      }
    when CTRL('O'):
      if (!term.vt52_mode) {
        term.curs.gl = 0;
        term_update_cs();
      }
    otherwise:
      return false;
  }
  return true;
}
