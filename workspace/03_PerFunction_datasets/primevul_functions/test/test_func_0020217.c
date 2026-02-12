quote_string_for_globbing (pathname, qflags)
     const char *pathname;
     int qflags;
{
  char *temp;
  register int i, j;
  int cclass, collsym, equiv, c, last_was_backslash;
  int savei, savej;

  temp = (char *)xmalloc (2 * strlen (pathname) + 1);

  if ((qflags & QGLOB_CVTNULL) && QUOTED_NULL (pathname))
    {
      temp[0] = '\0';
      return temp;
    }

  cclass = collsym = equiv = last_was_backslash = 0;
  for (i = j = 0; pathname[i]; i++)
    {

      if (pathname[i] == CTLESC && pathname[i+1] == '\0')
	{
	  temp[j++] = pathname[i++];
	  break;
	}


      else if ((qflags & (QGLOB_REGEXP|QGLOB_CTLESC)) && pathname[i] == CTLESC && (pathname[i+1] == CTLESC || pathname[i+1] == CTLNUL))
	{
	  i++;
	  temp[j++] = pathname[i];
	  continue;
	}
      else if (pathname[i] == CTLESC)
	{
	  if ((qflags & QGLOB_FILENAME) && pathname[i+1] == '/')
	    continue;

	  if (pathname[i+1] != CTLESC && (qflags & QGLOB_REGEXP) && ere_char (pathname[i+1]) == 0)
	    continue;
	  temp[j++] = '\\';
	  i++;
	  if (pathname[i] == '\0')
	    break;
	}
      else if ((qflags & QGLOB_REGEXP) && (i == 0 || pathname[i-1] != CTLESC) && pathname[i] == '[')
	{
	  temp[j++] = pathname[i++];
	  savej = j;
	  savei = i;
	  c = pathname[i++];
	  if (c == '^')
	    {
	      temp[j++] = c;
	      c = pathname[i++];
	    }
	  if (c == ']')
	    {
	      temp[j++] = c;
	      c = pathname[i++];
	    }
	  do
	    {
	      if (c == 0)
		goto endpat;
	      else if (c == CTLESC)
		{


		  if (pathname[i] == 0)
		    goto endpat;
		  temp[j++] = pathname[i++];
		}
	      else if (c == '[' && pathname[i] == ':')
		{
		  temp[j++] = c;
		  temp[j++] = pathname[i++];
		  cclass = 1;
		}
	      else if (cclass && c == ':' && pathname[i] == ']')
		{
		  temp[j++] = c;
		  temp[j++] = pathname[i++];
		  cclass = 0;
		}
	      else if (c == '[' && pathname[i] == '=')
		{
		  temp[j++] = c;
		  temp[j++] = pathname[i++];
		  if (pathname[i] == ']')
		    temp[j++] = pathname[i++];
		  equiv = 1;
		}
	      else if (equiv && c == '=' && pathname[i] == ']')
		{
		  temp[j++] = c;
		  temp[j++] = pathname[i++];
		  equiv = 0;
		}
	      else if (c == '[' && pathname[i] == '.')
		{
		  temp[j++] = c;
		  temp[j++] = pathname[i++];
		  if (pathname[i] == ']')
		    temp[j++] = pathname[i++];
		  collsym = 1;
		}
	      else if (collsym && c == '.' && pathname[i] == ']')
		{
		  temp[j++] = c;
		  temp[j++] = pathname[i++];
		  collsym = 0;
		}
	      else
		temp[j++] = c;
	    }
	  while (((c = pathname[i++]) != ']') && c != 0);


	  if (c == 0)
	    {
	      i = savei - 1;
	      j = savej;
	      continue;
	    }

	  temp[j++] = c;
	  i--;
	  continue;
	}
      else if (pathname[i] == '\\' && (qflags & QGLOB_REGEXP) == 0)
	{


	  temp[j++] = '\\';

	  i++;
	  if (pathname[i] == '\0')
	    break;


	  if ((qflags & QGLOB_CTLESC) && pathname[i] == CTLESC && (pathname[i+1] == CTLESC || pathname[i+1] == CTLNUL))
	    i++;
	}
      else if (pathname[i] == '\\' && (qflags & QGLOB_REGEXP))
        last_was_backslash = 1;
      temp[j++] = pathname[i];
    }
endpat:
  temp[j] = '\0';

  return (temp);
}
