do_vt52(uchar c)
{
  term_cursor *curs = &term.curs;
  term.state = NORMAL;
  term.autowrap = false;
  term.rev_wrap = false;
  term.esc_mod = 0;
  switch (c) {
    when '\e':
      term.state = ESCAPE;
    when '<':
      term.vt52_mode = 0;
    when '=':
      term.app_keypad = true;
    when '>':
      term.app_keypad = false;
    when 'A':
      move(curs->x, curs->y - 1, 0);
    when 'B':
      move(curs->x, curs->y + 1, 0);
    when 'C':
      move(curs->x + 1, curs->y, 0);
    when 'D':
      move(curs->x - 1, curs->y, 0);
    when 'F':
      term.vt52_mode = 2;
    when 'G':
      term.vt52_mode = 1;
    when 'H':
      move(0, 0, 0);
    when 'I':
      if (curs->y == term.marg_top)
        term_do_scroll(term.marg_top, term.marg_bot, -1, true);
      else if (curs->y > 0)
        curs->y--;
      curs->wrapnext = false;
    when 'J':
      term_erase(false, false, false, true);
    when 'K':
      term_erase(false, true, false, true);
    when 'Y':
      term.state = VT52_Y;
    when 'Z':
      child_write("\e/Z", 3);

    when 'E':
      move(0, 0, 0);
      term_erase(false, false, false, true);
    when 'b':
      term.state = VT52_FG;
    when 'c':
      term.state = VT52_BG;
    when 'd':
      term_erase(false, false, true, false);
    when 'e':
      term.cursor_on = true;
    when 'f':
      term.cursor_on = false;
    when 'j':
      save_cursor();
    when 'k':
      restore_cursor();
    when 'l':
      term_erase(false, true, true, true);
      write_return();
    when 'o':
      term_erase(false, true, true, false);
    when 'p':
      term.curs.attr.attr |= ATTR_REVERSE;
    when 'q':
      term.curs.attr.attr &= ~ATTR_REVERSE;
    when 'v':
      term.autowrap = true;
      term.curs.wrapnext = false;
    when 'w':
      term.autowrap = false;
      term.curs.wrapnext = false;
  }
}
