bash_forward_shellword (count, key)
     int count, key;
{
  size_t slen;
  int c, p;
  DECLARE_MBSTATE;

  if (count < 0)
    return (bash_backward_shellword (-count, key));


  p = rl_point;
  slen = rl_end;

  while (count)
    {
      if (p == rl_end)
	{
	  rl_point = rl_end;
	  return 0;
	}


      if (char_is_quoted (rl_line_buffer, p) && p > 0 && rl_line_buffer[p-1] != '\\')
	{
	  do
	    ADVANCE_CHAR (rl_line_buffer, slen, p);
	  while (p < rl_end && char_is_quoted (rl_line_buffer, p));
	  count--;
	  continue;
	}


      while (p < rl_end && (c = rl_line_buffer[p]) && WORDDELIM (c))
	{
	  switch (c)
	    {
	    default:
	      ADVANCE_CHAR (rl_line_buffer, slen, p);
	      continue;
	    case '\\':
	      if (p < rl_end && rl_line_buffer[p])
		ADVANCE_CHAR (rl_line_buffer, slen, p);
	      break;
	    case '\'':
	      p = skip_to_delim (rl_line_buffer, ++p, "'", SD_NOJMP);
	      break;
	    case '"':
	      p = skip_to_delim (rl_line_buffer, ++p, "\"", SD_NOJMP);
	      break;
	    }

	  if (p < rl_end)
	    p++;
	}

      if (rl_line_buffer[p] == 0 || p == rl_end)
        {
	  rl_point = rl_end;
	  rl_ding ();
	  return 0;
        }


      while (p < rl_end && (c = rl_line_buffer[p]) && WORDDELIM (c) == 0)
	{
	  switch (c)
	    {
	    default:
	      ADVANCE_CHAR (rl_line_buffer, slen, p);
	      continue;
	    case '\\':
	      if (p < rl_end && rl_line_buffer[p])
		ADVANCE_CHAR (rl_line_buffer, slen, p);
	      break;
	    case '\'':
	      p = skip_to_delim (rl_line_buffer, ++p, "'", SD_NOJMP);
	      break;
	    case '"':
	      p = skip_to_delim (rl_line_buffer, ++p, "\"", SD_NOJMP);
	      break;
	    }

	  if (p < rl_end)
	    p++;
	}

      if (p == rl_end || rl_line_buffer[p] == 0)
	{
	  rl_point = rl_end;
	  return (0);
	}

      count--;
    }

  rl_point = p;
  return (0);
}
