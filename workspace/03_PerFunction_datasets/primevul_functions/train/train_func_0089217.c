tek_ctrl(char c)
{
  if (term.state == TEK_ADDRESS0 || term.state == TEK_ADDRESS)
    prev_state = term.state;

  switch (c) {
    when '\e':
      prev_state = term.state;
      term.state = TEK_ESCAPE;
    when '\a':
      write_bell();
      tek_bypass = false;
    when '\b' or '\t' or '\v':
      if (tek_mode == TEKMODE_ALPHA)
        tek_write(c, -2);
    when '\n':
      tek_bypass = false;
      tek_write(c, -2);
    when '\r':
      tek_mode = TEKMODE_ALPHA;
      term.state = NORMAL;
      tek_bypass = false;
      tek_write(c, -2);
    when 0x1C:
      tek_mode = TEKMODE_POINT_PLOT;
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
      tek_bypass = false;
  }
}
