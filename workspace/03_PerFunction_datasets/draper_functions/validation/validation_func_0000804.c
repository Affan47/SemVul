argcv_scan (int len, const char *command, const char *delim, const char* cmnt,
	    int *start, int *end, int *save)
{
  int i = 0;

  for (;;)
    {
      i = *save;

      if (i >= len)
	return i + 1;


      while (i < len && isws (command[i]))
	i++;
      *start = i;

      if (!isdelim (command[i], delim))
	{
	  while (i < len)
	    {
	      if (command[i] == '\\')
		{
		  if (++i == len)
		    break;
		  i++;
		  continue;
		}

	      if (command[i] == '\'' || command[i] == '"')
		{
		  int j;
		  for (j = i+1; j < len && command[j] != command[i]; j++)
		    if (command[j] == '\\')
		      j++;
		  if (j < len)
		    i = j+1;
		  else
		    i++;
		}
	      else if (isws (command[i]) || isdelim (command[i], delim))
		break;
	      else
		i++;
	    }
	  i--;
	}

      *end = i;
      *save = i + 1;


      if (*save <= len)
	{
	  if (cmnt && strchr (cmnt, command[*start]) != NULL)
	    {
	      i = *save;
	      while (i < len && command[i] != '\n')
		i++;

	      *save = i;
	      continue;
	    }
	}
      break;
    }
  return *save;
}
