print_line_middle (const char *beg, const char *lim,
                   const char *line_color, const char *match_color)
{
  size_t match_size;
  size_t match_offset;
  const char *cur = beg;
  const char *mid = NULL;

  while (cur < lim
         && ((match_offset = execute (beg, lim - beg, &match_size,
                                      beg + (cur - beg))) != (size_t) -1))
    {
      char const *b = beg + match_offset;


      if (b == lim)
        break;


      if (match_size == 0)
        {


          match_size = 1;
          if (!mid)
            mid = cur;
        }
      else
        {


          if (only_matching)
            print_line_head (b, lim, (out_invert ? SEP_CHAR_REJECTED
                                      : SEP_CHAR_SELECTED));
          else
            {
              pr_sgr_start (line_color);
              if (mid)
                {
                  cur = mid;
                  mid = NULL;
                }
              fwrite (cur, sizeof (char), b - cur, stdout);
            }

          pr_sgr_start_if (match_color);
          fwrite (b, sizeof (char), match_size, stdout);
          pr_sgr_end_if (match_color);
          if (only_matching)
            fputs ("\n", stdout);
        }
      cur = b + match_size;
    }

  if (only_matching)
    cur = lim;
  else if (mid)
    cur = mid;

  return cur;
}
