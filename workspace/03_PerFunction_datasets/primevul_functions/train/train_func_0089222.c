tek_esc(char c)
{
  if (prev_state)
    term.state = prev_state;
  else
    term.state = NORMAL;

  switch (c) {
    when '\e':
      term.state = TEK_ESCAPE;
    when '\n':
      term.state = TEK_ESCAPE;
    when 0 or '\r':
      term.state = TEK_ESCAPE;
    when '\a':
      write_bell();
    when '\b' or '\t' or '\v':
      tek_write(c, -2);
    when CTRL('L'):
      tek_mode = TEKMODE_ALPHA;
      term.state = NORMAL;
      tek_bypass = false;
      tek_clear();
    when CTRL('E'):
      tek_bypass = true;
      tek_enq();
    when CTRL('N'):
      tek_alt(true);
    when CTRL('O'):
      tek_alt(false);
    when CTRL('W'):
      term_save_image();
      tek_bypass = false;
    when CTRL('X'):
      tek_bypass = true;
    when CTRL('Z'):
      tek_mode = TEKMODE_GIN;
      tek_gin();
      term.state = NORMAL;
      tek_bypass = true;
    when 0x1C:
      tek_mode = TEKMODE_SPECIAL_PLOT;
      term.state = TEK_ADDRESS0;
    when 0x1D:
      tek_mode = TEKMODE_GRAPH0;
      term.state = TEK_ADDRESS0;
    when 0x1E:
      tek_mode = TEKMODE_INCREMENTAL_PLOT;
      term.state = TEK_INCREMENTAL;
    when 0x1F:
      tek_mode = TEKMODE_ALPHA;
      term.state = NORMAL;
    when '`' ... 'g':
      tek_beam(false, false, c & 7);
    when 'h' ... 'o':
      tek_beam(true, false, c & 7);
    when 'p' ... 'w':
      tek_beam(false, true, c & 7);
    when '8' ... ';':
      tek_font(c - '8');
    when '?':
      if (term.state == TEK_ADDRESS0 || term.state == TEK_ADDRESS)
        term_do_write("", 1);
    when CTRL('C'):
      tek_mode = TEKMODE_OFF;
      term.state = NORMAL;
      win_invalidate_all(false);
    when ']':
      term.state = OSC_START;
  }
}
