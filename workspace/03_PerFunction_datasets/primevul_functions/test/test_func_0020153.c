bash_backward_shellword (count, key)
     int count, key;
{
  size_t slen;
  int c, p, prev_p;
  DECLARE_MBSTATE;

  if (count < 0)
    return (bash_forward_shellword (-count, key));

  p = rl_point;
  slen = rl_end;

  while (count)
    {
      if (p == 0)
	{
	  rl_point = 0;
	  return 0;
	}


      BACKUP_CHAR (rl_line_buffer, slen, p);
      while (p > 0)
	{
	  c = rl_line_buffer[p];
	  if (WORDDELIM (c) == 0 || char_is_quoted (rl_line_buffer, p))
	    break;
	  BACKUP_CHAR (rl_line_buffer, slen, p);
	}

      if (p == 0)
	{
	  rl_point = 0;
	  return 0;
	}


      prev_p = p;
      while (p > 0)
	{
	  c = rl_line_buffer[p];
	  if (WORDDELIM (c) && char_is_quoted (rl_line_buffer, p) == 0)
	    {
	      p = prev_p;
	      break;
	    }
	  prev_p = p;
	  BACKUP_CHAR (rl_line_buffer, slen, p);
	}

      count--;
    }

  rl_point = p;
  return 0;
}
