print_offset (uintmax_t pos, int min_width, const char *color)
{


  char buf[sizeof pos * CHAR_BIT];
  char *p = buf + sizeof buf;

  do
    {
      *--p = '0' + pos % 10;
      --min_width;
    }
  while ((pos /= 10) != 0);


  if (align_tabs)
    while (--min_width >= 0)
      *--p = ' ';

  pr_sgr_start_if (color);
  fwrite (p, 1, buf + sizeof buf - p, stdout);
  pr_sgr_end_if (color);
}
