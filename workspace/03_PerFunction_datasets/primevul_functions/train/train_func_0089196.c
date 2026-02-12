write_error(void)
{


  wchar errch = 0xFFFD;
  win_check_glyphs(&errch, 1, term.curs.attr.attr);
  if (!errch)
    errch = 0x2592;
  write_char(errch, 1);
}
