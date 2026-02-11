rl_vi_back_to_indent (count, key)
     int count, key;
{
  rl_beg_of_line (1, key);
  while (rl_point < rl_end && whitespace (rl_line_buffer[rl_point]))
    rl_point++;
  return (0);
}
